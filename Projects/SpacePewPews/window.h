#pragma once
#include "utils/execeptions.h"

#include "utils/containers/array2D.h"
#include "utils/containers/linked_list.h"

#include "entity.h"
#include "bullet.h"
#include "character.h"

#define DEFAULT_HEIGHT 35
#define DEFAULT_WIDTH 145

#define EMPTY_TILE ' '
#define VERTICAL_BORDER_TILE '|'
#define HORIZONTAL_BORDER_TILE '-'

class Window
{
private:
  int width, height;
  array2D<char> map;

  LinkedList<Bullet> bullets;
  LinkedList<Character> enemies;
  Character player;

private:
  void set_entity_starting_position(Entity *,
                                    const int);

public:
  void generate_map();
  void clear() const;

#pragma region Big Four
public:
  Window();
  Window(const Window &) = delete;
  Window &operator=(const Window &) = delete;
  ~Window();
#pragma endregion

public:
  Window(const int, const int);

public:
  void draw();
};