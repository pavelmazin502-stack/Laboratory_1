#ifndef SINGLY_LIST_H
#define SINGLY_LIST_H

#include <string>  
#include <sstream>

// Узел односвязного списка
struct SinglyNode {
    std::string val;  // Данные узла
    SinglyNode* next; // Указатель на следующий узел
};

// Заголовок односвязного списка
struct SinglyList {
    SinglyNode* head; // Указатель на первый элемент списка
    SinglyNode* tail; // Указатель на последний элемент списка
    int size;         // Количество элементов

    void init();                                                           // Инициализация пустого списка
    void clear();                                                          // Полная очистка памяти всех узлов

    void push_head(const std::string& val);                                // Добавление в голову (1 способ)
    void push_tail(const std::string& val);                                // Добавление в хвост (2 способ)
    bool insert_before(const std::string& target, const std::string& val); // Вставка ДО элемента (3 способ)
    bool insert_after(const std::string& target, const std::string& val);  // Вставка ПОСЛЕ элемента (4 способ)

    std::string pop_head();                                                // Удаление из головы
    std::string pop_tail();                                                // Удаление из хвоста
    bool remove_val(const std::string& val);                               // Удаление узла по значению

    bool find(const std::string& val) const;                               // Проверка наличия значения
    std::string get(int index) const;                                      // Доступ по индексу
    void print() const;                                                    // Вывод списка: [a -> b -> c]

    std::string serialize() const;                                         // Сохранение в строку
    void deserialize(std::istringstream& ss);                              // Восстановление из строки
};

#endif // SINGLY_LIST_H