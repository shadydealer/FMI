#pragma once
#include <iostream>
#include <string.h>

template <typename T>
class LinkedList
{
  private:
    struct node
    {
        T data;
        node *prev; //pointer to the previous node.
        node *next; //pointer to the next node.

      public:
        #pragma region node Big Four
        node();
        node(const node &);
        node &operator=(const node &);
        ~node();
        #pragma endregion

      public:
        node(const T &);

    } dummy;

  private:
    void copy_list(const LinkedList &);

  public:
    class iterator
    {
        friend class LinkedList;
        node *pnode;

      public:
        #pragma region iterator Big Four
        iterator();
        iterator(const iterator &);
        iterator &operator=(const iterator &);
        ~iterator();
        #pragma endregion
      public:
        iterator(node *);

      public:
        T *operator->();
        T &operator*();

      public:
        #pragma region iterator Increment and Decrement operators
        iterator &operator++();
        iterator operator++(const int);
        iterator &operator--();
        iterator operator--(const int);
        #pragma endregion

      public:
        #pragma region iterator comparison operators
        bool operator!=(const iterator &) const;
        bool operator==(const iterator &) const;
        #pragma endregion
    };

  public:
    void clean();

  public:
    iterator beg();
    iterator end();

  public:
    #pragma region LinkedList Big Four
    LinkedList();
    LinkedList(const LinkedList &);
    LinkedList<T> &operator=(const LinkedList &);
    ~LinkedList();
    #pragma endregion

  public:
    void push_back(const T &);
    void insert_after(iterator &, const T &);
    void remove_at(iterator &);
};

#pragma region LinkedList Big Four
//
// Default LinkedList ctor.
//
template <typename T>
LinkedList<T>::LinkedList() : dummy()
{
    dummy.next = &dummy;
    dummy.prev = &dummy;
}

//
// LinkedList copy ctor.
//
template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T> &rhs) : LinkedList()
{
    copy_list(rhs);
}

//
//LinkedList operator=.
//

template <typename T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &rhs)
{
    if (&rhs != this)
        copy_list(rhs);
    return *this;
}


//
//LinkedList dtor.
//
template <typename T>
LinkedList<T>::~LinkedList()
{
    clean();
}
#pragma endregion

//
// Coppies each node from the input list along with the timestamps.
//
template <typename T>
void LinkedList<T>::copy_list(const LinkedList<T> &rhs)
{

    LinkedList<T>::iterator curr = beg();     //iterator to the beinning of the curr list.
    LinkedList<T>::iterator next = rhs.beg(); //iterator to the beginning of the input list.

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
void LinkedList<T>::clean()
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
// Returns a copy of an iterator pointing to the first element in the list.
//
template <typename T>
typename LinkedList<T>::iterator LinkedList<T>::beg()
{
    return iterator(dummy.next);
}

//
// Returns a copy of an iterator pointing to the last element in the list.
//
template <typename T>
typename LinkedList<T>::iterator LinkedList<T>::end()
{
    return iterator(&dummy);
}

//
// Inserts a node at the end of the list.
//
template <typename T>
void LinkedList<T>::push_back(const T &rhs)
{
    dummy.prev->next = new node(rhs);
    dummy.prev->next->next = &dummy;
    dummy.prev->next->prev = dummy.prev;
    dummy.prev = dummy.prev->next;
}

template <typename T>
void LinkedList<T>::insert_after(iterator &it, const T &rhs)
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
void LinkedList<T>::remove_at(iterator &it)
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

#pragma region node Big Four

//
// Default node ctor.
//
template <typename T>
LinkedList<T>::node::node() : prev(NULL), next(NULL), data()
{
}


//
// nodes copy ctor.
//
template <typename T>
LinkedList<T>::node::node(const node &rhs) : node()
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
// node operator=.
//
template <typename T>
typename LinkedList<T>::node &LinkedList<T>::node::operator=(const node &rhs)
{
    if (&rhs != this)
    {
        prev = rhs.prev;
        next = rhs.next;
    }
    return *this;
}

//
// node dtor.
//
template <typename T>
LinkedList<T>::node::~node()
{
}
#pragma endregion

//
// node ctor with string parameter.
//
template <typename T>
LinkedList<T>::node::node(const T &rhs) : node()
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


#pragma region iterator Big Four
//
// iterator default ctor.
//
template <typename T>
LinkedList<T>::iterator::iterator() : pnode(NULL)
{
}

//
// iterator copy ctor.
//
template <typename T>
LinkedList<T>::iterator::iterator(const iterator &rhs) : iterator()
{
    pnode = rhs.pnode;
}

//
// iterator operator=.
//
template <typename T>
typename LinkedList<T>::iterator &LinkedList<T>::iterator::operator=(const iterator &rhs)
{
    if (&rhs != this)
        pnode = rhs.pnode;
    return *this;
}

template <typename T>
LinkedList<T>::iterator::~iterator()
{
}

#pragma endregion

//
// iterator ctor with node pointer parameter.
//
template <typename T>
LinkedList<T>::iterator::iterator(node *rhs) : pnode(rhs)
{
}
//
// iterator operator->
//
template <typename T>
T *LinkedList<T>::iterator::operator->()
{
    return &(*pnode).data;
}

template <typename T>
T &LinkedList<T>::iterator::operator*()
{
    return (*pnode).data;
}

#pragma region iterator Increment and Decrement operators
//
// iterator operator++.
//
template <typename T>
typename LinkedList<T>::iterator &LinkedList<T>::iterator::operator++()
{
    pnode = pnode->next;
    return *this;
}

//
// iterator ++operator.
//
template <typename T>
typename LinkedList<T>::iterator LinkedList<T>::iterator::operator++(const int)
{
    iterator dummy(*this);
    ++(*this);
    return dummy;
}

//
// iterator operator--.
//
template <typename T>
typename LinkedList<T>::iterator &LinkedList<T>::iterator::operator--()
{
    pnode = pnode->prev;
    return *this;
}

//
// iterator --operator.
//
template <typename T>
typename LinkedList<T>::iterator LinkedList<T>::iterator::operator--(const int)
{
    iterator temp(*this);
    --(*this);
    return temp;
}
#pragma endregion

#pragma region iterator comparison operators
//
// iterator operator!=.
//
template <typename T>
bool LinkedList<T>::iterator::operator!=(const iterator &rhs) const
{
    return !(pnode == rhs.pnode);
}

//
// iterator operator==.
//
template <typename T>
bool LinkedList<T>::iterator::operator==(const iterator &rhs) const
{
    return !(*this != rhs);
}
#pragma endregion