#pragma once
#include "LinkedList.h"

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
// Coppies each node from the input list along with the timestamps.
//
template <typename T>
void LinkedList<T>::copy_list(const LinkedList<T> &rhs)
{

    LinkedList<T>::Iterator curr = beg();      //iterator to the beinning of the curr list.
    LinkedList<T>::Iterator next = rhs.beg(); //iterator to the beginning of the input list.

    // We will keep copying until we encounter the dummy node.
    while (next != rhs.end())
    {
        //Creates a new node and coppies the data from the passed in one.
        curr.pnode->next = new Node(*(*next));

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

    Node *curr = dummy.next; //pointer to the current node.

    //We will keep iterating until we reach the dummy node.
    while (curr != &dummy)
    {
        Node *temp = curr->next; //get the next node to delete.
        delete curr;             //delete the curr node we are on right now.
        curr = temp;             //set the current node to be the next one in the list.
    }
}

//
//LinkedList dtor.
//
template <typename T>
LinkedList<T>::~LinkedList()
{
    clean();
}

//
// Returns a copy of an iterator pointing to the first element in the list.
//
template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::beg()
{
    return Iterator(dummy.next);
}

//
// Returns a copy of an iterator pointing to the last element in the list.
//
template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::end()
{
    return Iterator(&dummy);
}

//
// Inserts a node at the end of the list.
//
template <>
inline void LinkedList<Tab>::push_back(const char *rhs_url)
{
    dummy.prev->next = new Node(rhs_url);
    dummy.prev->next->next = &dummy;
    dummy.prev->next->prev = dummy.prev;
    dummy.prev = dummy.prev->next;
}
//
// Creates a new node by given url and inserts it after a specific node.
//
template <>
inline void LinkedList<Tab>::insert_after(Iterator &it, const char *rhsUrl)
{
    it.pnode->next->prev = new Node(rhsUrl);     //Set the next nodes "previous" pointer to a new Node.
    it.pnode->next->prev->next = it.pnode->next; //Set the new nodes "next" pointer to the current Nodes "next" node.
    it.pnode->next->prev->prev = it.pnode;       //Set the new nodes "previous" pointer to the current Nodes "previous" node.
    it.pnode->next = it.pnode->next->prev;       //Set the current nodes "next" Node to the new Node.

    //increment the iterator.
    ++it;
}

//
// Removes the Node after the one the iterator is pointig to.
//
template <typename T>
void LinkedList<T>::remove_at(Iterator &it)
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
// Default Node ctor.
//

template <typename T>
LinkedList<T>::Node::Node() : prev(NULL), next(NULL), data()
{
}

//
// Node ctor with string parameter.
//
template <typename T>
LinkedList<T>::Node::Node(const T &rhs) : Node()
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
// Nodes copy ctor.
//
template <typename T>
LinkedList<T>::Node::Node(const Node &rhs) : Node()
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
// Node dtor.
//
template <typename T>
LinkedList<T>::Node::~Node()
{
}

//
// Node operator=.
//
template <typename T>
typename LinkedList<T>::Node &LinkedList<T>::Node::operator=(const Node &rhs)
{
    if (&rhs != this)
    {

        prev = rhs.prev;
        next = rhs.next;
    }
    return *this;
}

//
// Iterator default ctor.
//
template <typename T>
LinkedList<T>::Iterator::Iterator() : pnode(NULL)
{
}

//
// Iterator ctor with Node pointer parameter.
//
template <typename T>
LinkedList<T>::Iterator::Iterator(Node *rhs) : pnode(rhs)
{
}

//
// Iterator copy ctor.
//
template <typename T>
LinkedList<T>::Iterator::Iterator(const Iterator &rhs) : Iterator()
{
    pnode = rhs.pnode;
}

//
// Iterator operator=.
//
template <typename T>
typename LinkedList<T>::Iterator &LinkedList<T>::Iterator::operator=(const Iterator &rhs)
{
    if (&rhs != this)
        pnode = rhs.data;

    return *this;
}

//
// Iterator operator->
//
template <typename T>
T *LinkedList<T>::Iterator::operator->()
{
    return &(*pnode).data;
}

//
// Iterator operator++.
//
template <typename T>
typename LinkedList<T>::Iterator &LinkedList<T>::Iterator::operator++()
{
    pnode = pnode->next;
    return *this;
}

//
// Iterator ++operator.
//
template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::Iterator::operator++(const int)
{
    Iterator dummy(*this);
    ++(*this);
    return dummy;
}

//
// Iterator operator--.
//
template <typename T>
typename LinkedList<T>::Iterator &LinkedList<T>::Iterator::operator--()
{
    pnode = pnode->prev;
    return *this;
}

//
// Iterator --operator.
//
template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::Iterator::operator--(const int)
{
    Iterator temp(*this);
    --(*this);
    return temp;
}

//
// Iterator operator!=.
//
template <typename T>
bool LinkedList<T>::Iterator::operator!=(const Iterator &rhs) const
{
    return !(pnode == rhs.pnode);
}

//
// Iterator operator==.
//
template <typename T>
bool LinkedList<T>::Iterator::operator==(const Iterator &rhs) const
{
    return !(*this != rhs);
}
