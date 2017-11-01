#include "LinkedList.h"


LinkedList::LinkedList() : dummy(new Node()), size(0)
{
    dummy->prev = dummy;
    dummy->next = dummy;

}

void LinkedList::Clean()
{
    Node * curr = dummy->next;

    while(size)
    {
        Node * temp = curr->next;
        delete curr;
        curr = temp;
        --size;
    }

    delete dummy;

    size = 0;
}

LinkedList::~LinkedList()
{
    Clean();
}

void LinkedList::Print() const
{
    std::cout << dummy->url << std::endl;
}

//
// Default Node ctor.
//
LinkedList::Node::Node() : url(NULL), prev(NULL), next(NULL), timeStamp(time(0))
{
    CopyString("about:blank");
}

//
// Node ctor with string parameter.
//
LinkedList::Node::Node(const char *rhsURL) : Node()
{
    CopyString(rhsURL);
}

//
// Coppies the string held in the parameter of the function.
//
void LinkedList::Node::CopyString(const char *rhsURL)
{
    try
    {
        char *buffer = new char[strlen(rhsURL) + 1];
        strcpy(buffer, rhsURL);

        delete[] url;
        url = buffer;
    }
    catch (std::bad_alloc())
    {
        Clean();
        throw "Failed to allocate enough memory./n";
    }
}

//
// Frees any allcated memory and sets the timeStamp to 0.
//
void LinkedList::Node::Clean()
{
    delete[] url;
    timeStamp = 0;
}

//
// Nodes copy ctor.
//
LinkedList::Node::Node(const Node &rhs) : Node()
{
    CopyString(rhs.url);
    timeStamp = rhs.timeStamp;
}

//
// Node dtor.
//
LinkedList::Node::~Node()
{
    Clean();
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
    }
    return *this;
}
