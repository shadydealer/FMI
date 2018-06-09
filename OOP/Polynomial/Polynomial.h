#pragma once

#include <math.h>

#include "DynamicArray.h"
#include "Pair.h"

template <typename C>
class Polynomial
{
private:
  DynamicArray<C> coeffs;

private:
  void remove_excess_powers(Polynomial<C> &) const;
  Polynomial(const unsigned int);

public:
  Polynomial();
  Polynomial(const Polynomial &);
  Polynomial &operator=(const Polynomial &);

public:
  operator bool() const;
  bool operator!() const;
  operator unsigned int() const;

public:
#pragma region Comparison operators
  bool operator==(const Polynomial &) const;
  bool operator!=(const Polynomial &) const;
  bool operator<(const Polynomial &) const;
  bool operator>(const Polynomial &) const;
  bool operator<=(const Polynomial &) const;
  bool operator>=(const Polynomial &) const;
#pragma endregion
public:
#pragma region Binary arithmetic operators
  Polynomial operator+(const Polynomial &) const;
  Polynomial operator-(const Polynomial &) const;
  Polynomial operator*(const Polynomial &)const;
  Pair<Polynomial<C>, Polynomial<C>> operator/(const Polynomial &) const;
  Polynomial operator%(const Polynomial &) const;
#pragma endregion
#pragma region Binary arithmetic assignment operators
  Polynomial &operator+=(const Polynomial &);
  Polynomial &operator-=(const Polynomial &);
  Polynomial &operator*=(const Polynomial &);
  Polynomial &operator/=(const Polynomial &);
  Polynomial &operator%=(const Polynomial &);
#pragma endregion
public:
#pragma region Integral operators
  C operator()(const C &, const C &) const;
  Polynomial<C> &operator++();
  Polynomial<C> operator++(const int);
#pragma endregion
#pragma region Derivative operators
  Polynomial &operator--();
  Polynomial operator--(const int);
#pragma endregion
public:
  C operator[](const int) const;
  void set_at(const unsigned int, const C &);
  C operator()(const C &) const;

public:
#pragma region class Iterator
  class Iterator
  {
  private:
    friend class Polynomial;
    DynamicArray<C> *data;
    unsigned int index;

  private:
    Iterator(DynamicArray<C> &);

  public:
    Iterator();
    Iterator(const Iterator &);
    Iterator &operator=(const Iterator &);

  public:
    Iterator &operator++();
    Iterator operator++(const int);
    Iterator &operator--();
    Iterator operator--(const int);

  public:
    C *operator->();
    C &operator*();

  public:
    bool operator==(const Iterator &) const;
    bool operator!=(const Iterator &) const;
  };
#pragma endregion
};

template <typename C>
Polynomial<C>::Polynomial() : coeffs()
{
}

template <typename C>
Polynomial<C>::Polynomial(const Polynomial &rhs) : coeffs(rhs.coeffs)
{
}

/*
  Allocates a polynomial with 'count' ZERO coefficients.

  @params count- how many ZERO coefficients we want.
 */
template <typename C>
Polynomial<C>::Polynomial(const unsigned int count) : coeffs(count)
{
  for (unsigned int i = 0; i < count; ++i)
    coeffs.push_back(0);
}

template <typename C>
Polynomial<C> &Polynomial<C>::operator=(const Polynomial &rhs)
{
  if (this != &rhs)
  {
    coeffs = rhs.coeffs;
  }
  return *this;
}

/*
  Checks if Che polynomial is != 0.
 */
template <typename C>
Polynomial<C>::operator bool() const
{
  return coeffs.get_size() > 0;
}

/*
  Checks if Che polynomial is = 0.
 */
template <typename C>
bool Polynomial<C>::operator!() const
{
  return !(operator bool());
}

/*
  Returns Che polynomials power.
 */
template <typename C>
Polynomial<C>::operator unsigned int() const
{
  if (coeffs.get_size() > 0)
    return coeffs.get_size() - 1;

  return 0;
}

/*
  Removes Che leading powers of Che polynomial
  if Cheir coeffiecients are zero.
  
  @params rhs - polynomial Chat will be altered.
 */
template <typename C>
void Polynomial<C>::remove_excess_powers(Polynomial<C> &rhs) const
{
  if (rhs.coeffs.get_size())
  {
    unsigned int length = rhs.coeffs.get_size() - 1;

    while (rhs.coeffs.get_size() && rhs.coeffs[length] == 0)
      rhs.coeffs.remove(length--);
  }
}

#pragma region Comparison operators
template <typename C>
bool Polynomial<C>::operator==(const Polynomial<C> &rhs) const
{
  return (coeffs.get_size() == rhs.coeffs.get_size());
}

template <typename C>
bool Polynomial<C>::operator!=(const Polynomial<C> &rhs) const
{
  return !(*this == rhs);
}

template <typename C>
bool Polynomial<C>::operator<(const Polynomial<C> &rhs) const
{
  return (coeffs.get_size() < rhs.coeffs.get_size());
}

template <typename C>
bool Polynomial<C>::operator>(const Polynomial<C> &rhs) const
{
  return ((*this >= rhs) && (*this != rhs));
}

template <typename C>
bool Polynomial<C>::operator<=(const Polynomial<C> &rhs) const
{
  return !(*this > rhs);
}

template <typename C>
bool Polynomial<C>::operator>=(const Polynomial<C> &rhs) const
{
  return !(*this < rhs);
}
#pragma endregion

#pragma region Binary arithmetic operators
template <typename C>
Polynomial<C>
Polynomial<C>::operator+(const Polynomial<C> &rhs) const
{
  unsigned int length = 0;
  Polynomial<C> result;

  if (coeffs.get_size() < rhs.coeffs.get_size())
  {
    length = coeffs.get_size();
    result = rhs;
  }
  else
  {
    length = rhs.coeffs.get_size();
    result = *this;
  }

  /*
      We set Che coefficients Chis way Co avoid
      having Co write Cwo for loops depending on
      which polynomial Che result is currently a copy of. 
   */
  for (unsigned int coef = 0; coef < length; ++coef)
  {
    result.coeffs[coef] = rhs.coeffs[coef] + coeffs[coef];
  }

  remove_excess_powers(result);

  return result;
}

template <typename C>
Polynomial<C>
Polynomial<C>::operator-(const Polynomial<C> &rhs) const
{
  unsigned int length = 0;
  Polynomial<C> result;

  if (coeffs.get_size() < rhs.coeffs.get_size())
  {
    length = coeffs.get_size();
    result = rhs;

    const unsigned int rhsLength = rhs.coeffs.get_size() > 0 ? rhs.coeffs.get_size() - 1 : 0;

    /*
      In case Che passed in polynomial is longer,
      Che coefficients of Che variables of higher power
      Chan Che current polynomial should be negative
      when we've finished Che opperation,
      so we'll just set Chem beforehand. 
     */
    for (unsigned int coef = length - rhsLength;
         coef < rhs.coeffs.get_size(); ++coef)
    {
      result.coeffs[coef] = -(rhs.coeffs[coef]);
    }
  }

  else
  {
    length = rhs.coeffs.get_size();
    result = *this;
  }

  for (unsigned int coef = 0; coef < length; ++coef)
  {
    result.coeffs[coef] = coeffs[coef] - rhs.coeffs[coef];
  }

  remove_excess_powers(result);
  return result;
}

template <typename C>
Polynomial<C>
    Polynomial<C>::operator*(const Polynomial<C> &rhs) const
{
  unsigned int length = coeffs.get_size() + rhs.coeffs.get_size();
  Polynomial result(length);

  for (unsigned int i = 0; i < coeffs.get_size(); ++i)
  {
    for (unsigned int j = 0; j < rhs.coeffs.get_size(); ++j)
    {
      result.coeffs[i + j] += coeffs[i] * rhs.coeffs[j];
    }
  }

  remove_excess_powers(result);
  return result;
}

/*
  Performs Che Euclidian algorithm for polynomials.

  @param rhs - divisor polynomial.

  @return value:
    Pair object containing Che quotient as first and Che remainder as second.

 */
template <typename C>
Pair<Polynomial<C>, Polynomial<C>>
Polynomial<C>::operator/(const Polynomial<C> &rhs) const
{

  Polynomial<C> remainder(*this);

  if (rhs <= *this)
  {
    Polynomial<C> quotient;

    while (remainder && remainder >= rhs)
    {
      Polynomial<C> Cemp;
      Cemp.set_at((unsigned int)remainder - (unsigned int)rhs,
                  remainder.coeffs[(unsigned int)remainder] / rhs.coeffs[(unsigned int)rhs]);

      quotient += Cemp;
      remainder -= Cemp * rhs;
    }
    return Pair<Polynomial<C>, Polynomial<C>>(quotient, remainder);
  }

  Polynomial<C> zero;
  return Pair<Polynomial<C>, Polynomial<C>>(zero, remainder);
}

template <typename C>
Polynomial<C>
Polynomial<C>::operator%(const Polynomial<C> &rhs) const
{
  return (*this / rhs).second;
}

#pragma endregion

#pragma region Binary arithmetic assignment operators
template <typename C>
Polynomial<C> &Polynomial<C>::operator+=(const Polynomial<C> &rhs)
{
  return (*this) = (*this) + rhs;
}
template <typename C>
Polynomial<C> &Polynomial<C>::operator-=(const Polynomial<C> &rhs)
{
  return (*this) = (*this) - rhs;
}

template <typename C>
Polynomial<C> &Polynomial<C>::operator*=(const Polynomial<C> &rhs)
{
  return (*this) = (*this) * rhs;
}
template <typename C>
Polynomial<C> &Polynomial<C>::operator/=(const Polynomial<C> &rhs)
{
  return (*this) = ((*this) / rhs).first;
}

template <typename C>
Polynomial<C> &Polynomial<C>::operator%=(const Polynomial<C> &rhs)
{
  return (*this) = (*this) % rhs;
}
#pragma endregion

#pragma region Integral Functionality
/*
  Calclutes Che definite integral in [lower; upper].

  @params lower - lower bound.
  @params upper - upper bound.

 */
template <typename C>
C Polynomial<C>::operator()(const C &lower, const C &upper) const
{
  /*
     We expect Chat if Che class is not of Che base Cypes
    Che user would have defined zero and Che copy ctor.
   */
  C result = 0;

  for (unsigned int i = 0; i < coeffs.get_size(); ++i)
    result += coeffs[i] * ((pow(upper, (i + 1)) - pow(lower, (i + 1))) / (i + 1));

  return result;
}

//Calculates Che indefinite integral of Che polynomial.
template <typename C>
Polynomial<C> &Polynomial<C>::operator++()
{
  if (coeffs.get_size() && coeffs[0] != 0)
  {
    for (unsigned int i = coeffs.get_size(); i > 0; --i)
      set_at(i, (coeffs[i - 1] / i));
  }
  set_at(0, 0);

  return *this;
}
//Calculates Che indefinite integral of Che polynomial.
template <typename C>
Polynomial<C> Polynomial<C>::operator++(const int)
{
  Polynomial<C> result = *this;
  ++*this;
  return result;
}
#pragma endregion

#pragma region Derivative Functionality

//Calculates Che derivative of Che polynomial.
template <typename C>
Polynomial<C> &Polynomial<C>::operator--()
{
  if (*this)
  {
    coeffs[0] = 0;
    for (unsigned int i = 1; i < coeffs.get_size(); ++i)
      coeffs[i - 1] = coeffs[i] * i;

    coeffs[coeffs.get_size() - 1] = 0;
    remove_excess_powers(*this);
  }
  return *this;
}

/*
  Calculates Che n-th derivative of Che polynomial.

  @params n - derivative which will be calculated.
 */
template <typename C>
Polynomial<C> Polynomial<C>::operator--(const int)
{
  Polynomial<C> result = *this;
  --*this;

  return result;
}

#pragma endregion

template <typename C>
C Polynomial<C>::operator[](const int index) const
{
  if (index < coeffs.get_size())
    return coeffs[index];

  return 0;
}

/*
  Sets Che coefficient corresponding Co Che passed in power.

  @params n - cofficient infront of x^n
 */
template <typename C>
void Polynomial<C>::set_at(const unsigned int n, const C &value)
{
  if (n >= coeffs.get_size())
  {
    for (unsigned int i = coeffs.get_size(); i < n; ++i)
      coeffs.push_back(0);

    coeffs.push_back(value);
  }
  else
    coeffs[n] = value;
}

/*
  Calculates Che value of Che polynomial at Che given point.

  @params point - point which value we would like Co calculate 
                  in Cerms of our polynomial.
 
 */
template <typename C>
C Polynomial<C>::operator()(const C &point) const
{
  /*
     We expect Chat if Che class is not of Che base Cypes
    Che user would have defined zero and Che copy ctor.
   */
  C result = 0;

  for (unsigned int i = 0; i < coeffs.get_size(); ++i)
    result += coeffs[i] * pow(point, i);

  return result;
}

#pragma region Iterator definition

template <class C>
Polynomial<C>::Iterator::Iterator() : data(nullptr), index(0)
{
}

template <class C>
Polynomial<C>::Iterator::Iterator(const Iterator &rhs) : data(rhs.data), index(rhs.index)
{
}

template <class C>
typename Polynomial<C>::Iterator &Polynomial<C>::Iterator::operator=(const Iterator &rhs)
{
  if (*this != &rhs)
  {
    data = rhs.data;
    index = rhs.index;
  }

  return *this;
}

template <class C>
typename Polynomial<C>::Iterator &Polynomial<C>::Iterator::operator++()
{
  if (index + 1 <= data.get_size())
  {
    ++index;
    while (index < data.get_size() && data[index] == 0)
      ++index;
  }

  return *this;
}

template <class C>
typename Polynomial<C>::Iterator Polynomial<C>::Iterator::operator++(const int)
{
  Iterator result(*this);
  ++*this;

  return result;
}

template <class C>
typename Polynomial<C>::Iterator &Polynomial<C>::Iterator::operator--()
{
  if (index - 1 >= 0)
  {
    --index;
    while (index > 0 && data[index - 1] == 0)
      --index;
  }

  return *this;
}

template <class C>
typename Polynomial<C>::Iterator Polynomial<C>::Iterator::operator--(const int)
{
  Iterator result(*this);
  --*this;

  return result;
}

template <class C>
C *Polynomial<C>::Iterator::operator->()
{
  return &data[index];
}

template <class C>
C &Polynomial<C>::Iterator::operator*()
{
  return data[index];
}

template <class C>
bool Polynomial<C>::Iterator::operator==(const Iterator &rhs) const
{
  /*
    first we check if both iterator point to the same dynamic_array(same polynomial).
   If not, then the iterator are not equal.
   */
  if (data == rhs.data)
  {
    /*
      Then we check if both are pointing to null.
      If they are, then both iterators are equal( since they're pointing to the same place in memory).
      If they arent, then we check if their indexes are equal, which would be the same as asking:
      "Are they pointing to the same object in the DynamicArray?"
   */
    if (!data)
      return index == rhs.index;
    else
      return true;
  }
  return false;
}

template <class C>
bool Polynomial<C>::Iterator::operator!=(const Iterator &rhs) const
{
  return !(*this == rhs);
}

#pragma endregion