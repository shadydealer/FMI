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

/* 
    Coppies the contents of the rhsStr into the data char array attribute.

    @params rhsStr- string to be coppied over.
 */
void Word::set_string(const char * rhsStr)
{
    _strcpy(rhsStr);
    flags = NONE;
}

/*
    Updates the flags FontFlags attribute.
    
    @params rhsFlag- flag to be set.
 */
void Word::set_flag(const FontFlags & rhsFlag)
{
    flags = flags | rhsFlag;
}

const char * Word::get_data() const
{
    return data;
}

const FontFlags Word::get_flags() const
{
    return flags;
}