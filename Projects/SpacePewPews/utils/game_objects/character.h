#pragma once
#include "entity.h"

#define DEFAULT_PLAYER_AVATAR_PATH "assets/character_avatars/player_avatar.txt"
#define DEFAULT_ENEMY_AVATAR_PATH "assets/character_avatars/enemy_avatar.txt"

#define DEFAULT_CHARACTER_LIVES 1
/*
  A simple Character class that will
  represent the player and enemy objects.
 */
class Character : public Entity
{
private:
  int lives;

#pragma region Big Four
public:
  Character();
  Character(const Character &);
  Character &operator=(const Character &);
  ~Character();
#pragma endregion

public:
  Character(const char *,
            const int,
            const int,
            const int,
            const Direction);

  Character(const Avatar &,
            const int,
            const int,
            const int,
            const Direction);

public:
  Pair<int, int> shoot() const;
  void take_damage();
  
public:
  const int get_lives() const;

public:
  const bool is_alive() const;
};