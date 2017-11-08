#include "LinkedList.h"

//
// Default LinkedList ctor.
//
LinkedList::LinkedList() : dummy(new Node())
{
    dummy->next = dummy;
    dummy->prev = dummy;
}

//
// LinkedList copy ctor.
//
LinkedList::LinkedList(const LinkedList &rhs) : LinkedList()
{
    copy_list(rhs);
}

//
//LinkedList operator=.
//
LinkedList &LinkedList::operator=(const LinkedList &rhs)
{
    if (&rhs != this)
        copy_list(rhs);
    return *this;
}
//
// Coppies each node from the input list along with the timestamps.
//
void LinkedList::copy_list(const LinkedList &rhs)
{
    LinkedList::Iterator curr = beg();     //iterator to the beinning of the curr list.
    LinkedList::Iterator next = rhs.beg(); //iterator to the beginning of the input list.

    // We will keep copying until we encounter the dummy node.
    while (next != rhs.end())
    {
        //Creates a new node and coppies the data from the passed in one.
        (*curr)->next = new Node(*(*next));

        // Changing the pointer to the prev and next
        //because they will be pointing to elements
        //from the input list if we don't.
        (*curr)->next->prev = *curr;
        (*curr)->next->next = dummy;

        ++curr;
        ++next;
    }
}

//
// Deletes all the nodes in the list including the dummy.
//
void LinkedList::clean()
{

    Node *curr = dummy->next; //pointer to the current node.

    //We will keep iterating until we reach the dummy node.
    while (curr != dummy)
    {
        Node *temp = curr->next; //get the next node to delete.
        delete curr;             //delete the curr node we are on right now.
        curr = temp;             //set the current node to be the next one in the list.
    }

    //delete the last node in the list.
    delete dummy;
}

//
//LinkedList dtor.
//
LinkedList::~LinkedList()
{
    clean();
}

//
// Returns a copy of an iterator pointing to the first element in the list.
//
LinkedList::Iterator LinkedList::beg() const
{
    return Iterator(dummy->next);
}

//
// Returns a copy of an iterator pointing to the last element in the list.
//
LinkedList::Iterator LinkedList::end() const
{
    return Iterator(dummy);
}

//
// Creates a new node by given url and inserts it after a specific node.
//
void LinkedList::insert_after(Iterator &it, const char *rhsUrl)
{
    (*it)->next->prev = new Node(rhsUrl);  //Set the next nodes "previous" pointer to a new Node.
    (*it)->next->prev->next = (*it)->next; //Set the new nodes "next" pointer to the current Nodes "next" node.
    (*it)->next->prev->prev = (*it);       //Set the new nodes "previous" pointer to the current Nodes "previous" node.
    (*it)->next = (*it)->next->prev;       //Set the current nodes "next" Node to the new Node.

    //increment the iterator.
    ++it;
}

//
// Removes the Node after the one the iterator is pointig to.
//
void LinkedList::remove_at(Iterator &it)
{
    (*it)->prev->next = (*it)->next; //Set the previous nodes "next" pointer to the current nodes "next" pointer.
    (*it)->next->prev = (*it)->prev; //Set the next nodes "previous" pointer to the current nodes "previous" pointer.

    // Check if the next node is the dummy node
    //if it is, point to the previous element,
    //else point to the next element in the list.
    if ((*it)->next->url != NULL)
        delete (*it++);
    else
        delete (*it--);
}

//
// Default Node ctor.
//
LinkedList::Node::Node() : prev(NULL), next(NULL), timeStamp(time(0)), url(NULL)
{
}

//
// Node ctor with string parameter.
//
LinkedList::Node::Node(const char *rhsURL) : Node()
{
    try
    {
        CopyString(rhsURL);
    }
    catch (std::bad_alloc())
    {
        clean_node();
        throw "Failed to allocate enough memory./n";
    }
}

//
// Nodes copy ctor.
//
LinkedList::Node::Node(const Node &rhs) : Node()
{
    try
    {
        CopyString(rhs.url);
        timeStamp = rhs.timeStamp;

        prev = rhs.prev;
        next = rhs.next;
    }
    catch (std::bad_alloc())
    {
        clean_node();
        throw "Failed to allocate enough memory./n";
    }
}

//
// Node dtor.
//
LinkedList::Node::~Node()
{
    clean_node();
}

//
// Node operator=.
//
LinkedList::Node &LinkedList::Node::operator=(const Node &rhs)
{
    if (&rhs != this)
    {
        CopyString(rhs.url);
        timeStamp = rhs.timeStamp;

        prev = rhs.prev;
        next = rhs.next;
    }
    return *this;
}

//
// Coppies the string held in the parameter of the function.
//
void LinkedList::Node::CopyString(const char *rhsURL)
{
    char *buffer = new char[strlen(rhsURL) + 1];
    strcpy(buffer, rhsURL);

    delete[] url;
    url = buffer;
}

//
// Frees any allcated memory and sets the timeStamp to 0.
//
void LinkedList::Node::clean_node()
{
    delete[] url;
    timeStamp = 0;
}

//
// Iterator default ctor.
//
LinkedList::Iterator::Iterator() : data(NULL)
{
}

//
// Iterator ctor with Node pointer parameter.
//
LinkedList::Iterator::Iterator(Node *rhs) : data(rhs)
{
}

//
// Iterator copy ctor.
//
LinkedList::Iterator::Iterator(const Iterator &rhs) : Iterator()
{
    data = rhs.data;
}

//
// Iterator operator=.
//
LinkedList::Iterator &LinkedList::Iterator::operator=(const Iterator &rhs)
{
    if (&rhs != this)
        data = rhs.data;

    return *this;
}

//
// Iterator operator++.
//
LinkedList::Iterator &LinkedList::Iterator::operator++()
{
    data = data->next;
    return *this;
}

//
// Iterator ++operator.
//
LinkedList::Iterator LinkedList::Iterator::operator++(const int)
{
    Iterator dummy(*this);
    ++(*this);
    return dummy;
}

//
// Iterator operator--.
//
LinkedList::Iterator &LinkedList::Iterator::operator--()
{
    data = data->prev;
    return *this;
}

//
// Iterator --operator.
//
LinkedList::Iterator LinkedList::Iterator::operator--(const int)
{
    Iterator dummy(*this);
    --(*this);
    return dummy;
}

//
// Iterator dereference operator.
//
LinkedList::Node *LinkedList::Iterator::operator*()
{
    return data;
}

//
// Iterator operator!=.
//
bool LinkedList::Iterator::operator!=(const Iterator &rhs) const
{
    return !(data == rhs.data);
}

//
// Iterator operator==.
//
bool LinkedList::Iterator::operator==(const Iterator &rhs) const
{
    return !(*this != rhs);
}
