#include "InputReader.h"

//
// Reads a full line of input into a char *
//and returns it if it's a valid command.
//
// May throw std::bad_alloc()
//
const char *InputReader::get_input()
{

    const size_t length = 10;
    size_t count = 0;

    char *buffer = new char[length];
    char *temp;

    try
    {
        //
        // Loops until all the flags are set to false.
        //
        while (!std::cin.getline(buffer, length).good())
        {
            // move the buffer pointer to the beginning of the string.
            buffer -= count;

            // get the amount of characters extracted from the stream.
            count += std::cin.gcount();

            // allocate more space for a bigger string.
            temp = new char[length + count];

            // copy the alraedy read characters
            // from the buffer into the newly allocated space.
            strcpy(temp, buffer);

            delete[] buffer;
            buffer = temp;

            // Increment the pointer to the first place
            //in the newly allocated space where we can write
            //without writing over the previously extracted characters.
            buffer += count;

            //reset the stream state flags.
            std::cin.clear();
        }

        // move the buffer pointer to the beginning of the string.
        buffer -= count;
        // check if the input string is a valid command
        //and delete it if it isn't.

        if (!valid_command(buffer))
            delete[] buffer;

        return buffer;
    }
    catch (std::bad_alloc())
    {
        delete[] buffer;
        throw std::bad_alloc();
    }
}

//
// Checks if the input string is a valid command.
//
//
// May throw std::bad_alloc()
//
bool InputReader::valid_command(const char *buffer)
{
    char *command;

    size_t length = 0;

    if (*buffer != 0)
    {
        if ((!strcmp(buffer, "SORT TIME")) || (!strcmp(buffer, "SORT URL")))
            length = strlen(buffer) + 1;

        else
        {
            size_t it = 0;

            while (buffer[it] != ' ' 
                && buffer[it] != '\n'
                && buffer[it] != 0)
            {
                ++it;
                ++length;
            }
        }

        command = new char[length];

        for (size_t c = 0; c < length; ++c)
        {
            command[c] = buffer[c];
        }
        command[length] = 0;

        if ((!strcmp(command, "GO")) 
        || (!strcmp(command, "INSERT"))
        || (!strcmp(command, "BACK")) 
        || (!strcmp(command, "FORWARD")) 
        || (!strcmp(command, "REMOVE")) 
        || (!strcmp(command, "PRINT")) 
        || (!strcmp(command, "SORT URL")) 
        || (!strcmp(command, "SORT TIME")))
        {
            return true;
        }
    }

    return false;
}