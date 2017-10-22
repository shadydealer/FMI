#include "Browser.h"

#define CHUNK_SIZE 20

Browser::Browser() : _data(new Tab*(new Tab[CHUNK_SIZE])),
                     _size(0),
                     _capacity(CHUNK_SIZE)
{
}


Browser::~Browser()
{
    size_t chunks = _capacity / CHUNK_SIZE;
    
    for(size_t c = 0; c < chunks; ++c)
        delete[] _data[c];
    delete[] _data;
}

const size_t Browser::size() const
{
    return _size;
}

const size_t Browser::capacity() const
{
    return _capacity;
}

const Tab * const * Browser::data() const
{
    return _data;
}