#include <iostream>
#include "LinkedList.h"
#include "CommandHandler.h"
#include "InputReader.h"
#include "string.h"
int main()
{
    try
    {

        char *input;
        LinkedList a;
        CommandHandler handler(a);

        const char *buffer;

        while (strcmp(buffer, "EXIT") != 0 && buffer)
        {
            buffer = InputReader::get_input();
            handler.execute_command(buffer);
        }
    }
    catch(const char * msg)
    {
        std::cout << msg;
    }
    catch(std::bad_alloc())
    {
        std::cout << "Failed to allocate enough memory.\n";
    }
    return 0;
}