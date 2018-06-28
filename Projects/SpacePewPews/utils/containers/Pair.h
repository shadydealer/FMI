#pragma once

template <class C1, class C2>
struct Pair
{
  public:
    C1 first;
    C2 second;

  public:
    Pair();
    Pair(const Pair &);
    Pair &operator=(const Pair &);
    Pair(const C1 &, const C2 &);

  public:
    bool operator==(const Pair &) const;
    bool operator!=(const Pair &) const;
};

template <class C1, class C2>
Pair<C1, C2>::Pair() : first(), second()
{
}

template <class C1, class C2>
Pair<C1, C2>::Pair(const C1 &rhsFirst, const C2 &rhsSecond) : first(rhsFirst), second(rhsSecond)
{
}

template <class C1, class C2>
Pair<C1, C2>::Pair(const Pair<C1, C2> &rhs) : first(rhs.first), second(rhs.second)
{
}

template <class C1, class C2>
Pair<C1, C2> &Pair<C1, C2>::operator=(const Pair<C1, C2> &rhs)
{
    if (this != &rhs)
    {
        first = rhs.first;
        second = rhs.second;
    }
    return *this;
}

template <class C1, class C2>
bool Pair<C1, C2>::operator==(const Pair<C1, C2> &rhs) const
{
    return first == rhs.first && second == rhs.second;
}

template <class C1, class C2>
bool Pair<C1, C2>::operator!=(const Pair<C1, C2> &rhs) const
{
    return !(*this == rhs);
}