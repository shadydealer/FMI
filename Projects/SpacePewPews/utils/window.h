#pragma once
#include "execeptions.h"

#include "containers/array2D.h"
#include "containers/dynamic_array.h"

#include "game_objects/character.h"
#include "game_objects/bullet.h"

#define DEFAULT_HEIGHT 20
#define DEFAULT_WIDTH 60

#define EMPTY_TILE ' '
#define VERTICAL_BORDER_TILE '|'
#define HORIZONTAL_BORDER_TILE '-'

#define DEFAULT_CLEAR_SPEED 70000

class Window
{
private:
  static Window instance;
  int width, height;
  array2D<char> map;

  DynamicArray<Bullet> *bullets;
  DynamicArray<Character> *enemies;
  Character *player;

#pragma region Big Four
private:
  Window(){};

public:
  Window(const Window &) = delete;
  Window &operator=(const Window &) = delete;
  ~Window(){};
#pragma endregion

private:
  void generate_map();

public:
  void init(const int,
            const int,
            DynamicArray<Bullet> &,
            DynamicArray<Character> &,
            Character &);

public:
  static Window *get_instance();

public:
  void print_level_menu() const;

public:
  void clear() const;
  void print_stats() const;
  void draw();
};