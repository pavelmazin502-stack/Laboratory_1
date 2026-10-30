#include "Database.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <vector>

using namespace std;

// Таблица соответствия строкового имени команды значению enum
static const map<string, Command> COMMANDS = {
    {"MPUSH", Command::MPUSH},
    {"MINSERT", Command::MINSERT},
    {"MGET", Command::MGET},
    {"MSET", Command::MSET},
    {"MDEL", Command::MDEL},
    {"MLEN", Command::MLEN},

    {"FPUSH", Command::FPUSH},
    {"FPUSH_HEAD", Command::FPUSH_HEAD},
    {"FPUSH_TAIL", Command::FPUSH_TAIL},
    {"FDEL", Command::FDEL},
    {"FPOP_HEAD", Command::FPOP_HEAD},
    {"FPOP_TAIL", Command::FPOP_TAIL},
    {"FDEL_VAL", Command::FDEL_VAL},
    {"FFIND", Command::FFIND},
    {"FGET", Command::FGET},
    {"FINSERT_BEFORE", Command::FINSERT_BEFORE},
    {"FINSERT_AFTER", Command::FINSERT_AFTER},

    {"LPUSH", Command::LPUSH},
    {"LPUSH_HEAD", Command::LPUSH_HEAD},
    {"LPUSH_TAIL", Command::LPUSH_TAIL},
    {"LDEL", Command::LDEL},
    {"LPOP_HEAD", Command::LPOP_HEAD},
    {"LPOP_TAIL", Command::LPOP_TAIL},
    {"LDEL_VAL", Command::LDEL_VAL},
    {"LFIND", Command::LFIND},
    {"LGET", Command::LGET},
    {"LINSERT_BEFORE", Command::LINSERT_BEFORE},
    {"LINSERT_AFTER", Command::LINSERT_AFTER},

    {"SPUSH", Command::SPUSH},
    {"SPOP", Command::SPOP},
    {"SPEEK", Command::SPEEK},

    {"QPUSH", Command::QPUSH},
    {"QPOP", Command::QPOP},
    {"QPEEK", Command::QPEEK},

    {"TINSERT", Command::TINSERT},
    {"TFIND", Command::TFIND},
    {"TISCOMPLETE", Command::TISCOMPLETE},
    {"TGET", Command::TGET},

    {"PRINT", Command::PRINT},
    {"ISMEMBER", Command::ISMEMBER}
};

static Command parseCommand(const string& cmd) {
    auto it = COMMANDS.find(cmd);
    if (it == COMMANDS.end()) return Command::UNKNOWN;
    return it->second;
}

void Database::execute(const vector<string>& tokens) {
    if (tokens.empty()) return;

    Command cmd = parseCommand(tokens[0]);

    // Автоматическая инициализация структуры при первом обращении к ней
    if (tokens.size() > 1) {
        const string& name = tokens[1];
        char firstChar = tokens[0][0];

        if (firstChar == 'M' && arrays.find(name) == arrays.end()) {
            MyArray a; a.init(); arrays[name] = a;
        } else if (firstChar == 'F' && slists.find(name) == slists.end()) {
            SinglyList l; l.init(); slists[name] = l;
        } else if (firstChar == 'L' && dlists.find(name) == dlists.end()) {
            DoublyList l; l.init(); dlists[name] = l;
        } else if (firstChar == 'S' && stacks.find(name) == stacks.end()) {
            Stack s; s.init(); stacks[name] = s;
        } else if (firstChar == 'Q' && queues.find(name) == queues.end()) {
            Queue q; q.init(); queues[name] = q;
        } else if (firstChar == 'T' && trees.find(name) == trees.end()) {
            CompleteTree t; t.init(); trees[name] = t;
        }
    }

    switch (cmd) {
        // --- МАССИВ (M) ---
        case Command::MPUSH: {
            string name = tokens[1];
            string val = tokens[2];
            arrays[name].push_back(val);
            cout << "-> " << val << "\n";
            break;
        }
        case Command::MINSERT: {
            string name = tokens[1];
            int idx = stoi(tokens[2]);
            string val = tokens[3];
            arrays[name].insert(idx, val);
            cout << "-> " << val << "\n";
            break;
        }
        case Command::MGET: {
            string name = tokens[1];
            int idx = stoi(tokens[2]);
            cout << "-> " << arrays[name].get(idx) << "\n";
            break;
        }
        case Command::MSET: {
            string name = tokens[1];
            int idx = stoi(tokens[2]);
            string val = tokens[3];
            arrays[name].set(idx, val);
            cout << "-> " << val << "\n";
            break;
        }
        case Command::MDEL: {
            string name = tokens[1];
            int idx = stoi(tokens[2]);
            arrays[name].remove(idx);
            cout << "-> OK\n";
            break;
        }
        case Command::MLEN: {
            string name = tokens[1];
            cout << "-> " << arrays[name].get_size() << "\n";
            break;
        }

        // --- ОДНОСВЯЗНЫЙ СПИСОК (F) ---
        case Command::FPUSH:
        case Command::FPUSH_TAIL: {
            string name = tokens[1];
            string val = tokens[2];
            slists[name].push_tail(val);
            cout << "-> " << val << "\n";
            break;
        }
        case Command::FPUSH_HEAD: {
            string name = tokens[1];
            string val = tokens[2];
            slists[name].push_head(val);
            cout << "-> " << val << "\n";
            break;
        }
        case Command::FDEL:
        case Command::FPOP_HEAD: {
            string name = tokens[1];
            cout << "-> " << slists[name].pop_head() << "\n";
            break;
        }
        case Command::FPOP_TAIL: {
            string name = tokens[1];
            cout << "-> " << slists[name].pop_tail() << "\n";
            break;
        }
        case Command::FDEL_VAL: {
            string name = tokens[1];
            string val = tokens[2];
            cout << "-> " << (slists[name].remove_val(val) ? "TRUE" : "FALSE") << "\n";
            break;
        }
        case Command::FFIND: {
            string name = tokens[1];
            string val = tokens[2];
            cout << "-> " << (slists[name].find(val) ? "TRUE" : "FALSE") << "\n";
            break;
        }
        case Command::FGET: {
            string name = tokens[1];
            int idx = stoi(tokens[2]);
            cout << "-> " << slists[name].get(idx) << "\n";
            break;
        }
        case Command::FINSERT_BEFORE: {
            string name = tokens[1];
            string target = tokens[2];
            string val = tokens[3];
            cout << "-> " << (slists[name].insert_before(target, val) ? val : "ERROR") << "\n";
            break;
        }
        case Command::FINSERT_AFTER: {
            string name = tokens[1];
            string target = tokens[2];
            string val = tokens[3];
            cout << "-> " << (slists[name].insert_after(target, val) ? val : "ERROR") << "\n";
            break;
        }

        // --- ДВУСВЯЗНЫЙ СПИСОК (L) ---
        case Command::LPUSH:
        case Command::LPUSH_TAIL: {
            string name = tokens[1];
            string val = tokens[2];
            dlists[name].push_tail(val);
            cout << "-> " << val << "\n";
            break;
        }
        case Command::LPUSH_HEAD: {
            string name = tokens[1];
            string val = tokens[2];
            dlists[name].push_head(val);
            cout << "-> " << val << "\n";
            break;
        }
        case Command::LDEL:
        case Command::LPOP_HEAD: {
            string name = tokens[1];
            cout << "-> " << dlists[name].pop_head() << "\n";
            break;
        }
        case Command::LPOP_TAIL: {
            string name = tokens[1];
            cout << "-> " << dlists[name].pop_tail() << "\n";
            break;
        }
        case Command::LDEL_VAL: {
            string name = tokens[1];
            string val = tokens[2];
            cout << "-> " << (dlists[name].remove_val(val) ? "TRUE" : "FALSE") << "\n";
            break;
        }
        case Command::LFIND: {
            string name = tokens[1];
            string val = tokens[2];
            cout << "-> " << (dlists[name].find(val) ? "TRUE" : "FALSE") << "\n";
            break;
        }
        case Command::LGET: {
            string name = tokens[1];
            int idx = stoi(tokens[2]);
            cout << "-> " << dlists[name].get(idx) << "\n";
            break;
        }
        case Command::LINSERT_BEFORE: {
            string name = tokens[1];
            string target = tokens[2];
            string val = tokens[3];
            cout << "-> " << (dlists[name].insert_before(target, val) ? val : "ERROR") << "\n";
            break;
        }
        case Command::LINSERT_AFTER: {
            string name = tokens[1];
            string target = tokens[2];
            string val = tokens[3];
            cout << "-> " << (dlists[name].insert_after(target, val) ? val : "ERROR") << "\n";
            break;
        }

        // --- СТЕК (S) ---
        case Command::SPUSH: {
            string name = tokens[1];
            string val = tokens[2];
            stacks[name].push(val);
            cout << "-> " << val << "\n";
            break;
        }
        case Command::SPOP: {
            string name = tokens[1];
            cout << "-> " << stacks[name].pop() << "\n";
            break;
        }
        case Command::SPEEK: {
            string name = tokens[1];
            cout << "-> " << stacks[name].peek() << "\n";
            break;
        }

        // --- ОЧЕРЕДЬ (Q) ---
        case Command::QPUSH: {
            string name = tokens[1];
            string val = tokens[2];
            queues[name].push(val);
            cout << "-> " << val << "\n";
            break;
        }
        case Command::QPOP: {
            string name = tokens[1];
            cout << "-> " << queues[name].pop() << "\n";
            break;
        }
        case Command::QPEEK: {
            string name = tokens[1];
            cout << "-> " << queues[name].peek() << "\n";
            break;
        }

        // --- ДЕРЕВО (T) ---
        case Command::TINSERT: {
            string name = tokens[1];
            string val = tokens[2];
            trees[name].insert(val);
            cout << "-> " << val << "\n";
            break;
        }
        case Command::TFIND: {
            string name = tokens[1];
            string val = tokens[2];
            cout << "-> " << (trees[name].find(val) ? "TRUE" : "FALSE") << "\n";
            break;
        }
        case Command::TISCOMPLETE: {
            string name = tokens[1];
            cout << "-> " << (trees[name].is_complete() ? "TRUE" : "FALSE") << "\n";
            break;
        }
        case Command::TGET: {
            string name = tokens[1];
            if (trees[name].root != nullptr) cout << "-> " << trees[name].root->val << "\n";
            else cout << "-> \n";
            break;
        }

        // --- УНИВЕРСАЛЬНЫЕ КОМАНДЫ ---
        case Command::PRINT: {
            string name = tokens[1];
            if (arrays.count(name)) arrays[name].print();
            else if (slists.count(name)) slists[name].print();
            else if (dlists.count(name)) dlists[name].print();
            else if (stacks.count(name)) stacks[name].print();
            else if (queues.count(name)) queues[name].print();
            else if (trees.count(name)) trees[name].print();
            else cout << "Структура " << name << " не найдена\n";
            break;
        }
        case Command::ISMEMBER: {
            string name = tokens[1];
            string val = tokens[2];
            bool found = false;
            if (trees.count(name)) found = trees[name].find(val);
            else if (slists.count(name)) found = slists[name].find(val);
            else if (dlists.count(name)) found = dlists[name].find(val);
            else if (arrays.count(name)) {
                for (int i = 0; i < arrays[name].get_size(); ++i) {
                    if (arrays[name].get(i) == val) { found = true; break; }
                }
            }
            cout << "-> " << (found ? "TRUE" : "FALSE") << "\n";
            break;
        }

        case Command::UNKNOWN:
        default:
            cout << "Неизвестная команда: " << tokens[0] << "\n";
            break;
    }
}

void Database::load(const string& filename) {
    arrays.clear();
    slists.clear();
    dlists.clear();
    stacks.clear();
    queues.clear();
    trees.clear();

    ifstream file(filename);
    if (!file.is_open()) return;

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;

        istringstream ss(line);
        string type, name;
        int count;
        if (!(ss >> type >> name >> count)) continue;

        if (type == "ARRAY") {
            MyArray a; a.init();
            for (int i = 0; i < count; ++i) { string v; ss >> v; a.push_back(v); }
            arrays[name] = a;
        } else if (type == "SLIST") {
            SinglyList l; l.init();
            for (int i = 0; i < count; ++i) { string v; ss >> v; l.push_tail(v); }
            slists[name] = l;
        } else if (type == "DLIST") {
            DoublyList l; l.init();
            for (int i = 0; i < count; ++i) { string v; ss >> v; l.push_tail(v); }
            dlists[name] = l;
        } else if (type == "STACK") {
            Stack s; s.init();
            string* tmp = new string[count];
            for (int i = 0; i < count; ++i) ss >> tmp[i];
            for (int i = count - 1; i >= 0; --i) s.push(tmp[i]);
            delete[] tmp;
            stacks[name] = s;
        } else if (type == "QUEUE") {
            Queue q; q.init();
            for (int i = 0; i < count; ++i) { string v; ss >> v; q.push(v); }
            queues[name] = q;
        } else if (type == "TREE") {
            CompleteTree t; t.init();
            for (int i = 0; i < count; ++i) { string v; ss >> v; t.insert(v); }
            trees[name] = t;
        }
    }
}

void Database::save(const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) return;

    for (const auto& p : arrays) {
        file << "ARRAY " << p.first << " " << p.second.get_size();
        for (int i = 0; i < p.second.get_size(); ++i) file << " " << p.second.get(i);
        file << "\n";
    }

    for (const auto& p : slists) {
        file << "SLIST " << p.first << " " << p.second.size;
        for (int i = 0; i < p.second.size; ++i) file << " " << p.second.get(i);
        file << "\n";
    }

    for (const auto& p : dlists) {
        file << "DLIST " << p.first << " " << p.second.size;
        for (int i = 0; i < p.second.size; ++i) file << " " << p.second.get(i);
        file << "\n";
    }

    for (auto p : stacks) {
        file << "STACK " << p.first << " " << p.second.size;
        StackNode* curr = p.second.top;
        while (curr != nullptr) {
            file << " " << curr->val;
            curr = curr->next;
        }
        file << "\n";
    }

    for (auto p : queues) {
        file << "QUEUE " << p.first << " " << p.second.size;
        QueueNode* curr = p.second.head;
        while (curr != nullptr) {
            file << " " << curr->val;
            curr = curr->next;
        }
        file << "\n";
    }

    for (const auto& p : trees) {
        vector<string> vals;
        if (p.second.root != nullptr) {
            queue<TreeNode*> q;
            q.push(p.second.root);
            while (!q.empty()) {
                TreeNode* c = q.front(); q.pop();
                vals.push_back(c->val);
                if (c->left) q.push(c->left);
                if (c->right) q.push(c->right);
            }
        }
        file << "TREE " << p.first << " " << vals.size();
        for (const auto& v : vals) file << " " << v;
        file << "\n";
    }
}