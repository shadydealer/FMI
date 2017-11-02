#include "LinkedList.h"

//
// Default LinkedList ctor.
//
LinkedList::LinkedList() : dummy(new Node("about:blank"))
{
    dummy->prev = dummy;
    dummy->next = dummy;
}

//
// Deletes all the nodes in the list including the dummy.
//
void LinkedList::clean()
{
    Node *curr = dummy->next;

    while (curr != dummy)
    {
        Node *temp = curr->next;
        delete curr;
        curr = temp;
    }

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
LinkedList::Iterator LinkedList::beg()
{
    return Iterator (dummy->next);
}

//
// Returns a copy of an iterator pointing to the last element in the list.
//
LinkedList::Iterator LinkedList::end()
{
    return Iterator(dummy);
}

//
// Creates a new node by given url and inserts it after a specific node.
//
void LinkedList::insert_after(Iterator & it, const char* rhsUrl)
{
    (*it)->next->prev = new Node(rhsUrl);
    (*it)->next->prev->next = (*it)->next;
    (*it)->next->prev->prev = (*it);
    (*it)->next = (*it)->next->prev;
}

//
// Removes the current Node.
//
void LinkedList::remove_at(Iterator & it)
{
    (*it)->prev->next = (*it)->next;
    (*it)->next->prev = (*it)->prev;
    delete (*it);
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
LinkedList::Iterator& LinkedList::Iterator::operator++()
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
LinkedList::Iterator& LinkedList::Iterator::operator--()
{
    data = data->prev;
    return * this;
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
LinkedList::Node* LinkedList::Iterator::operator*()
{
    return data;
}

//
// Iterator operator!=.
//
bool LinkedList::Iterator::operator!=(const Iterator & rhs) const
{
    return !(data == rhs.data);
}

