#pragma once
#include <fstream>
#include <string.h>

#include <crypto++/sha.h>
#include <cryptopp/hex.h>

#define PATH_LENGTH 261
#define HASH_LENGTH 41

class file_data
{
private:
  char path[PATH_LENGTH];
  char hash[HASH_LENGTH];

private:
  void get_file_path(const std::string &);
  void get_content_hash(std::ifstream &);

public:
  file_data();
  file_data(const std::string &);
  file_data(const file_data &);
  file_data &operator=(const file_data &);

public:
  void set_path(const char[PATH_LENGTH]);
  void set_hash(const char[HASH_LENGTH]);

public:
  const char *get_path() const;
  const char *get_hash() const;
};