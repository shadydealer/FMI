#pragma once
#include "utils/containers/array2D.h"
#include "utils/containers/linked_list.h"

#include "bullet.h"

#define DEFAULT_HEIGHT 35
#define DEFAULT_WIDTH 145

#define EMPTY_TILE ' '
#define HORIZONTAL_BORDER_TILE '|'
#define VERTICAL_BORDER_TILE '-'

class Window
{
  private:
    int width, height;
    array2D<char> map;
    LinkedList<Bullet> bullets;

  public:
    void generate_map();
    void clear() const;
    
  public:
    Window();
    Window(const int, const int);
    ~Window();
  public:
    void draw();
};