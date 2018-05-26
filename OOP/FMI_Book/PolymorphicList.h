#pragma once

#include <stdexcept> //std::out_of_range

/*
    polymorphic list class which will be used as a polymorphic container.
 */
template <typename T>
class PolymorphicList
{
  private:
    struct Node
    {
        Node *prev;
        Node *next;
        T * data;

      public:
        Node();
        Node(T *);
        Node &operator=(const Node&);
    } * front, *back;

    unsigned int length;

  public:
    class Iterator
    {
        friend class PolymorphicList;
        Node *curr;

      public:
        Iterator();
        Iterator(Node *);
        Iterator(const Iterator &);
        Iterator &operator=(const Iterator &);

      public:
        T *operator->();
        T &operator*();

      public:
        Iterator &operator++();
        Iterator operator++(const int);
        Iterator &operator--();
        Iterator operator--(const int);

      public:
        operator bool() const;
        bool operator!=(const Iterator &);
        bool operator==(const Iterator &);
    };

  public:
    PolymorphicList();
    ~PolymorphicList();

  public:
    void push_back(T *);
    void remove(Iterator &);

  public:
    Iterator beg();
    Iterator end();
};

//Default Node ctor.
template <typename T>
PolymorphicList<T>::Node::Node() : prev(nullptr), next(nullptr), data(nullptr)
{
}

/*
    Node T paramter ctor. 
    T is not const nore a reference because
    T will be pointer to base object.
 */
template <typename T>
PolymorphicList<T>::Node::Node(T * rhsData) : prev(nullptr), next(nullptr), data(rhsData)
{
}

//Node operator=.
template <typename T>
typename PolymorphicList<T>::Node &PolymorphicList<T>::Node::operator=(const Node &rhs)
{
    if (this != &rhs)
    {
        prev = rhs.prev;
        next = rhs.next;
        data = rhs.data;
    }
    return *this;
}

//Default Iterator ctor.
template <typename T>
PolymorphicList<T>::Iterator::Iterator() : curr(nullptr)
{
}

//Iterator copy ctor.
template <typename T>
PolymorphicList<T>::Iterator::Iterator(const Iterator &rhs) : curr(rhs.curr)
{
}

//Iterator Node pointer paramter ctor.
template <typename T>
PolymorphicList<T>::Iterator::Iterator(Node *rhs) : curr(rhs)
{
}

//Iteartor operator->.
template <typename T>
T *PolymorphicList<T>::Iterator::operator->()
{
    return (curr->data);
}

//Iterator operator*.
template <typename T>
T& PolymorphicList<T>::Iterator::operator*()
{
    return (*(curr->data));
}

//Iterator prefix operator++.
template <typename T>
typename PolymorphicList<T>::Iterator &PolymorphicList<T>::Iterator::operator++()
{
    curr = curr->next;

    return *this;
}

//Iterator postfix operator++.
template <typename T>
typename PolymorphicList<T>::Iterator PolymorphicList<T>::Iterator::operator++(const int)
{
    PolymorphicList::Iterator temp(*this);
    ++(*this);
    return temp;
}

//Iterator prefix operator--.
template <typename T>
typename PolymorphicList<T>::Iterator &PolymorphicList<T>::Iterator::operator--()
{
    curr = curr->prev;

    return *this;
}

//Iterator postfix operator--.
template <typename T>
typename PolymorphicList<T>::Iterator PolymorphicList<T>::Iterator::operator--(const int)
{
    Iterator temp(*this);
    --(*this);
    return temp;
}

//Bool operator.
template <typename T>
PolymorphicList<T>::Iterator::operator bool() const
{
    return curr ? true : false;
}

//Iterator operator==.
template <typename T>
bool PolymorphicList<T>::Iterator::operator==(const Iterator &rhs)
{
    return curr == rhs.curr;
}

//Iterator opreator!=.
template <typename T>
bool PolymorphicList<T>::Iterator::operator!=(const Iterator &rhs)
{
    return !(*this == rhs);
}

//Default PolymorphicList ctor.
template <typename T>
PolymorphicList<T>::PolymorphicList() : front(nullptr), back(nullptr), length(0)
{
}

//Dtor.
template <typename T>
PolymorphicList<T>::~PolymorphicList()
{
    Node *temp = front;

    while (temp)
    {
        front = temp;
        temp = temp->next;
        delete front;
    }
}

/*
    Pushes rhs to the back of the polymorphic list.

    @params rhs - data which will be added to the back of the polymorphic list.
 */
template <typename T>
void PolymorphicList<T>::push_back(T * rhs)
{
    if (back)
    {
        back->next = new Node(rhs);
        back->next->prev = back;
        back = back->next;
    }
    else
    {
        back = new Node(rhs);
        front = back;
    }

    ++length;
}

/*
    Removes the node the iterator is pointing to.

    @params rhs- Iterator containing a pointer to the node we're removing.
 */
template <typename T>
void PolymorphicList<T>::remove(Iterator &rhs)
{
    if (length && rhs.curr)
    {
        if (rhs.curr->prev)
        {
            rhs.curr->prev->next = rhs.curr->next;
            back = rhs.curr->prev;
        }

        if (rhs.curr->next)
        {
            rhs.curr->next->prev = rhs.curr->prev;
            back = rhs.curr->next;
        }
        --length;

        if (!length)
            front = back = nullptr;

        delete (rhs--).curr;
    }
    else
        throw std::out_of_range("Iterator is out of range of the list.\n");
}

/*
    Returns an iterator to the beginning of the list.
*/
template <typename T>
typename PolymorphicList<T>::Iterator PolymorphicList<T>::beg()
{
    return Iterator(front);
}

/*
    Returns an iterator to the end of the list.
 */
template <typename T>
typename PolymorphicList<T>::Iterator PolymorphicList<T>::end()
{
    if (length)
        return Iterator(back->next);
    else
        return Iterator(back);
}
