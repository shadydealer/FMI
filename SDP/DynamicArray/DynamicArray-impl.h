#pragma once
#include <iostream>

//
// Default ctor.
//
template <typename T>
DynamicArray<T>::DynamicArray(): elements(NULL), capacity(0), size(0)
{}
//
// Single parameter ctor.
//
template <typename T>
DynamicArray<T>::DynamicArray(const size_t rhsCap): elements(NULL), capacity(rhsCap), size(0)
{
    elements = new T[capacity];     
}

//
// Dtor.
//
template <typename T>
DynamicArray<T>::~DynamicArray()
{
    delete[] elements;
}

//
// Copy ctor.
//
template <typename T>
DynamicArray<T>::DynamicArray(const DynamicArray<T> & rhs): DynamicArray()
{   
    CopyFrom(rhs);
}

//
// Assignment operator.
//
template <typename T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray<T>& rhs)
{
    if(this != &rhs)
    {
        CopyFrom(rhs);
    }
    return *this;
}
//
// Coppies the elements and the arrays dimensions.
// May throw std::bad_alloc();
//
template <typename T>
void DynamicArray<T>::CopyFrom(const DynamicArray<T> &rhs)
{
    T * buffer = new T[rhs.capacity];

    for(size_t e = 0; e < rhs.size; ++e)
    {
        buffer[e] = rhs.elements[e];
    }

    delete[] elements;
    elements = buffer;

    capacity = rhs.capacity;
    size = rhs.size;
}


//
// operator +=
//
template <typename T>
DynamicArray<T> & DynamicArray<T>::operator+=(const T& rhs)
{
    printf("Attempting to add a new element...\n");

    if(size == capacity)
        Resize();
    elements[size] = rhs;
    ++size;

    printf("Successfully added a new element! New size = %zu\n", size);
}

//
// operator +
//
template <typename T>
DynamicArray<T> DynamicArray<T>::operator+(const T &rhs) const
{
    DynamicArray<T> buffer(*this);

    buffer += rhs;
    return buffer;
    
}

//
// const operator[]
//
template <typename T>
const T& DynamicArray<T>::operator[](const size_t index) const 
{
    if(index >= size)
        throw "Index was out of bounds of the array.";
    return elements[index];
}
//
// operator[]
//
template <typename T>
T& DynamicArray<T>::operator[](const size_t index)
{
    if(index >= size)
        throw "Index was out of bounds of the array.";
    return elements[index];
}

//
// Resizes the array in order to fit in additional elements.
//
template <typename T>
void DynamicArray<T>::Resize()
{
    printf("Attempting to resize the array...\n");

    size_t newCap = capacity;
    capacity == 0 ? ++newCap : newCap *=2;

    CopyFrom(*this);
    capacity = newCap;

    printf("Successfully resized the array! New capacity = %zu\n", capacity);
    
}

//
// Capacity getter method.
//
template <typename T>
const size_t DynamicArray<T>::Capacity() const
{
    return capacity;
}

//
// Size getter method.
//
template <typename T>
const size_t DynamicArray<T>::Size() const
{
    return size;
}

//
// Default ctor for the DynamicArray's iterator.
//

template <typename T>
DynamicArray<T>::iterator::iterator(): data(*this)
{

}

template <typename T>
DynamicArray<T>::iterator::~iterator()
{
    delete data;
}