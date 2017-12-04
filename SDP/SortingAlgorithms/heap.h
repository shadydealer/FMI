#include <iostream>
#include "dynamic_array.h"
template <typename T>

class heap
{
private:
  dynamic_array<T> data;

private:
  void heapify(const dynamic_array<T> &);

public:
  heap();
  heap(const heap &);
  heap &operator=(const heap &);
  ~heap();

public:
  heap(const dynamic_array<T> &);

public:
  void push(const T &);
  T pop();
};

template <typename T>
heap<T>::heap() : data()
{
}

template <typename T>
heap<T>::heap(const dynamic_array<T> &rhs_data) : data()
{
  heapify(rhs_data);
}

template <typename T>
heap<T>::heap(const heap<T> &rhs) : data(rhs.data)
{
}

template <typename T>
heap<T> &heap<T>::operator=(const heap<T> &rhs)
{
  data = rhs.data;
}

template <typename T>
void heap<T>::heapify(const dynamic_array<T> &rhs)
{
  dynamic_array<T> temp(rhs.get_capacity());

  int rhs_size = rhs.get_size();
  temp.push();
  for (int el = 1; el < rhs_size; ++el)
  {

  }
}