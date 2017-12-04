#include "String.h"

//
// String default ctor.
//
String::String() : data(), length(0)
{
}

//
// Coppies the chars from the parameter char array.
//May throw std::bad_alloc().
//
void String::copy_string(const char *rhs_str)
{
    if (rhs_str)
    {
        length = strlen(rhs_str) + 1;
        char *buffer = new char[length];
        strcpy(buffer, rhs_str);

        delete[] data;

        data = buffer;
    }
}

//
// String paramter ctor.
//
String::String(const char *rhs_str) : String()
{
    copy_string(rhs_str);
}

//
//String copy ctor.
//
String::String(const String &rhs) : String(rhs.data)
{
}

//
//String dtor.
//
String::~String()
{
    delete[] data;
}
//
// String oeprator=.
//May throw std::bad_alloc().
//
String &String::operator=(const String &rhs)
{
    if (this != &rhs)
    {
        copy_string(rhs.data);
    }

    return *this;
}

String &String::operator=(const char *rhs)
{
    copy_string(rhs);
}
//
//  Puts the passed in char array at the nd of the data array.
//
void String::append(const char *rhs)
{
    int newLen = strlen(rhs) + 1;
    char *temp;

    if (data)
    {
        newLen += strlen(data);
        temp = new char[newLen];
        strcpy(temp, data);
        temp += strlen(data);
        strcpy(temp, rhs);
        temp -= strlen(data);
    }

    else
    {
        temp = new char[newLen];
        strcpy(temp, rhs);
    }

    length = newLen;

    delete[] data;
    data = temp;
}

String String::substr(const int from, const char delim) const
{
    String str;
    char *temp = data;
    temp = from ? temp + from : temp;

    int len = 0;
    while (*temp++ != delim)
        ++len;

    temp -= len + 1;

    char *buffer = new char[len];
    strncpy(buffer, temp, len);

    str = buffer;
    return str;
}

bool String::operator==(const String &rhs) const
{
    return strcmp(data, rhs.data) == 0;
}

bool String::operator==(const char *rhs) const
{
    return strcmp(data, rhs) == 0;
}
//
// get method for the strings data.
//
const char *String::get_data() const
{
    return data;
}

const int String::get_length() const
{
    return length;
}