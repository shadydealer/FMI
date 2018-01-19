#pragma once
#include <fstream>
#include <string.h>

#define ADDED '+'
#define REMOVED '-'

class file_data
{
private:
  std::string name;
  unsigned int size;
  char marker;

private:
  void get_file_name(const std::string &);

public:
  file_data();
  file_data(const std::string &, const char);
  file_data(const file_data &);
  file_data &operator=(const file_data &);

public:
  void set_marker(const char);

public:
  const std::string get_name() const;
  const unsigned int get_size() const;
  const char get_marker() const;
};