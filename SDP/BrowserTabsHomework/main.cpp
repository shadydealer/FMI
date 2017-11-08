#include <iostream>
#include "LinkedList.h"
#include "Tab.h"
#include "CommandHandler.h"
#include "string.h"

const char * get_input();

int main()
{
    try
    {
        LinkedList<Tab> a;
        a.push_back("about:blank");
        CommandHandler handler(a);

        const char *buffer;

        do
        {
            buffer = get_input();
            handler.execute_command(buffer);
        }
        while (buffer);
    }
    catch (const char *msg)
    {
        std::cout << msg;
    }
    catch (std::bad_alloc())
    {
        std::cout << "Failed to allocate enough memory.\n";
    }
    return 0;
}

const char * get_input()
{
    const int length = 1024;
    size_t count = 0;   //stores the amount of characters read from the stream.

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

        return buffer;
    }
    catch (std::bad_alloc())
    {
        delete[] buffer;
        throw std::bad_alloc();
    }
}