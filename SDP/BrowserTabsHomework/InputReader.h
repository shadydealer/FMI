#pragma once
#include "iostream"

class InputReader
{
  private:
    InputReader(){};
    InputReader(const InputReader &) = delete;
    InputReader &operator=(const InputReader &) = delete;

  public:
    ~InputReader(){};

  public:
    static const char * get_input();
};