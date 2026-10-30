#include "../h.files/SinglyList.h"
#include <iostream>                

using namespace std;


// Инициализация пустого списка
void SinglyList::init(){
    head = nullptr;
    tail = nullptr;
    size = 0;
}
// Добавление в голову
void SinglyList::push_head(const string& val){
    SinglyNode* node = new SinglyNode;
    node -> val = val;
    node -> next = head;
    
    head = node;
    if (tail == nullptr){
        tail = node; // Хвост указывает на этот же узел
    }
    size++;
}
// Добавление в хвост
void SinglyList::push_tail(const string& val){
    SinglyNode* node = new SinglyNode;
    node->val = val;
    node -> next = nullptr; // Конец

    if (tail == nullptr){
        head = node;
        tail = node;
    } else {
        tail->next = node;
        tail = node;
    }
    size++;
}

bool SinglyList::insert_after(const string& target, const string&val){
    SinglyNode* curr = head; // Указатель для поиска
    while (curr != nullptr && curr->val != target){ // Пока не найдем элемент
        curr = curr -> next;
    }
    if (curr == nullptr){
        return false;
    }
    SinglyNode* node = new SinglyNode; // Создаем новый узел, который будем добавлять
    node->val = val;

    node->next = curr->next;
    curr->next = node;

    // Если вставили после старого хвоста — обновляем tail:
    if (curr == tail) {
        tail = node;
    }

    size++;
    return true;
}

// Односвязный список умеет смотреть только вперед. Возвращаться назад нельзя
bool SinglyList::insert_before(const std::string& target, const std::string& val){
    if (head == nullptr){
        return false;
    }
    // Если target лежит прямо в голове:
    if (head->val == target) {
        push_head(val);
        return true;
    }

    // Ищем предшественника целевого узла:
    SinglyNode* curr = head;
    while (curr->next != nullptr && curr->next->val != target) {
        curr = curr->next;
    }

    // Если следующего узла нет — target в списке не найден:
    if (curr->next == nullptr) {
        return false;
    }

    // Создаем узел и связываем:
    SinglyNode* node = new SinglyNode;
    node->val = val;
    node->next = curr->next;
    curr->next = node;

    size++;
    return true;
}

// Удаление из головы
string SinglyList::pop_head(){
    if (head == nullptr){
        return "";
    }
    SinglyNode* temp = head;
    string res = temp -> val;
    head = head ->next;

    if (head == nullptr){
        tail = nullptr;
    }

    delete temp;
    size--;

    return res;
}

string SinglyList::pop_tail() {
    if (head == nullptr) {                   
        return "";                           
    }

    if (head == tail) {                      
        return pop_head();                   
    }

    // Ищем предпоследний узел (у которого next указывает на tail)
    SinglyNode* curr = head;                 
    while (curr->next != tail) {            
        curr = curr->next;                   // Шагаем вперед[cite: 1]
    }

    string val = tail->val;                  
    delete tail;                             // Освобождаем память старого хвоста[cite: 1]

    tail = curr;                             
    tail->next = nullptr;                    
    size--;                                 
    return val;                              
}

void SinglyList::clear(){
    SinglyNode* curr = head;

    while (curr != nullptr){
        SinglyNode* next_node = curr -> next; 
        delete curr;
        curr = next_node; 
    }
    head = nullptr;
    tail = nullptr;
    size = 0;
}

bool SinglyList::remove_val(const string& val){
    if (head == nullptr){
        return false;
    }
    if (head -> val == val){ // Удаление из головы 
        pop_head();
        return true;
    }
    SinglyNode* curr = head;
    while (curr -> next != nullptr && curr->next->val != val){
        curr = curr->next; 
    }

    if (curr->next == nullptr){
        return false; 
    }
    SinglyNode* to_delete = curr->next;
    curr->next = to_delete->next;

    if (to_delete == tail) {
        tail = curr;
    }
    delete to_delete;
    size--;
    return true;
}

bool SinglyList::find(const string& val) const {
    SinglyNode* curr = head;               
    while (curr != nullptr) {              
        if (curr->val == val) {              
            return true;
        }                     
        curr = curr->next;
    }                   
    return false;                            
}
// Получение значения по индексу 
string SinglyList::get(int index) const {
    if (index < 0 || index >= size) {        
        return "";                          
    }

    SinglyNode* curr = head;                 
    for (int i = 0; i < index; ++i) {        
        curr = curr->next;
    }
    return curr->val;                        
}

// Форматированный вывод элементов списка в консоль
void SinglyList::print() const {
    SinglyNode* curr = head;               
    cout << "[";                             
    while (curr != nullptr) {                
        cout << curr->val;                   
        if (curr->next != nullptr) {         
            cout << " -> ";                 
        }
        curr = curr->next;                   
    }
    cout << "]\n";                         
}