#include "String.h"

//Default ctor.
String::String() : data(nullptr), length(0)
{
}

/*
    Coppies the paramter cstring into the data attribute
    and sets the length attribute to the paramater cstring length.
    
    @params rhsStr - string to be coppied.

    WARNING: May throw std::bad_alloc()
 */
void String::_copy(const char *rhsStr)
{
    unsigned int rhsLen = strlen(rhsStr) + 1;
    char *temp = new char[rhsLen];

    strcpy(temp, rhsStr);

    delete[] data;
    data = temp;

    length = rhsLen;
}

//Cstring parameter ctor.
String::String(const char *rhsStr) : String()
{
    _copy(rhsStr);
}

//_copy ctor.
String::String(const String &rhs) : String()
{
    _copy(rhs.data);
}

//Dtor.
String::~String()
{
    delete[] data;
}

//String parameter operator=.
String &String::operator=(const String &rhs)
{
    if (this != &rhs)
        _copy(rhs.data);

    return *this;
}

//Cstring operator=.
String &String::operator=(const char *rhsStr)
{
    _copy(rhsStr);
}

//Operator==.
bool String::operator==(const String &rhs) const
{
    return (strcmp(data, rhs.data) == 0);
}
/*
    Moves the data from one cstring to another.

    @params dest- where the function is moving the data.
    @param from - from where the function is getting the data.
 */
void String::_move(char *dest, const char *from) const
{
    if (from)
    {
        unsigned int fromLength = strlen(from) + 1;
        strncpy(dest, from, fromLength);
    }
}

/* 
    Appends the right string to the left one.

    @params left- cstring to be appended.
    @params right- cstring whose value is appended. 
 */
void String::_append(char *left, const char *right) const
{
    if (left)
    {
        unsigned int destLength = strlen(left);
        left += destLength;
    }
    strcpy(left, right);
}

/*
    Appends the passed in string to the objects data.

    @params rhsStr- string which the function will put at the end of the objects data.
 */
void String::append(const char *rhsStr)
{
    unsigned int totalLength = strlen(rhsStr) + length + 1;
    char *temp = new char[totalLength]{0};

    _move(temp, data);
    _append(temp, rhsStr);

    delete[] data;
    data = temp;
    length = totalLength;
}

/*
    Converts an unsigned long long to a String object.

    @params number- number to be converted to string.
 */
String String::ull_to_string(unsigned long long number)
{
    char temp[MAX_ULLONG_DIGITS + 1] = {0};

    unsigned long long dummy = number;
    short digits = 0;

    while (dummy != 0)
    {
        dummy /= 10;
        ++digits;
    }

    short index = digits - 1;
    while (number != 0)
    {
        temp[index--] = '0' + number % 10;
        number /= 10;
    }

    return String(temp);
}

//length attribute getter method.
const unsigned int String::get_length() const
{
    return length;
}

//data attribute getter method.
const char *String::get_cstr() const
{
    return data;
}
