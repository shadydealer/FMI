#pragma once

#include <fstream>
#include "utils/avatar.h"

class Entity
{
protected:
  int x, y;
  Avatar avatar;
  
protected:
  Entity();
  Entity(const Entity &) = delete;
  Entity &operator=(const Entity &) = delete;
  ~Entity();

protected:
  virtual void set_avatar(const char *) = 0;

public:
  void move(const int, const int);
  void shoot() const;
};