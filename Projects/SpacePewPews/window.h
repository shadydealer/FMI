#pragma once
#include "utils/array2D.h"

class Window
{
  private:
    int width, height;
    array2D<char> map;

  public:
    void generate_map();
    void clear() const;
    
  public:
    Window();
    Window(const int, const int);
    ~Window();
  public:
    void draw() const;
};