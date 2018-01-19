#pragma once
#include <iomanip>

#define MIN_CAP 64

template <typename T>
class dynamic_array
{
  private:
    T *data;
    int capacity;
    int size;

  private:
    void resize();
    void copy_data(const dynamic_array &);

  public:
    dynamic_array();
    dynamic_array(const int);
    dynamic_array(const dynamic_array &);
    ~dynamic_array();
    dynamic_array &operator=(const dynamic_array &);

  public:
    T &operator[](const int);
    const T &operator[](const int) const;
    T &operator*();

  public:
    void push(const T &);
    T pop();
    void reverse();

  public:
    const int get_capacity() const;
    const int get_size() const;
};

template <typename T>
dynamic_array<T>::dynamic_array() : data(NULL), capacity(0), size(0)
{
}

template <typename T>
dynamic_array<T>::dynamic_array(const int cap) : data(NULL), capacity(cap), size(0)
{
    data = new T[cap];
    memset(data, 0, cap);
}

template <typename T>
dynamic_array<T>::dynamic_array(const dynamic_array<T> &rhs) : data(NULL), capacity(rhs.capacity), size(rhs.size)
{
    copy_data(rhs);
}

template <typename T>
dynamic_array<T>::~dynamic_array()
{
    delete[] data;
}

template <typename T>
dynamic_array<T> &dynamic_array<T>::operator=(const dynamic_array<T> &rhs)
{
    if (this != &rhs)
    {
        copy_data(rhs);
    }
    return *this;
}

//
// May throw std::bad_alloc();
// coppies the data from another dynamic_array of the same type.
//
template <typename T>
inline void dynamic_array<T>::copy_data(const dynamic_array<T> &rhs)
{
    T *temp = new T[rhs.capacity];

    for (int d = 0; d < rhs.size; ++d)
    {
        temp[d] = rhs.data[d];
    }

    delete[] data;
    data = temp;
}

template <typename T>
void dynamic_array<T>::push(const T &rhs)
{
    if (size >= capacity - 1)
        resize();

    data[size++] = rhs;
}

template <typename T>
T dynamic_array<T>::pop()
{
    T temp = data[size--];
    return temp;
}

template <typename T>
void dynamic_array<T>::reverse()
{
    T temp;
    for (int i = 0; i < size / 2; ++i)
    {
        temp = data[i];
        data[i] = data[size - 1 - i];
        data[size - 1 - i] = temp;
    }
}

//
// Makes space for more T types,
//coppies the data from the previously allocated space into the new space,
//frees the previously allocated space.
//
template <typename T>
inline void dynamic_array<T>::resize()
{
    int newCap = (capacity == 0 ? MIN_CAP : 2 * capacity);

    T *temp = new T[newCap]();
    
    for (int d = 0; d < size; ++d)
    {
        temp[d] = data[d];
    }

    delete[] data;
    data = temp;

    capacity = newCap;
}

template <typename T>
T &dynamic_array<T>::operator[](const int index)
{
    return data[index];
}

template <typename T>
const T &dynamic_array<T>::operator[](const int index) const
{
    return data[index];
}

template <typename T>
T &dynamic_array<T>::operator*()
{
    return *data;
}
template <typename T>
const int dynamic_array<T>::get_capacity() const
{
    return capacity;
}

template <typename T>
const int dynamic_array<T>::get_size() const
{
    return size;
}
