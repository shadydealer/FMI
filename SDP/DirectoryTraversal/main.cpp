#include <iostream>
#include "filedata.h"

#define ALLOC_FAILURE "Failed to allocate enough memory.\n";

int main()
{
    try
    {
        
    }
    catch(std::bad_alloc())
    {
        throw ALLOC_FAILURE;
    }
    catch(const char * msg)
    {
        std::cout << msg;
    }
    return 0;
}