#pragma once

#include <fstream>
#include "utils/avatar.h"
#include "utils/containers/Pair.h"

/*
  An enum that will represent the directions
  each entity may face.
 */
enum Direction
{
  LEFT = -1,
  RIGHT = 1
};

/* 
  A class which will serve as a base to
  all object which be displayed in the window.

 */
class Entity
{
protected:
  Pair<int, int> coords;
  Direction direction;
  Avatar avatar;

  /*
  The object creation
  methods are protected because you
  shouldn't be able to create
  entity instances, but should still be able
  to call the methods from derived classes
  to help with their own construction of instances.
 */
protected:
#pragma region Big Four
  Entity();
  Entity(const Entity &);
  Entity &operator=(const Entity &);

public:
  virtual ~Entity() = 0;

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
  const Direction &get_direction() const;
  const Avatar &get_avatar() const;

public:
  bool within_hitbox(const Pair<int, int> &) const;

public:
  void move(const int,
            const int);

};