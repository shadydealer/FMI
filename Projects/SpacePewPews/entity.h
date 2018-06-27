#pragma once

#include <fstream>
#include "utils/avatar.h"
#include "utils/containers/Pair.h"

enum Direction{
  LEFT = -1,
  RIGHT = 1
};

class Entity
{
protected:
  Pair<int, int> coords;
  Direction direction;
  Avatar avatar;

protected:

#pragma region Big Four
  Entity();
  Entity(const Entity &);
  Entity &operator=(const Entity &);

public:
  virtual ~Entity();

#pragma endregion

protected:
  Entity(const int,
         const int,
         const Direction,
         const char *);

public:
  void set_avatar(const char *);

public:
  const Pair<int, int> &get_coords() const;
  const Direction& get_direction() const;
  const Avatar &get_avatar() const;

public:
  virtual void move(const int,
                    const int);
};