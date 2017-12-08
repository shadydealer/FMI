#include "linked_list.h"

linked_list::linked_list() : nodes(NULL), size(0)
{
}

linked_list::linked_list(const int rhsSize) : nodes(NULL), size(rhsSize)
{
    nodes = new node *[size];
    memset(nodes, 0, size);
}

linked_list::~linked_list()
{
    node *curr = *nodes;
    node *temp;
    while (curr)
    {
        temp = *curr->next;
        delete curr;
        curr = temp;
    }

    delete[] nodes;
}

void linked_list::push(const examData &rhs)
{
    bool hasChar = 0;
    node *currNode = *nodes;
    const char *currChar = rhs.get_name().get_data();

    while (currNode)
    {
        if (currNode->data == *currChar)
        {
            hasChar = 1;
            break;
        }
        ++currNode;
    }

    if (!hasChar)
        currNode = new node(*currChar++);

    currNode = *currNode->next;

    hasChar = 0;

    while (*currChar != 0)
    {
        while (currNode)
        {
            if (currNode->data == *currChar)
            {
                currNode = *currNode->next;
                hasChar = 1;
            }
            ++currChar;
        }
        currNode = new node(*currChar++);
        currNode = *currNode->next; 
        hasChar = 0;
    }

    currNode->obj = &rhs;
}

linked_list::node::node() : data(0), next(NULL), obj(NULL)
{
}

linked_list::node::node(const char rhsChar) : data(rhsChar), next(NULL), obj(NULL)
{
}

linked_list::node::~node()
{
    delete obj;
}
