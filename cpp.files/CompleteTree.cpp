#include "../h.files/CompleteTree.h"
#include <iostream>
#include <queue>                    

using namespace std;

// Инициализация пустого дерева: корень указывает в nullptr
void CompleteTree::init() {
    root = nullptr;
}

// Вспомогательная функция: рекурсивно удаляет поддеревья снизу вверх 
static void free_nodes(TreeNode* node) {
    if (node == nullptr) return;
    free_nodes(node->left);   // Сначала очищаем левое поддерево
    free_nodes(node->right);  // Затем правое
    delete node;              // Затем удаляем сам корень
}

// Очистка всего дерева
void CompleteTree::destroy() {
    free_nodes(root);
    root = nullptr;
}

// Вставка по уровням слева направо через BFS
void CompleteTree::insert(const string& val) {
    TreeNode* node = new TreeNode{val, nullptr, nullptr}; // Создаем новый узел

    // Если дерево пустое, новый узел становится корнем
    if (root == nullptr) {
        root = node;
        return;
    }

    // Иначе запускаем очередь для поиска первого узла с пустым местом
    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        TreeNode* curr = q.front();
        q.pop();

        // Проверяем левое место: если свободно — вставляем и завершаем
        if (curr->left == nullptr) {
            curr->left = node;
            return;
        } else {
            q.push(curr->left); // Если занято — добавляем в очередь на проверку
        }

        // 2. Проверяем правое место: если свободно — вставляем и завершаем
        if (curr->right == nullptr) {
            curr->right = node;
            return;
        } else {
            q.push(curr->right); // Если занято — добавляем в очередь на проверку
        }
    }
}

// Алгоритм проверки свойства Complete
bool CompleteTree::is_complete() const {
    if (root == nullptr) return true; 

    queue<TreeNode*> q;// Создаем очередь для обхода BFS
    q.push(root);                    
    bool seen_null = false;// Флаг: встречалась ли нам уже пустота

    while (!q.empty()) {
        TreeNode* curr = q.front();// Берем первый элемент из очереди
        q.pop();

        if (curr == nullptr) {
            seen_null = true;// Зафиксировали первую дыру/пустоту
        } else {
            if (seen_null) {
                return false;
            }
            // Добавляем детей в очередь (даже если они nullptr, чтобы зафиксировать пустоту)
            q.push(curr->left);
            q.push(curr->right);
        }
    }
    return true;
}
bool CompleteTree::find(const string& val) const {
    if (root == nullptr) return false;

    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        TreeNode* curr = q.front();
        q.pop();

        if (curr->val == val) 
            return true; // Значение найдено

        if (curr->left != nullptr)  
            q.push(curr->left);
        if (curr->right != nullptr) 
            q.push(curr->right);
    }
    return false;
}

void CompleteTree::print() const {
    if (root == nullptr) {
        cout << "[]\n";
        return;
    }

    queue<TreeNode*> q;
    q.push(root);
    cout << "Complete Tree (по уровням):\n";

    int level = 0;
    while (!q.empty()) {
        int level_size = q.size();
        cout << "  Уровень " << level << ": ";

        for (int i = 0; i < level_size; ++i) {
            TreeNode* curr = q.front();
            q.pop();

            cout << "[" << curr->val << "] ";

            if (curr->left != nullptr)  q.push(curr->left);
            if (curr->right != nullptr) q.push(curr->right);
        }
        cout << "\n";
        level++;
    }
}