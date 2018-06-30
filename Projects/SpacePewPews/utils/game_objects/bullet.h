#pragma once
#include "entity.h"

#define DEFAULT_BULLET_FILE_PATH "assets/bullets/default_bullet.txt"

class Bullet : public Entity
{
#pragma region Big Four
public:
  Bullet();
  Bullet(const Bullet &);
  Bullet &operator=(const Bullet &);
  ~Bullet();

#pragma endregion

public:
  Bullet(const int,
         const int,
         const Direction,
         const char * = DEFAULT_BULLET_FILE_PATH);
};