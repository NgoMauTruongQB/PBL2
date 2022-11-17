#include <iostream>
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
        vector(int = 100);
        ~vector();
        vector& operator= (vector &vt); 
        int size(); // trả về số lượng phần tử được sử dụng trong vector
        bool empty(); // Trả về dữ liệu vùng chứa có trống hay không, nếu trống thì trả về True, nếu có phần tử thì trả về False
        T& operator[] (int index); 
        void push_back(T value); // them phần tử vao cuoi vector
        void pop_back(); // xoá phần tử ở cuối vector
        void insert(int position,T value); // chèn phần tử value có kiểu dữ liệu T vào vị trí position
        void erase(int pos); // xoá phần tử ở vị trí pos
        void clear(); // loại bỏ tất cả các phần tử của vùng chứa vector.
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
vector<T> & vector<T>::operator=(vector & vt)
{
    if(this != vt)
    {
        delete[] this->array;
        this->Size = vt.Size;
        this->capacity = vt.capacity;
        this->array = new T[capacity];
    }
    for(int i = 0; i < this->Size; i++)
    {
        this->array[i] = vt.array[i];
    }
    return *this; // tra ve vector ve trai sao khi gan xong
}

template <typename T>
int vector<T>::size()
{
    return this->Size;
}

template <typename T>
bool vector<T>::empty()
{
    if(this->Size == 0)
        return 1;
    return 0;
}

template <typename T>
T & vector<T>::operator[](int index)
{
    return this->array[index];
}

template <typename T>
void vector<T>::push_back(T value)
{
    if(this->Size == this->capacity)
        capacityUp(2 * this->Size);
    this->array[this->Size] = value;
    this->Size++;
}

template <typename T>
void vector<T>::pop_back()
{
    size--;
}

template <typename T>
void vector<T>::insert(int position,T value)
{
    if(this->Size == this->capacity)
        capacityUp(2 * this->Size);
    for(int i = this->Size; i > position; i--)
        this->array[i] = this->array[i - 1];
    this->array[position] = value;
    this->Size++;
}

template <typename T>
void vector<T>::erase(int pos)
{
    for(int i = pos; i < this->Size - 1; i++)
        this->array[i] = this->array[i + 1];
    this->Size--;
}

template <typename T>
void vector<T>::clear()
{
    this->Size = 0;
}