#include "Tab.h"

//
// Tab default ctor.
//
Tab::Tab() : timeStamp(time(0)), url(NULL)
{
}

//
// Tab const char * parameter ctor.
//
Tab::Tab(const char *rhs_url) : Tab()
{
    try
    {
        copy_string(rhs_url);
    }
    catch (...)
    {
        clean();
        throw;
    }
}

Tab::Tab(const Tab &rhs) : Tab()
{
    try
    {
        copy_string(rhs.url);
        timeStamp = rhs.timeStamp;
    }
    catch (...)
    {
        clean();
        throw;
    }
}

//
// Tab dtor.
//

Tab::~Tab()
{
    clean();
}

//
// Tab operator=.
//
Tab &Tab::operator=(const Tab &rhs)
{
    if (&rhs != this)
    {
        copy_string(rhs.url);
        timeStamp = rhs.timeStamp;
    }
    return *this;
}

//
// Coppies the input string into the Tabs url.
//
void Tab::copy_string(const char *rhsURL)
{
    char *buffer = new char[strlen(rhsURL) + 1];
    strcpy(buffer, rhsURL);

    delete[] url;
    url = buffer;
}

//
// Frees any allocated memory and sets the timeStamp to 0.
//
void Tab::clean()
{
    delete[] url;
    timeStamp = 0;
}

bool Tab::operator==(const Tab &rhs) const
{
    return this == &rhs;
}

//
// Sets the tabs timeStamp.
//
void Tab::set_time(const size_t rhs_timeStamp)
{
    timeStamp = rhs_timeStamp;
}

//
// Sets the tabs url.
//
void Tab::set_url(const char *rhs_url)
{
    if (rhs_url)
        copy_string(rhs_url);

    else
        delete[] url;
}

//
// Returns the current tabs timeStamp.
//

const size_t Tab::get_time() const
{
        return timeStamp;
}

//
// Rturns the current tabs url.
//

const char * Tab::get_url() const
{
    return url;
}