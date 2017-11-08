#include <iostream>
#include "LinkedList.h"
#include "CommandHandler.h"
#include "InputReader.h"
#include "string.h"

int main()
{
    try
    {
        LinkedList a;
        LinkedList::Iterator it = a.beg();
        a.insert_after(it, "about:blank");
        
        CommandHandler handler(a);

        const char * buffer;

        while (buffer)
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