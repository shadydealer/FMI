#include <stdio.h>
#include <stdexcept>

#define DEFAULT_SIZE 256

template <typename T>
class Dynamic_Array
{
  private:
    unsigned int size;
    unsigned int capacity;
    T *data;

  private:
    void Resize();

  public:
    Dynamic_Array();
    Dynamic_Array(const unsigned int);
    ~Dynamic_Array();

  public:
    void push_back(const T &);

  public:
    const T &operator[](const unsigned int) const;

  public:
    const unsigned int get_size() const;
    const unsigned int get_capacity() const;
};

template <typename T>
Dynamic_Array<T>::Dynamic_Array() : size(0),
                                    capacity(0),
                                    data(NULL)
{
}

template <typename T>
Dynamic_Array<T>::Dynamic_Array(const unsigned int rhs_cap) : size(0),
                                                              capacity(rhs_cap),
                                                              data(new T[rhs_cap])
{
}

template <typename T>
Dynamic_Array<T>::~Dynamic_Array()
{
    delete[] data;
}

template <typename T>
void Dynamic_Array<T>::push_back(const T &rhs)
{
    if ( capacity == 0 || size == capacity - 1)
        Resize();
    data[size++] = rhs;
}

template <typename T>
void Dynamic_Array<T>::Resize()
{
    unsigned int new_capacity = capacity == 0 ? DEFAULT_SIZE : capacity*2;

    T * buffer = new T[new_capacity];
    memcpy(buffer,data, size);

    delete[] data;
    data = buffer;

    capacity = new_capacity;
}


template <typename T>
const T& Dynamic_Array<T>::operator[](const unsigned int index) const
{
    if(index < size)
        return data[index];
    else
        throw std::out_of_range("Index was out of bounds of the array.\n");
}

template <typename T>
const unsigned int Dynamic_Array<T>::get_size() const
{
    return size;
}

template <typename T>
const unsigned int Dynamic_Array<T>::get_capacity() const
{
    return capacity;
}