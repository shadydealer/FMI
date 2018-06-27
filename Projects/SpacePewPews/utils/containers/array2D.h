#pragma once

#include <cstring> //memcpy()
#include <iostream>
#include <stdexcept> //std::out_of_range(), exception

template <class C>
class array2D
{
private:
  int width, height;
  C **data;

private:
#pragma region Memory Management
  C **allocate_memory(const int,
                      const int);
  void free_memory();
#pragma endregion

public:
#pragma region Big Four
  array2D();
  array2D(const array2D &);
  array2D &operator=(const array2D &);
  ~array2D();
#pragma endregion

public:
  array2D(const int, const int);
  array2D(const int,
          const int,
          const C *const *);

public:
  void copy_data(const int,
                 const int,
                 const C *const *);

public:
  void print() const;

public:
  C *operator[](const int);

public:
#pragma region Getters
  int get_height() const;
  int get_width() const;
#pragma endregion
};

#pragma region Big Four
template <class C>
array2D<C>::array2D() : width(0),
                        height(0),
                        data(nullptr)
{
}

template <class C>
array2D<C>::array2D(const array2D &rhs) : array2D()
{
  copy_data(rhs.height, rhs.width, rhs.data);
}

template <class C>
array2D<C> &array2D<C>::operator=(const array2D &rhs)
{
  if (this != &rhs)
    copy_data(rhs.height, rhs.width, rhs.data);

  return *this;
}

template <class C>
array2D<C>::~array2D()
{
  free_memory();
}
#pragma endregion

template <class C>
array2D<C>::array2D(const int rhsWidth,
                    const int rhsHeight) : width(rhsWidth),
                                           height(rhsHeight),
                                           data(nullptr)
{
  data = allocate_memory(height, width);
}

template <class C>
array2D<C>::array2D(const int rhsWidth,
                    const int rhsHeight,
                    const C *const *rhsData) : width(rhsWidth),
                                               height(rhsHeight),
                                               data(nullptr)
{
  copy_data(rhsHeight, rhsWidth, rhsData);
}

#pragma region Memory Management
/*
    Allocates (rhsHeight * rhsWidth) * sizeof(C) bytes.
 */
template <class C>
C **array2D<C>::allocate_memory(const int rhsHeight,
                                const int rhsWidth)
{

  C **temp = new C *[rhsHeight];
  for (unsigned int r = 0; r < rhsHeight; ++r)
    temp[r] = new C[rhsWidth]{};

  return temp;
}

/*
    Frees the memory pointed to by the data pointer.
 */
template <class C>
void array2D<C>::free_memory()
{
  for (unsigned int r = 0; r < height; ++r)
    delete[] data[r];

  delete[] data;
}
#pragma endregion

template <class C>
void array2D<C>::copy_data(const int rhsHeight,
                           const int rhsWidth,
                           const C *const *rhsData)
{
  C **temp = allocate_memory(rhsHeight, rhsWidth);

  for (unsigned int r = 0; r < rhsHeight; ++r)
    memcpy(temp[r], rhsData[r], rhsWidth * (sizeof(C)));

  free_memory();

  data = temp;

  width = rhsWidth;
  height = rhsHeight;
}

template <class C>
C *array2D<C>::operator[](const int row)
{
  if ((row >= 0 && row < height))
    return data[row];

  throw std::out_of_range("Row index out of range.");
}

#pragma region Getters
template <class C>
int array2D<C>::get_height() const
{
  return height;
}

template <class C>
int array2D<C>::get_width() const
{
  return width;
}
#pragma endregion

/*
  Prints the 2D array to the console window.
  
  The class C has to have a redifined operator<<.
 */
template <class C>
void array2D<C>::print() const
{
  for (unsigned int r = 0; r < height; ++r)
  {
    for (unsigned int c = 0; c < width; ++c)
      std::cout << data[r][c];
    if (r < height - 1)
      std::cout << "\n";
  }
}