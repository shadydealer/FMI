#include "Tab.h"

Tab::Tab() : _timeStamp(time(0)), _url(NULL)
{
    SetURL("about:blank");
}

Tab::Tab(const char *rhsURL) : Tab()
{
    SetURL(rhsURL);
}

//
// May throw std::badalloc()
//
void Tab::SetURL(const char *rhsURL)
{
    char *buffer = NULL;

    if (rhsURL != NULL)
    {
        size_t len = strlen(rhsURL);
        buffer = new char [len + 1];
        strcpy(buffer, rhsURL);
    }

    delete[] _url;
    _url = buffer;
}

Tab::Tab(const Tab &rhs) : Tab()
{
    SetURL(rhs._url);
}

Tab::~Tab()
{
    delete[] _url;
}

const char * Tab::url() const
{
    return _url;
}

const size_t Tab::timeStamp() const
{
    return _timeStamp;
}