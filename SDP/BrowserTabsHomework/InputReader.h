#pragma once
#include "iostream"
#include "string.h"

class InputReader
{

private:
  InputReader(){};
  InputReader(const InputReader &) = delete;
  InputReader &operator=(const InputReader &) = delete;

private:
  static bool valid_command(const char *);

public:
  ~InputReader(){};

public:
  static const char *get_input();
};