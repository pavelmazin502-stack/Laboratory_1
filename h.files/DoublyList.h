#ifndef DOUBLY_LIST_H
#define DOUBLY_LIST_H

#include <string>

// Сам узел списка 
struct DoublyNode{
    std::string val; // Данные 
    DoublyNode* prev; // Указатель на предыдущий узел в памяти 
    DoublyNode* next;
};
// Структура всего двусвязного списка и операций)
struct DoublyList{
    DoublyNode* head;
    DoublyNode* tail;
    int size;
    
    void init(); 
    void clear();

    void push_head(const std::string& val); 
    void push_tail(const std:: string& val);

    bool insert_before(const std::string& target, const std::string& val);
    bool insert_after(const std::string& target, const std::string& val);

    std::string pop_head();
    std::string pop_tail();
    bool remove_val(const std::string& val);

    bool find(const std::string& val) const;
    std::string get(int index) const;
    void print() const;   
};

#endif