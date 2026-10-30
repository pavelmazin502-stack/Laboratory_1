#include "Database/Database.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    string filename = "";
    string query = "";

    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];
        if (arg == "--file" && i + 1 < argc) {
            filename = argv[++i];
        } else if (arg == "--query" && i + 1 < argc) {
            query = argv[++i];
        }
    }

    if (filename.empty() || query.empty()) {
        cerr << "Использование: ./dbms --file <файл_базы> --query '<команда>'\n";
        return 1;
    }

    // Разбиваем строку query на токены
    vector<string> tokens;
    istringstream ss(query);
    string token;
    while (ss >> token) {
        tokens.push_back(token);
    }

    Database db;
    db.load(filename);
    db.execute(tokens);
    db.save(filename);

    return 0;
}