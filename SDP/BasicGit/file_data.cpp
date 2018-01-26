#include "file_data.h"

#define FILE_OPEN_FAILURE "Failed to open file. Please make sure the file path is correct.\n";

//
// Default file_data ctor.
//

file_data::file_data() : path(), hash()
{
}

void file_data::get_file_path(const std::string &data)
{
    std::string::iterator rhs_path = --(const_cast<std::string &>(data)).end();
    int size = 0;

    while (*(rhs_path--) != '/')
        ++size;

    strcpy(path, data.substr(data.size() - size).c_str());
}

void file_data::get_content_hash(std::ifstream &in)
{
    unsigned long long length = in.tellg();
    char *content = new char[length + 1]();
    in.seekg(0, in.beg);

    in.read(content, length);
    CryptoPP::SHA1 sha1;
    std::string str_hash;
    CryptoPP::StringSource(content, true,
                           new CryptoPP::HashFilter(sha1,
                                                    new CryptoPP::HexEncoder(new CryptoPP::StringSink(str_hash))));

    //puts(hash.c_str());

    strcpy(hash, str_hash.c_str());
    delete[] content;
}

//
// file_data const char * paramter ctor.
//
file_data::file_data(const std::string &rhs_path) : file_data()
{
    strcpy(path, rhs_path.c_str());
    std::ifstream in(path, std::ios::binary | std::ios::ate);

    if (in.is_open())
    {
        //puts(path.c_str());
        get_content_hash(in);
    }

    else
    {
        puts(path);
        throw FILE_OPEN_FAILURE;
    }

    in.close();

    get_file_path(rhs_path);
}

//
// file_data copy ctor.
//
file_data::file_data(const file_data &rhs) : file_data()
{
    strcpy(path, rhs.path);
    strcpy(hash, rhs.hash);
}

//
// file_data operator=.
//
file_data &file_data::operator=(const file_data &rhs)
{
    if (this != &rhs)
    {
        strcpy(path, rhs.path);
        strcpy(hash, rhs.hash);
    }
    return *this;
}

void file_data::set_path(const char rhs_path[PATH_LENGTH])
{
    if (rhs_path != NULL)
        strcpy(path, rhs_path);
}


void file_data::set_hash(const char rhs_hash[HASH_LENGTH])
{
    if (rhs_hash != NULL)
        strcpy(hash, rhs_hash);
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
const char *file_data::get_hash() const
{
    return hash;
}
