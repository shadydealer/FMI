#pragma once
#include <stdio.h>
#include <stdexcept>

#define DEFAULT_SIZE 256

template <typename T>
class DynamicArray
{
  private:
    unsigned int size;
    unsigned int length;
    T *data;

  private:
    void resize(const unsigned int);

  public:
    DynamicArray();
    DynamicArray(const unsigned int);
    DynamicArray &operator=(const DynamicArray &);
    ~DynamicArray();

  public:
    void push_back(const T &);
    void remove(const unsigned int);

  public:
    const T &operator[](const unsigned int) const;
    T &operator[](const unsigned int);

  public:
    const unsigned int get_size() const;
};

template <typename T>
DynamicArray<T>::DynamicArray() : size(0),
                                  length(2),
                                  data(new T[length])
{
}

template <typename T>
DynamicArray<T>::DynamicArray(const unsigned int rhs_cap) : size(0),
                                                            length(rhs_cap),
                                                            data(new T[rhs_cap])
{
}

template <typename T>
DynamicArray<T> &DynamicArray<T>::operator=(const DynamicArray<T> &rhs)
{
    if (this != &rhs)
    {
        unsigned int newLen = rhs.length;
        T *temp = new T[newLen];

        for (unsigned int i = 0; i < rhs.size; ++i)
            temp[i] = rhs.data[i];

        delete[] data;
        data = temp;

        length = rhs.length;
        size = rhs.size;
    }
    return *this;
}

template <typename T>
DynamicArray<T>::~DynamicArray()
{
    delete[] data;
}

template <typename T>
void DynamicArray<T>::push_back(const T &rhs)
{
    if (size == length - 1)
    {
        unsigned int newLength = length == 0 ? 2 : length * 2;
        resize(newLength);
    }
    data[size++] = rhs;
}

template <typename T>
void DynamicArray<T>::remove(const unsigned int index)
{
    if (index < size)
    {
        for (unsigned int i = index; i < size - 1; ++i)
            data[i] = data[i + 1];

        if (size < length / 2)
            resize(length / 2);
    }
    else
        throw std::out_of_range("Index was out of bounds of the array.\n");
}

template <typename T>
void DynamicArray<T>::resize(const unsigned int newLength)
{
    T *buffer = new T[newLength];

    for (unsigned int i = 0; i < size; ++i)
        buffer[i] = data[i];

    delete[] data;
    data = buffer;

    length = newLength;
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