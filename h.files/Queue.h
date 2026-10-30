#ifndef QUEUE_H
#define QUEUE_H

#include <string>

// Метод FIFO первым пришел, первым ушел

// Узел очереди
struct QueueNode{
    std::string val; // Значение узла
    QueueNode* next; // Следующий элемент в очереди
};

struct Queue{
    QueueNode* head; // Начало (отсюда извлекаем)
    QueueNode* tail;
    int size;

    
    void init();
    void destroy();
    void push(const std::string& val);
    std:: string pop();
    std:: string peek() const;
    void print() const;
};

#endif