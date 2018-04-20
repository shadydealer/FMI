#pragma once
#include <stdio.h>
#include <stdexcept>

#define DEFAULT_SIZE 256

template <typename T>
class DynamicArray
{
  private:
    unsigned int size;
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
                                  data(NULL)
{
}

template <typename T>
DynamicArray<T>::DynamicArray(const unsigned int rhs_cap) : size(0),
                                                            data(new T[rhs_cap])
{
}

template <typename T>
DynamicArray<T> &DynamicArray<T>::operator=(const DynamicArray<T> &rhs)
{
    if (this != &rhs)
    {

        unsigned int size = rhs.get_size();
        for (unsigned int i = 0; i < size; ++i)
            push_back(rhs[i]);
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
    resize(size + 1);
    data[size - 1] = rhs;
}

template <typename T>
void DynamicArray<T>::remove(const unsigned int index)
{
    if (index < size)
    {
        for (unsigned int i = index; i < size - 1; ++i)
            data[i] = data[i + 1];
        
        resize(size - 1);
    }
    else
        throw std::out_of_range("Index was out of bounds of the array.\n");
}

template <typename T>
void DynamicArray<T>::resize(const unsigned int new_size)
{
    T *buffer = new T[new_size];

    for (unsigned int i = 0; i < size; ++i)
        buffer[i] = data[i];

    delete[] data;
    data = buffer;

    size = new_size;
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