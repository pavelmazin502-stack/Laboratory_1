#include "../h.files/Array.h"
#include <iostream>

using namespace std;

void MyArray::init(){
    capacity = 4; // Размер ячеек памяти
    size = 0;
    data = new std::string[capacity];
}

void MyArray::destroy(){
    delete [] data;
    data = nullptr;
    size = 0;
    capacity = 0;
}

// Увеличение размера и  буфера памяти, копирования старых элементов в новый "улучшенный массив"
void MyArray::resize(int new_capacity){
    string* new_data = new string[capacity];

    for (int i = 0; i <= size - 1; ++i){
        new_data[i] = data[i];
    }
    delete[] data;

    data = new_data;
    capacity = new_capacity;
}

void MyArray::push_back(const string& value){
    if (size == capacity){
        int new_capacity = capacity * 2;
        resize(new_capacity);
    }
    data[size] = value;
    size++;
}

void MyArray::insert(int index, const string& value){
    if (index < 0 || index > size){
        cout << "Ошибка индекс вне диапазона" << endl;
        return;
    }
    if (size == capacity){
        int new_capacity = capacity * 2;
        resize(new_capacity);
    }
    for (int i = size; i > index; i--){
        data[i] = data[i-1];
    }
    data[index] = value;
    size++;
}

void MyArray::remove(int index){
    if (index < 0 || index >= size){
        cout << "Ошибка - некорректный индекс" << endl;
        return;
    }
    for (int i = index; i < size-1; i++){
        data[i] = data[i+1];

    }
    size--; 
}

string MyArray::get(int index) const{
    if (index < 0 || index >= size){
        return "";
    }
    return data[index];
}

void MyArray::set(int index, const string& value) {
    if (index < 0 || index >= size) {
        return;
    }
    data[index] = value;
}

int MyArray::get_size() const{
    return size; 
}
void MyArray::print() const{
    cout << "[";
    for (int i = 0; i < size; ++i){
        cout << data[i];
        if (i < size - 1){
            cout << ", ";
        }
    }
    cout << "]\n";
}

string MyArray::serialize() const {
    ostringstream ss;                                 // Создаем строковый поток
    ss << size;                                            // Первым пишем размер массива
    for (int i = 0; i < size; ++i) {                       // Перебираем элементы
        ss << " " << data[i];                              // Записываем их через пробел
    }
    return ss.str();                                       // Возвращаем итоговую строку
}

// Десериализация из файла
void MyArray::deserialize(istringstream& ss) {
    int count = 0;                                         // Переменная под считывание размера
    if (ss >> count) {                                     // Считываем количество элементов
        destroy();                                         // Очищаем старую память, если она была
        capacity = (count > 4) ? count * 2 : 4;            // Выделяем емкость с запасом
        data = new string[capacity];                  // Создаем массив в куче
        size = 0;                                          // Обнуляем счетчик
        for (int i = 0; i < count; ++i) {                  // Считываем заявленное число элементов
            string val;
            ss >> val;                                     // Читаем очередное значение
            data[size++] = val;                            // Записываем в массив
        }
    }
}

