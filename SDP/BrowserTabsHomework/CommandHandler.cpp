#include "CommandHandler.h"

// 
// CommandHandler LinkedList parameter ctor.
//
CommandHandler::CommandHandler(LinkedList &rhs) : data(&rhs), data_it((*data).beg())
{
}

void CommandHandler::execute_command(const char *rhs_command)
{
    
}

//
// Inserts a new Node by given url
//to simulate switching the current tabs url and timestamp.
//
void CommandHandler::go(const char *rhs_url)
{
    //removes the current Node in order to replace it with a new one.
    //remove_at() either moves the iterator to the next element
    //if there's one, else it moves it to the previous one.
    if (strcmp((*data_it)->url, "about:blank") != 0)
        (*data).remove_at(data_it);

    //inserts a new Node by given url.
    insert(rhs_url);
}

//
// Inserts a new Node by given url.
//
void CommandHandler::insert(const char *rhs_url)
{
    (*data).insert_after(data_it, rhs_url);
}

//
// Moves the iterator backwards if there's a Node there
//if there isn't the iterator stays where it is.
//
void CommandHandler::back()
{
    if (strcmp((*data_it)->prev->url, "about:blank") != 0)
        data_it = (*data_it)->prev;
}

//
// Moves the iterator forward if there's a Node there
//if there isnt the iterator stays where it is.
//
void CommandHandler::forward()
{
    if (strcmp((*data_it)->next->url, "about:blank") != 0)
        data_it = (*data_it)->next;
}

//
// Removes the Node we are currently on.
//the LinkedList::remove_at(iterator) function
//moves the iterator to the next element before removing it
//if there is one, if not then it moves it to the previous one.
//
void CommandHandler::remove()
{
    (*data).remove_at(data_it);
}

//
// Prints out the List that is currently in use.
//If there are no Nodes except the dummy one, print out only the dummy node.
//
void CommandHandler::print()
{
    LinkedList::Iterator temp = (*data).beg();

    for (; temp != (*data).end(); ++temp)
    {
        if (temp == data_it)
            std::cout << "> ";

        std::cout << (*temp)->url
                  << " "
                  << (*temp)->timeStamp
                  << std::endl;
    }

    if ((*temp)->prev == (*temp))
    {
        std::cout << "> "
                  << (*temp)->url
                  << " "
                  << (*temp)->timeStamp
                  << std::endl;
    }
}