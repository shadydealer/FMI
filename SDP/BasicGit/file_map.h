#pragma once
#include "file_data.h"

#include <list>
#include <vector>

#define CHUNK_SIZE 256

class file_map
{
  private:
    std::list<std::vector<file_data> *> data;
    size_t size;

  public:
    file_map();
    file_map &operator=(const file_map &) = delete;
    file_map(const file_map &) = delete;
    ~file_map();

  public:
    //
    //Returns the file content hash by given file name.
    //If it fails to find the file push_back is called.
    //
    const char * operator[](const std::string &);
    const char * get_path(const std::string &);

  public:
    void push_back(const std::string &);
    void push_back(const file_data &);

  public:
    class iterator
    {
        friend class file_map;
        std::vector<file_data>::iterator vit;              //vector iterator.
        std::list<std::vector<file_data> *>::iterator lit; //list iterator.

      public:
        iterator();
        iterator(const iterator &);
        iterator &operator=(const iterator &);

      public:

        bool operator !=(const iterator &) const;
        file_data& operator*();
        const file_data& operator*() const;
        operator bool() const;
      public:
        iterator &operator++();
        iterator operator++(const int);
    };

    iterator begin();
    iterator end();

    public:
    const size_t get_size() const;
};