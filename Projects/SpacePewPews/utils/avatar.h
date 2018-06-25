#pragma once
#include <fstream>

#include "array2D.h"
#include "execeptions.h"

#define MAX_AVATAR_DIMENSIONS 10 //so the avatar file will contain 10x10 ASCII characters \
                                 //not including end of line specifiers.

/*
  A simple class that will hold a 2d char array
  that will be the entities visual representation.  
 */

class Avatar
{
private:
  array2D<char> data;

private:
  bool valid_file(std::ifstream &) const;
  void extract_data(std::ifstream &);

public:
#pragma region Big Four
  Avatar();
  Avatar(const Avatar &);
  Avatar &operator=(const Avatar &);
  ~Avatar();
#pragma endregion

public:
  Avatar(const char *);

public:
  void open_file(const char *);
  array2D<char> get_data() const;

};