#include "file_map.h"

file_map::file_map() : data(), size()
{
    data.push_back(new std::vector<file_data>);
}

file_map::~file_map()
{
    std::list<std::vector<file_data> *>::iterator curr = data.begin();
    std::list<std::vector<file_data> *>::iterator next = curr;
    ++next;

    while (curr != data.end())
    {
        delete *curr;
        curr = next;
        ++next;
    }
}
const char * file_map::operator[](const std::string &file_name)
{
    std::list<std::vector<file_data> *>::iterator lit = data.begin(); //list iterator.
    std::vector<file_data>::iterator vit;                             //vector iterator.

    for (; lit != data.end(); ++lit)
    {
        vit = (*lit)->begin();
        for (; vit != (*lit)->end(); ++vit)
        {
            if (strcmp(vit->get_name(), file_name.c_str()) == 0)
                return vit->get_hash();
        }
    }
    return NULL;
}

const char * file_map::get_path(const std::string & file_hash)
{
    std::list<std::vector<file_data> *>::iterator lit = data.begin(); //list iterator.
    std::vector<file_data>::iterator vit;                             //vector iterator.

    for (; lit != data.end(); ++lit)
    {
        vit = (*lit)->begin();
        for (; vit != (*lit)->end(); ++vit)
        {
            if (strcmp(vit->get_hash(), file_hash.c_str()) == 0)
                return vit->get_name();
        }
    }
    return NULL;
}

void file_map::push_back(const std::string &file_path)
{
    file_data temp(file_path);

    std::list<std::vector<file_data> *>::iterator ep = --data.end(); //pointer to the last allocated chunk.

    //
    // Checks whether there's space in the last allocated chunk
    // and allocates another if there isn't any.
    //
    if ((*ep)->size() / CHUNK_SIZE >= 1)
    {
        data.push_back(new std::vector<file_data>(CHUNK_SIZE));
        ++ep;
    }

    //
    // Push the file_data to the end of the last allocated chunk.
    //
    (*ep)->push_back(temp);
    ++size;
}

void file_map::push_back(const file_data & temp)
{
    std::list<std::vector<file_data> *>::iterator ep = --data.end(); //pointer to the last allocated chunk.

    //
    // Checks whether there's space in the last allocated chunk
    // and allocates another if there isn't any.
    //
    if ((*ep)->size() / CHUNK_SIZE >= 1)
    {
        data.push_back(new std::vector<file_data>(CHUNK_SIZE));
        ++ep;
    }

    //
    // Push the file_data to the end of the last allocated chunk.
    //
    (*ep)->push_back(temp);
    ++size;
}

file_map::iterator::iterator() : vit(), lit()
{
}

file_map::iterator::iterator(const file_map::iterator &rhs) : iterator()
{
    vit = rhs.vit;
    lit = rhs.lit;
}

file_map::iterator &file_map::iterator::operator=(const file_map::iterator &rhs)
{
    if (this != &rhs)
    {
        vit = rhs.vit;
        lit = rhs.lit;
    }

    return *this;
}

bool file_map::iterator::operator!=(const file_map::iterator &rhs) const
{
    return vit != rhs.vit;
}

file_map::iterator &file_map::iterator::operator++()
{
    if (vit == (*lit)->end())
    {
        ++lit;
        vit = (*lit)->begin();
    }
    else
        ++vit;

    return *this;
}
file_data &file_map::iterator::operator*()
{
    return (*vit);
}

const file_data &file_map::iterator::operator*() const
{
    return (*vit);
}

file_map::iterator::operator bool() const
{
    if ((vit).operator->())
        return true;
    return false;
}

file_map::iterator file_map::iterator::operator++(const int)
{
    file_map::iterator temp;
    temp.vit = vit;
    temp.lit = lit;

    ++(*this);
    return temp;
}

file_map::iterator file_map::begin()
{
    file_map::iterator temp;
    temp.lit = data.begin();
    temp.vit = (*temp.lit)->begin();
    return temp;
}

file_map::iterator file_map::end()
{
    file_map::iterator temp;

    temp.lit = --data.end();
    temp.vit = (*temp.lit)->end();

    return temp;
}

const size_t file_map::get_size() const
{
    return size;
}