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

        return buffer;
    }
    catch (std::bad_alloc())
    {
        delete[] buffer;
        throw std::bad_alloc();
    }
}
