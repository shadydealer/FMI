#pragma once
#include "iostream"

template <typename T>
class DynamicArray
{
  private:
    T *elements;
    size_t capacity;
    size_t size;

  public:
    DynamicArray();
    DynamicArray(const size_t);
    DynamicArray(const DynamicArray<T> &);
    DynamicArray<T> &operator=(const DynamicArray<T> &);
    ~DynamicArray();

  public:
    DynamicArray<T> &operator+=(const T &);
    DynamicArray<T> operator+(const T&) const;
    T&              operator[](const size_t);
    const T&        operator[](const size_t) const;
  public:
    void CopyFrom(const DynamicArray<T> &);
    void Resize();

  public:
    const size_t Capacity() const;
    const size_t Size() const;
};

template <typename T>
class iterator
{
  private:
    DynamicArray<T> * data;

  public:
    iterator();
    ~iterator();
};

#include "DynamicArray-impl.h"