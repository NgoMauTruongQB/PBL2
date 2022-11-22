#pragma once
#include <string>
using namespace std;

template <typename T>
class vector
{
    private:
        int Size;
        int capacity; // chứa dung lượng tối đa của vector
        T *array;
        void capacityUp(int newCapacity); // tăng số lượng phần tử của vector
    public:
        vector(int = 0);
        ~vector();
        vector& operator= (vector &vt); 
        int size(); // trả về số lượng phần tử được sử dụng trong vector
        bool empty(); // Trả về dữ liệu vùng chứa có trống hay không, nếu trống thì trả về True, nếu có phần tử thì trả về False
        T& operator[] (const int index); 
        T& at(int index); // tương tự như đa năng hóa toán tử truy cập
        void push_back(T value); // them phần tử vao cuoi vector
        void pop_back(); // xoá phần tử ở cuối vector
        void insert(int position,T value); // chèn phần tử value có kiểu dữ liệu T vào vị trí position
        void erase(int pos); // xoá phần tử ở vị trí pos
        void clear(); // loại bỏ tất cả các phần tử của vùng chứa vector.
        T* data(); // trả về con trỏ trực tiếp đến memory array được sử dụng bên trong vector để lưu trữ các thành phần của nó
};

template <typename T>
void vector<T>::capacityUp(int newCapacity)
{
    if(newCapacity <= this->Size)
        return;
    T *oldArray = this->array; 
    this->array = new T[newCapacity]; 
    for(int i = 0; i < this->Size; i++)
        this->array[i] = oldArray[i]; 
    delete[] oldArray;
    this->capacity = newCapacity;
}

template <typename T>
vector<T>::vector(int inputCapacity ) 
{
    this->Size = 0;
    this->capacity = inputCapacity;
    this->array = new T[capacity]; 
}

template <typename T>
vector<T>::~vector()
{
    delete[] this->array; 
}

template <typename T>
vector<T>& vector<T>::operator=(vector &vt)
{
    int temp = vt.Size;
    if (this->Size > temp)
    {
        for (int i = temp; i < this->Size; i++)
        {
            delete (this->array + i);
        }
    }
    for (int i = 0; i < temp; ++i)
    {
        this->array[i] = vt[i];
    }
    this->Size = temp;
    return (*this);
}

template <typename T>
int vector<T>::size()
{
    return this->Size;
}

template <typename T>
bool vector<T>::empty()
{
    return (this->Size == 0);
}

template <typename T>
T & vector<T>::operator[](const int index)
{
    if (index > this->Size || index < 0)
    {
        static T temp;
        return temp;
    }
    return *(this->array + index);
}

template <typename T>
T & vector<T>::at(int index)
{
    if (index > this->Size || index < 0)
    {
        static T temp;
        return temp;
    }
    return *(this->array + index);
}
template <typename T>
void vector<T>::push_back(T value)
{
    if(this->Size == this->capacity)
        capacityUp(2 * this->Size);
    T* temp = new T[++this->Size];
    for (int i = 0; i < this->Size - 1; ++i)
    {
        temp[i] = this->array[i];
    }
    temp[this->Size - 1] = value;
    delete[] this->array;
    this->array = temp;
}

template <typename T>
void vector<T>::pop_back()
{
    if(!this->empty())
    {
        delete (this->array + this->Size - 1);
        this->Size--;
    }
}

template <typename T>
void vector<T>::insert(int position, T value)
{
    if(this->Size == this->capacity)
        capacityUp(2 * this->Size);
    T* temp = new T[++this->Size];
    for (int i = 0; i < position; i++)
    {
        temp[i] = this->array[i];
    }
    temp[position] = value;
    for (int i = position + 1; i < this->Size; i++)
    {
        temp[i] = this->array[i - 1];
    }
    delete[] this->array;
    this->array = temp;
}

template <typename T>
void vector<T>::erase(int pos)
{
    if (!this->empty() && pos >= 0 && pos < this->Size)
    {
        for(int i = pos; i < this->Size - 1; i++)
            this->array[i] = this->array[i + 1];
        delete (this->array + this->Size - 1);
        this->Size--;
    }
}
template <typename T>
void vector<T>::clear()
{
    this->Size = 0;
}

template <typename T>
T* vector<T>::data()
{
    return array;
}