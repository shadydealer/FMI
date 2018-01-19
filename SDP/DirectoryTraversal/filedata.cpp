#include "filedata.h"

#define FILE_OPEN_FAILURE "Failed to open the file.\n";

//
// Default file_data ctor.
//

file_data::file_data() : name(), size(0), marker()
{
}

void file_data::get_file_name(const std::string & data)
{
    const char * rhs_name = data.c_str();
    int size = 0;
    size = strlen(rhs_name);

    while (*(rhs_name + size) != '/')
        --size;

    name = rhs_name + size + 1;
}

//
// file_data const char * paramter ctor.
//
file_data::file_data(const std::string& rhs_name, const char rhs_marker) : file_data()
{
    name = rhs_name;
    marker = rhs_marker;
    std::ifstream in(name.c_str(), std::ios::binary | std::ios::ate);

    if (in.is_open())
    {
        size = in.tellg();
    }

    else
    {
        puts(name.c_str());
        throw FILE_OPEN_FAILURE;
    }

    in.close();

    get_file_name(rhs_name);
}

//
// file_data copy ctor.
//
file_data::file_data(const file_data &rhs) : file_data()
{
    name = rhs.name;
    size = rhs.size;
}

//
// file_data operator=.
//
file_data &file_data::operator=(const file_data &rhs)
{
    if (this != &rhs)
    {
        name = rhs.name;
        size = rhs.size;
    }
    return *this;
}

void file_data::set_marker(const char rhs)
{
    marker = rhs;
}

//
// file_data get name method.
//
const std::string file_data::get_name() const
{
    return name;
}

//
// file_data get size method.
//
const unsigned int file_data::get_size() const
{
    return size;
}

const char file_data::get_marker() const
{
    return marker;
}