#include "filedata.h"

#define FILE_OPEN_FAILURE "Failed to open the file.\n";

//
// Default file_data ctor.
//

file_data::file_data() : path(NULL), size(0)
{
}

//
// Coppies the path to the file from the passed in char array.
// May throw std::bad_alloc()
//
void file_data::copy_path(const char *rhs_path)
{
    if (rhs_path)
    {
        char *temp = new char[strlen(rhs_path) + 1];

        strcpy(temp, rhs_path);
        delete[] path;
        path = temp;
    }
    else
        delete[] path;
}
//
// file_data const char * paramter ctor.
//
file_data::file_data(const char *rhs_path) : file_data()
{
    copy_path(rhs_path);
    std::ifstream in(path, std::ios::binary | std::ios::ate);

    if (in.is_open())
    {
        if (in.tellg() == -1)
            throw "d";

        size = in.tellg();
        in.close();
    }

    else
        throw FILE_OPEN_FAILURE;
}

//
// file_data copy ctor.
//
file_data::file_data(const file_data &rhs) : file_data()
{
    copy_path(rhs.path);
    size = rhs.size;
}

//
// file_data operator=.
//
file_data &file_data::operator=(const file_data &rhs)
{
    if (this != &rhs)
    {
        copy_path(rhs.path);
        size = rhs.size;
    }
    return *this;
}

//
// file_data dtor.
//

file_data::~file_data()
{
    delete[] path;
}

//
// file_data set path method.
// NOTE: also alters the size member.
//
void file_data::set_path(const char *rhs_path)
{
    copy_path(rhs_path);
    size = rhs_path ? strlen(rhs_path) : 0;
}

//
// file_data get path method.
//
const char *file_data::get_path() const
{
    return path;
}

//
// file_data get size method.
//
const unsigned int file_data::get_size() const
{
    return size;
}