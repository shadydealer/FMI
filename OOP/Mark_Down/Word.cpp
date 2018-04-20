#include "Word.h"

Word::Word(): data(NULL), flags(NONE)
{}

Word::Word(const char * rhsStr) : Word()
{
    _strcpy(rhsStr);
}

/*
 Coppies a string into our objects data char array.

    @param rhsStr - string to be coppied.
    
    WARNING:
    May throw std::bad_alloc()
*/
void Word::_strcpy(const char * rhsStr)
{
    unsigned short rhsStrLen = strlen(rhsStr) + 1;
    char * temp = new char[rhsStrLen];

    strcpy(temp, rhsStr);
    
    delete[] data;
    data = temp;
}

Word& Word::operator=(const Word & rhs)
{
    if(this != &rhs)
    {
        _strcpy(rhs.data);
        flags = rhs.flags;
    }
    return *this;
}
Word::~Word()
{
    delete[] data;
}

void Word::set_string(const char * rhsStr)
{
    _strcpy(rhsStr);
    flags = NONE;
}

void Word::set_flag(const FontFlags & rhs_flag)
{
    flags = flags | rhs_flag;
}

const char * Word::get_data() const
{
    return data;
}

const FontFlags Word::get_flags() const
{
    return flags;
}