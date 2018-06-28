#pragma once
#include "entity.h"

#define DEFAULT_PLAYER_AVATAR_PATH "assets/character_avatars/player_avatar.txt"

/*
  A simple Character class that will
  represent the player and enemy objects.
 */
class Character : public Entity
{
#pragma region Big Four
public:
  Character();
  Character(const Character &);
  Character &operator=(const Character &);
  ~Character();
#pragma endregion

public:
  Character(const int,
            const int,
            const Direction,
            const char *);

public:
  Pair<int, int> shoot() const;
};