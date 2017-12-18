#pragma once
#include <fstream>
#include <string.h>

class file_data
{
  private:
    char *path;
    unsigned int size;

  private:
    void copy_path(const char *);

  public:
    file_data();
    file_data(const char *);
    file_data(const file_data &);
    file_data &operator=(const file_data &);
    ~file_data();

  public:
    void set_path(const char*);
    
  public:
    const char *get_path() const;
    const unsigned int get_size() const;
};