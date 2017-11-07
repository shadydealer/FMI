#pragma once
#include "iostream"
#include "string.h"

class InputReader
{

private:
  InputReader(){};
  InputReader(const InputReader &) = delete;
  InputReader &operator=(const InputReader &) = delete;

public:
  ~InputReader(){};

public:
  static const char *get_input();
};