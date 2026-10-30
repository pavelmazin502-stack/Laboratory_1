// Вершина top
#include "../h.files/Stack.h" 
#include <iostream>          

using namespace std;

// Инициализация пустого стека: обнуляем вершину и счетчик
void Stack::init() {
    top = nullptr; 
    size = 0;       
}

// Очистка памяти: последовательно удаляем узлы сверху вниз
void Stack::destroy() {
    StackNode* curr = top;                  
    while (curr != nullptr) {               
        StackNode* next_node = curr->next;  // Запоминаем узел уровнем ниже
        delete curr;                        // Удаляем текущий узел из кучи
        curr = next_node;                   // Спускаемся на уровень ниже
    }
    top = nullptr;                          
    size = 0;                               
}

// Добавление элемента на вершину стека 
void Stack::push(const string& val) {
    StackNode* node = new StackNode; 
    node->val = val;                 
    node->next = top;              
    top = node;                      
    size++;                          
}

// Снятие элемента с вершины стека
string Stack::pop() {
    if (top == nullptr) {            
        return "";                   
    }

    StackNode* temp = top;           // Запоминаем узел на вершине
    string val = temp->val;          // Сохраняем значение перед удалением[cite: 1]

    top = top->next;                
    delete temp;                     
    size--;                          
    return val;                      
}

// Просмотр значения верхнего элемента без его снятия
string Stack::peek() const {
    if (top == nullptr) {            
        return "";
    }
    return top->val;                 // Возвращаем значение с вершины
}

// Вывод
void Stack::print() const {
    StackNode* curr = top;         
    cout << "Вершина -> [";
    while (curr != nullptr) {        
        cout << curr->val;           
        if (curr->next != nullptr) {
            cout << " | ";           // Разделитель между слоями стопки
        }
        curr = curr->next;           // Переходим к следующему элементу
    }
    cout << "] <- Дно\n";
}