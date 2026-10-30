#ifndef COMPLETE_TREE_H
#define COMPLETE_TREE_H

#include <string>

// Узел бинарного дерева
struct TreeNode {
    std::string val;   // Значение узла (строка)
    TreeNode* left;    // Указатель на левого потомка
    TreeNode* right;   // Указатель на правого потомка
};

// Структура дерева Complete Binary Tree (Вариант 3)
struct CompleteTree {
    TreeNode* root;    // Указатель на корень дерева

    void init();                                     
    void destroy();                                    

    void insert(const std::string& val);// Вставка с сохранением Complete 
    bool find(const std::string& val) const;// Поиск значения
    bool is_complete() const;// Проверка на свойство Complete
    void print() const;           
};                
#endif // COMPLETE_TREE_H