#include "CommandHandler.h"

//
// CommandHandler LinkedList parameter ctor.
//
CommandHandler::CommandHandler(LinkedList &rhs) : reciever(&rhs), data_it((*reciever).beg())
{
}

void CommandHandler::execute_command(const char *rhs_input)
{
    if (rhs_input)
    {
        switch (hash_command(rhs_input))
        {
        case GO:
            go(extract_url(rhs_input, 2));
            break;
        case INSERT:
            insert(extract_url(rhs_input, 6));
            break;
        case BACK:
            back();
            break;
        case FORWARD:
            forward();
            break;
        case REMOVE:
            remove();
            break;
        case PRINT:
            print();
            break;
        case EXIT:
            throw "Invalid command.\n";
        }
    }
    else
        throw "Invalid command.\n";
}

//
// Evaluates the command from the input string.
//
CommandHandler::command CommandHandler::hash_command(const char *rhs_input) const
{

    const char *command = extract_command(rhs_input);

    if (!strcmp(command, "GO"))
        return GO;
    if (!strcmp(command, "INSERT"))
        return INSERT;
    if (!strcmp(command, "BACK"))
        return BACK;
    if (!strcmp(command, "FORWARD"))
        return FORWARD;
    if (!strcmp(command, "REMOVE"))
        return REMOVE;
    if (!strcmp(command, "PRINT"))
        return PRINT;
    if (!strcmp(command, "SORT URL"))
        return SORT_URL;
    if (!strcmp(command, "SORT TIME"))
        return SORT_TIME;
    return EXIT;
}

//
// Extracts the string containing the command to be executed.
//
const char *CommandHandler::extract_command(const char *rhs_input) const
{
    char *command;

    size_t length = 0;

    if ((!strcmp(rhs_input, "SORT TIME")) || (!strcmp(rhs_input, "SORT URL")))
        length = strlen(rhs_input) + 1;

    else
    {
        size_t it = 0;

        while (rhs_input[it] != ' ' 
            && rhs_input[it] != '\n'
            && rhs_input[it] != 0)
        {
            ++it;
            ++length;
        }
    }

    command = new char[length];

    for (size_t c = 0; c < length; ++c)
    {
        command[c] = rhs_input[c];
    }
    command[length] = 0;

    return command;
}

const char *CommandHandler::extract_url(const char *rhs_input, const size_t url_beg) const
{
    size_t len = strlen(rhs_input + url_beg) + 1;
    char *buffer = new char[len];

    strcpy(buffer, rhs_input + url_beg);

    return buffer;
}

//
// Inserts a new Node by given url
//to simulate switching the current tabs url and timestamp.
//
void CommandHandler::go(const char *rhs_url)
{
    //
    // Updates the current nodes URL and timestamp,
    // if it's not the dummy node.
    //
    if (strcmp((*data_it)->url, "about:blank") != 0)
    {
        (*data_it)->CopyString(rhs_url);
        (*data_it)->timeStamp = time(0);
    }

    //
    // inserts a new Node by given url if
    //the iterator is pointing to the dummy node.
    //
    else
        insert(rhs_url);
}

//
// Inserts a new Node by given url.
//
void CommandHandler::insert(const char *rhs_url)
{
    (*reciever).insert_after(data_it, rhs_url);
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
    (*reciever).remove_at(data_it);
}

//
// Prints out the List that is currently in use.
//If there are no Nodes except the dummy one, print out only the dummy node.
//
void CommandHandler::print()
{
    LinkedList::Iterator temp = (*reciever).beg();

    for (; temp != (*reciever).end(); ++temp)
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