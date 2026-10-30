#ifndef STACK_H
#define STACK_H

#include <string> 

// Структура одного динамического узла стека
struct StackNode {
    std::string val;    // Полезные данные, хранящиеся в узле
    StackNode* next;    // Указатель на следующий узел (лежащий ниже по стопке)[cite: 1]
};

// Абстрактный тип данных "Стек" (LIFO: Last In, First Out)
struct Stack {
    StackNode* top; // Указатель на верхушку стека
    int size;           

    void init();                        
    void destroy();                     
    void push(const std::string& val);  
    std::string pop();                  
    std::string peek() const;            
    void print() const;                  
};

#endif // STACK_H