#include "InputReader.h"

const char *InputReader::get_input()
{
    size_t length = 10;
    char *buffer = new char[length];

    while (std::cin.getline(buffer, length))
    {
        
    }
}