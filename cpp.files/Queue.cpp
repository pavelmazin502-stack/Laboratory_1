#include "../h.files/Queue.h"
#include <iostream>

using namespace std;

// Инициализация узла очереди
void Queue::init(){
    head = nullptr;
    tail = nullptr;
    size = 0;
}

void Queue::destroy(){
    QueueNode* curr = head; // Указатель на 1 элемент в списке

    while (curr != nullptr){
        QueueNode* next_node = curr->next;
        delete curr;
        curr = next_node;
    }
    head = nullptr;
    tail = nullptr;
    size = 0;
}

void Queue::push(const string& val){
    QueueNode* node = new QueueNode; // Выделили память
    node->val = val;
    node->next = nullptr;

    if (tail == nullptr){
        head = node; 
        tail = node;
    } else {
        tail -> next = node;
        tail = node;
    }
    size++;
}
// Извлечение из начала очереди FIFO
string Queue::pop() {
    if (head == nullptr) {
        return ""; // Очередь пуста
    }

    QueueNode* temp = head;
    string val = temp->val;

    head = head->next;
    if (head == nullptr) {
        // Если извлекли последний элемент, очередь опустела
        tail = nullptr;
    }

    delete temp;
    size--;
    return val;
}

// Просмотр первого элемента без его удаления
string Queue::peek() const {
    if (head == nullptr) {
        return "";
    }
    return head->val;
}

// Вывод содержимого очереди от головы к хвосту
void Queue::print() const {
    QueueNode* curr = head;
    cout << "Начало -> [";
    while (curr != nullptr) {
        cout << curr->val;
        if (curr->next != nullptr) {
            cout << " <- ";
        }
        curr = curr->next;
    }
    cout << "] <- Конец\n";
}