#pragma once
#include <iostream>

template <typename T>
class linked_list
{
  private:
    struct node
    {
      public:
        T data;
        node *prev;
        node *next;

      public:
        node();
        node(const T &);
        node(const node &);
        node &operator=(const node &);
    } * beg, *end;

    int size;

  public:
    linked_list();
    linked_list(const linked_list<T>&);
    linked_list<T> operator=(const linked_list<T>&);
};

template <typename T>
linked_list<T>::linked_list() : beg(NULL), end(NULL)
{
}

//
// ===== NODE METHODS =====
//

//
// node default ctor.
//
template <typename T>
linked_list<T>::node::node() : data(), prev(NULL), next(NULL)
{
}

//
// node T parameter ctor.
//
template <typename T>
linked_list<T>::node::node(const T &rhs_data) : data(rhs_data), prev(NULL), next(NULL)
{
}

//
// node copy ctor.
//
template <typename T>
linked_list<T>::node::node(const node &rhs) : data(rhs.data), prev(rhs.prev), next(rhs.next)
{
}

//
// node operator=.
//
template <typename T>
typename linked_list<T>::node &linked_list<T>::node::operator=(const node &rhs)
{
    if (this != &rhs)
    {
        data = rhs.data;
        prev = rhs.prev;
        next = rhs.next;
    }
    return *this;
}