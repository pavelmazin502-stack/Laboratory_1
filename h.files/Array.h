#ifndef ARRAY_H
#define ARRAY_H

#include <string> 
#include <sstream>

// Структура динамического массива
struct MyArray {
    std::string* data; // Указатель на непрерывный массив строк в куче 
    int capacity;      // Сколько всего ячеек выделено в памяти
    int size;          // Сколько ячеек реально занято данными

    void init();                                       // Выделение памяти 
    void destroy();                                    // Освобождение динамической памяти через delete[]
    void resize(int new_capacity);                     // Увеличение емкости буфера при переполнении

    void push_back(const std::string& value);          // Добавление строки в конец массива (MPUSH)
    void insert(int index, const std::string& value);  // Вставка строки со сдвигом вправо (MINSERT)
    std::string get(int index) const;                  // Чтение элемента по его индексу (MGET)
    void set(int index, const std::string& value);     // Замена значения по индексу (MSET)
    void remove(int index);                            // Удаление элемента со сдвигом влево (MDEL)
    int get_size() const;                              // Возврат текущего количества элементов (MLEN)
    void print() const;                                // Красивый вывод массива в консоль (PRINT)

    std::string serialize() const;                     // Преобразование массива в строку для сохранения в файл
    void deserialize(std::istringstream& ss);          // Восстановление массива из строкового потока файла
};

#endif // ARRAY_H