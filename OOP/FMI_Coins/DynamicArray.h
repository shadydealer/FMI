#pragma once
#include <stdio.h>
#include <stdexcept>

#define DEFAULT_SIZE 256

template <typename T>
class DynamicArray
{
  private:
    unsigned int size;
    unsigned int capacity;
    T *data;

  private:
    void Resize();

  public:
    DynamicArray();
    DynamicArray(const unsigned int);
    ~DynamicArray();

  public:
    void push_back(const T &);

  public:
    const T &operator[](const unsigned int) const;
    T &operator[](const unsigned int);

  public:
    const unsigned int get_size() const;
    const unsigned int get_capacity() const;
};

template <typename T>
DynamicArray<T>::DynamicArray() : size(0),
                                  capacity(0),
                                  data(NULL)
{
}

template <typename T>
DynamicArray<T>::DynamicArray(const unsigned int rhs_cap) : size(0),
                                                            capacity(rhs_cap),
                                                            data(new T[rhs_cap])
{
}

template <typename T>
DynamicArray<T>::~DynamicArray()
{
    delete[] data;
}

template <typename T>
void DynamicArray<T>::push_back(const T &rhs)
{
    if (size == capacity - 1 || size == 0)
        Resize();
    data[size++] = rhs;
}

template <typename T>
void DynamicArray<T>::Resize()
{
    unsigned int new_capacity = capacity == 0 ? DEFAULT_SIZE : capacity * 2;

    T *buffer = new T[new_capacity];
    memcpy(buffer, data, size * sizeof(T));

    delete[] data;
    data = buffer;

    capacity = new_capacity;
}

template <typename T>
const T &DynamicArray<T>::operator[](const unsigned int index) const
{
    if (index < size)
        return data[index];
    else
        throw std::out_of_range("Index was out of bounds of the array.\n");
}

template <typename T>
T &DynamicArray<T>::operator[](const unsigned int index)
{
    if (index < size)
        return data[index];
    else
        throw std::out_of_range("Index was out of bounds of the array.\n");
}

template <typename T>
const unsigned int DynamicArray<T>::get_size() const
{
    return size;
}

template <typename T>
const unsigned int DynamicArray<T>::get_capacity() const
{
    return capacity;
}