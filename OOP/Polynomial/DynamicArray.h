#pragma once
#include <stdio.h>
#include <string.h> //memcpy()
#include <stdexcept>

#define DEFAULT_SIZE 256

template <class T>
class DynamicArray
{
  private:
    unsigned int size;
    unsigned int capacity;
    T *data;

  private:
    void Resize(const unsigned int);
    void _copy(T *&, const T *, const unsigned int, const unsigned int);

  public:
    DynamicArray();
    DynamicArray(const DynamicArray &);
    DynamicArray &operator=(const DynamicArray &);
    ~DynamicArray();
    DynamicArray(const unsigned int);

  public:
    void push_back(const T &);
    void remove(const unsigned int);

  public:
    const T &operator[](const unsigned int) const;
    T &operator[](const unsigned int);

  public:
    const unsigned int get_size() const;
    const unsigned int get_capacity() const;
};

template <class T>
DynamicArray<T>::DynamicArray() : size(0),
                                  capacity(0),
                                  data(NULL)
{
}

template <class T>
DynamicArray<T>::DynamicArray(const DynamicArray<T> &rhs) : DynamicArray()
{
    _copy(data, rhs.data, rhs.size, rhs.capacity);

    size = rhs.size;
    capacity = rhs.capacity;
}

template <class T>
DynamicArray<T>::DynamicArray(const unsigned int rhs_cap) : size(0),
                                                            capacity(rhs_cap),
                                                            data(new T[rhs_cap])
{
}

template <class T>
DynamicArray<T>::~DynamicArray()
{
    delete[] data;
}

template <class T>
DynamicArray<T> &DynamicArray<T>::operator=(const DynamicArray<T> &rhs)
{
    if (this != &rhs)
    {
        _copy(data, rhs.data, rhs.size, rhs.capacity);
        size = rhs.size;
        capacity = rhs.capacity;
    }
    return *this;
}

template <class T>
void DynamicArray<T>::push_back(const T &rhs)
{
    if (size == capacity - 1 || size == 0)
    {
        const unsigned int newCapacity = capacity > 0 ? capacity * 2 : DEFAULT_SIZE;
        Resize(newCapacity);
    }
    data[size++] = rhs;
}

template <class T>
void DynamicArray<T>::remove(const unsigned int index)
{
    if (index < size)
    {
        for (unsigned int i = index; i < size - 1; ++i)
            data[i] = data[i + 1];
    }
    --size;
    if (size < (capacity / 2))
        Resize(capacity / 2);
}

template <class T>
void DynamicArray<T>::_copy(T *&dest,
                            const T *src,
                            const unsigned int size,
                            const unsigned int capacity)
{
    T *buffer = new T[capacity];
    memcpy(buffer, src, size * sizeof(T));

    delete[] dest;
    dest = buffer;
}

template <class T>
void DynamicArray<T>::Resize(const unsigned int newCap)
{
    _copy(data, data, size, newCap);

    capacity = newCap;
}

template <class T>
const T &DynamicArray<T>::operator[](const unsigned int index) const
{
    if (index < size)
        return data[index];
    else
        throw std::out_of_range("Index was out of bounds of the array.\n");
}

template <class T>
T &DynamicArray<T>::operator[](const unsigned int index)
{
    if (index < size)
        return data[index];
    else
        throw std::out_of_range("Index was out of bounds of the array.\n");
}

template <class T>
const unsigned int DynamicArray<T>::get_size() const
{
    return size;
}

template <class T>
const unsigned int DynamicArray<T>::get_capacity() const
{
    return capacity;
}

