#pragma once

template <typename T1, typename T2>
struct Pair
{
  public:
    T1 first;
    T2 second;

  public:
    Pair();
    Pair(const Pair &);
    Pair &operator=(const Pair &);
    Pair(const T1 &, const T2 &);
};

template <typename T1, typename T2>
Pair<T1, T2>::Pair() : first(), second()
{
}

template <typename T1, typename T2>
Pair<T1, T2>::Pair(const T1 &rhsFirst, const T2& rhsSecond) : first(rhsFirst), second(rhsSecond)
{
}

template <typename T1, typename T2>
Pair<T1, T2>::Pair(const Pair<T1, T2> &rhs) : first(rhs.first), second(rhs.second)
{
}

template <typename T1, typename T2>
Pair<T1, T2> &Pair<T1, T2>::operator=(const Pair<T1, T2> &rhs)
{
    if (this != &rhs)
    {
        first = rhs.first;
        second = rhs.second;
    }
    return *this;
}