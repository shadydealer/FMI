#pragma once
#include "Queue.h"

//
// Queue default ctor.
//
template <typename T>
Queue<T>::Queue() : sentinel()
{
    sentinel.p_next = &sentinel;
    sentinel.p_prev = &sentinel;
}

//
// Queue Copy Ctor.
//
template <typename T>
Queue<T>::Queue(const Queue &rhs)
{
    try
    {
        copy_nodes(rhs);
    }
    catch (std::bad_alloc())
    {
        clean();
    }
}

//
// Queue operator=.
//
template <typename T>
Queue<T> &Queue<T>::operator=(const Queue &rhs)
{
    if (this != &rhs)
        copy_nodes(rhs);
    return *this;
}

//
// Coppies the nodes from the passed in array.
// May throw std::bad_alloc();
//
template <typename T>
void Queue<T>::copy_nodes(const Queue &rhs)
{
    Node *curr = rhs.sentinel.p_next;
    Node *at = sentinel;

    while (curr != &rhs.sentinel)
    {
        at->p_next->p_prev = new Node(*curr);
        at->p_next->p_prev->p_next = at->p_next;
        at->p_next->p_prev->p_prev = at;
        at->p_next = at->p_next->p_prev;
        at->p_next;
        curr->p_next;
    }
}

//
// Queue dtor.
//
template <typename T>
Queue<T>::~Queue()
{
    clean();
}

template <typename T>
void Queue<T>::clean()
{
    Node *curr = sentinel.p_next;
    while (curr != &sentinel)
    {
        curr = curr->p_next;
        delete curr->p_prev;
    }
}

//
// adds a Node at the end of the Queue.
//
template <typename T>
void Queue<T>::push(const T &rhs)
{
    sentinel.p_prev->p_next = new Node(rhs);
    sentinel.p_prev->p_next->p_next = &sentinel;
    sentinel.p_prev->p_next->p_prev = sentinel.p_prev;
    sentinel.p_prev = sentinel.p_prev->p_next;
}

//
// Removes a Node from the beginning of the Queue.
//
template <typename T>
T Queue<T>::pop()
{
    T buff;

    if (sentinel.p_next != &sentinel)
    {
        Node *temp = sentinel.p_next;

        buff = (*sentinel.p_next).data;
        sentinel.p_next->p_next->p_prev = &sentinel;
        sentinel.p_next = sentinel.p_next->p_next;
        delete temp;
    }
    else
        buff = sentinel.data;

    return buff;
}

//
// Returns a reference to the value of the "oldest" element in the Queue.
//
template <typename T>
T &Queue<T>::head()
{
    return (*sentinel.p_prev).data;
}

//
// Node Default ctor.
//
template <typename T>
Queue<T>::Node::Node() : data(), p_prev(NULL), p_next(NULL)
{
}

//
// Node copy ctor.
//
template <typename T>
Queue<T>::Node::Node(const Node &rhs) : Node()
{
    data = rhs.data;
    p_prev = rhs.p_prev;
    p_next = rhs.p_next;
}

//
// Node ctor with T parameter.
//

template <typename T>
Queue<T>::Node::Node(const T &rhs) : Node()
{
    data = rhs;
}