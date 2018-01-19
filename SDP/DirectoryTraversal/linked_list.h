#pragma once
#include <iostream>
#include <string.h>

template <typename T>
class linked_list
{
  private:
    struct node
    {
        T data;
        node *prev; //pointer to the previous node.
        node *next; //pointer to the next node.

      public:
        node();
        node(const T &);
        node(const node &);
        node &operator=(const node &);
        ~node();

    } dummy;

  private:
    void copy_list(const linked_list &);

  public:
    class iterator
    {
        friend class linked_list;
        node *pnode;

      public:
        iterator();
        iterator(node *);
        iterator(const iterator &);
        iterator &operator=(const iterator &);
        ~iterator(){};

      public:
        T *operator->();
        T &operator*();

        iterator &operator++();
        iterator operator++(const int);
        iterator &operator--();
        iterator operator--(const int);

      public:
        bool operator!=(const iterator &) const;
        bool operator==(const iterator &) const;
    };

  public:
    void clean();
    iterator beg();
    iterator end();

  public:
    linked_list();
    linked_list(const linked_list &);
    linked_list<T> &operator=(const linked_list &);
    ~linked_list();

  public:
    void push_back(const T &);
    void insert_after(iterator &, const T &);
    void remove_at(iterator &);
};

//
// Default linked_list ctor.
//
template <typename T>
linked_list<T>::linked_list() : dummy()
{
    dummy.next = &dummy;
    dummy.prev = &dummy;
}

//
// linked_list copy ctor.
//
template <typename T>
linked_list<T>::linked_list(const linked_list<T> &rhs) : linked_list()
{
    copy_list(rhs);
}

//
//linked_list operator=.
//

template <typename T>
linked_list<T> &linked_list<T>::operator=(const linked_list<T> &rhs)
{
    if (&rhs != this)
        copy_list(rhs);
    return *this;
}
//
// Coppies each node from the input list along with the timestamps.
//
template <typename T>
void linked_list<T>::copy_list(const linked_list<T> &rhs)
{

    linked_list<T>::iterator curr = beg();     //iterator to the beinning of the curr list.
    linked_list<T>::iterator next = rhs.beg(); //iterator to the beginning of the input list.

    // We will keep copying until we encounter the dummy node.
    while (next != rhs.end())
    {
        //Creates a new node and coppies the data from the passed in one.
        curr.pnode->next = new node(*(*next));

        // Changing the pointer to the prev and next
        //because they will be pointing to elements
        //from the input list if we don't.
        curr.pnode->next->prev = *curr;
        curr.pnode->next->next = &dummy;

        ++curr;
        ++next;
    }
}

//
// Deletes all the nodes in the list including the dummy.
//
template <typename T>
void linked_list<T>::clean()
{

    node *curr = dummy.next; //pointer to the current node.

    //We will keep iterating until we reach the dummy node.
    while (curr != &dummy)
    {
        node *temp = curr->next; //get the next node to delete.
        delete curr;             //delete the curr node we are on right now.
        curr = temp;             //set the current node to be the next one in the list.
    }
}

//
//linked_list dtor.
//
template <typename T>
linked_list<T>::~linked_list()
{
    clean();
}

//
// Returns a copy of an iterator pointing to the first element in the list.
//
template <typename T>
typename linked_list<T>::iterator linked_list<T>::beg()
{
    return iterator(dummy.next);
}

//
// Returns a copy of an iterator pointing to the last element in the list.
//
template <typename T>
typename linked_list<T>::iterator linked_list<T>::end()
{
    return iterator(&dummy);
}

//
// Inserts a node at the end of the list.
//
template <typename T>
void linked_list<T>::push_back(const T &rhs)
{
    dummy.prev->next = new node(rhs);
    dummy.prev->next->next = &dummy;
    dummy.prev->next->prev = dummy.prev;
    dummy.prev = dummy.prev->next;
}

template <typename T>
void linked_list<T>::insert_after(iterator &it, const T &rhs)
{
    it.pnode->next->prev = new node(rhs);        //Set the next nodes "previous" pointer to a new node.
    it.pnode->next->prev->next = it.pnode->next; //Set the new nodes "next" pointer to the current nodes "next" node.
    it.pnode->next->prev->prev = it.pnode;       //Set the new nodes "previous" pointer to the current nodes "previous" node.
    it.pnode->next = it.pnode->next->prev;       //Set the current nodes "next" node to the new node.

    //increment the iterator.
    ++it;
}

//
// Removes the node after the one the iterator is pointig to.
//
template <typename T>
void linked_list<T>::remove_at(iterator &it)
{
    it.pnode->prev->next = it.pnode->next; //Set the previous nodes "next" pointer to the current nodes "next" pointer.
    it.pnode->next->prev = it.pnode->prev; //Set the next nodes "previous" pointer to the current nodes "previous" pointer.

    // Check if the next node is the dummy node
    //if it is, point to the previous element,
    //else point to the next element in the list.
    if (it.pnode->next->data.get_url())
        delete ((it++).pnode);
    else
        delete ((it--).pnode);
}

//
// Default node ctor.
//

template <typename T>
linked_list<T>::node::node() : prev(NULL), next(NULL), data()
{
}

//
// node ctor with string parameter.
//
template <typename T>
linked_list<T>::node::node(const T &rhs) : node()
{
    try
    {
        data = rhs;
    }
    catch (std::bad_alloc())
    {
        throw "Failed to allocate enough memory./n";
    }
}

//
// nodes copy ctor.
//
template <typename T>
linked_list<T>::node::node(const node &rhs) : node()
{
    try
    {
        data = rhs.data;

        prev = rhs.prev;
        next = rhs.next;
    }
    catch (std::bad_alloc())
    {
        throw "Failed to allocate enough memory./n";
    }
}

//
// node dtor.
//
template <typename T>
linked_list<T>::node::~node()
{
}

//
// node operator=.
//
template <typename T>
typename linked_list<T>::node &linked_list<T>::node::operator=(const node &rhs)
{
    if (&rhs != this)
    {

        prev = rhs.prev;
        next = rhs.next;
    }
    return *this;
}

//
// iterator default ctor.
//
template <typename T>
linked_list<T>::iterator::iterator() : pnode(NULL)
{
}

//
// iterator ctor with node pointer parameter.
//
template <typename T>
linked_list<T>::iterator::iterator(node *rhs) : pnode(rhs)
{
}

//
// iterator copy ctor.
//
template <typename T>
linked_list<T>::iterator::iterator(const iterator &rhs) : iterator()
{
    pnode = rhs.pnode;
}

//
// iterator operator=.
//
template <typename T>
typename linked_list<T>::iterator &linked_list<T>::iterator::operator=(const iterator &rhs)
{
    if (&rhs != this)
        pnode = rhs.pnode;
    return *this;
}

//
// iterator operator->
//
template <typename T>
T *linked_list<T>::iterator::operator->()
{
    return &(*pnode).data;
}

template <typename T>
T &linked_list<T>::iterator::operator*()
{
    return (*pnode).data;
}
//
// iterator operator++.
//
template <typename T>
typename linked_list<T>::iterator &linked_list<T>::iterator::operator++()
{
    pnode = pnode->next;
    return *this;
}

//
// iterator ++operator.
//
template <typename T>
typename linked_list<T>::iterator linked_list<T>::iterator::operator++(const int)
{
    iterator dummy(*this);
    ++(*this);
    return dummy;
}

//
// iterator operator--.
//
template <typename T>
typename linked_list<T>::iterator &linked_list<T>::iterator::operator--()
{
    pnode = pnode->prev;
    return *this;
}

//
// iterator --operator.
//
template <typename T>
typename linked_list<T>::iterator linked_list<T>::iterator::operator--(const int)
{
    iterator temp(*this);
    --(*this);
    return temp;
}

//
// iterator operator!=.
//
template <typename T>
bool linked_list<T>::iterator::operator!=(const iterator &rhs) const
{
    return !(pnode == rhs.pnode);
}

//
// iterator operator==.
//
template <typename T>
bool linked_list<T>::iterator::operator==(const iterator &rhs) const
{
    return !(*this != rhs);
}
