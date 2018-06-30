#pragma once

#include "../containers/dynamic_array.h"
#include "../game_objects/entity.h"
#include "../game_objects/character.h"
#include "../game_objects/bullet.h"

class CommandHandler
{
private:
  static CommandHandler instance;

  int mapWidth, mapHeight;
  DynamicArray<Bullet> *bullets;
  DynamicArray<Character> *enemies;
  Character *player;

private:
  void set_character_starting_pos(Character &,
                                  const int);
  bool is_within_bounds(const Entity *,
                        const int,
                        const int) const;

  bool hitboxes_collide(const Entity *, const Entity *) const;
  bool collide(const Entity *);
#pragma region Big Four
private:
  CommandHandler(){};

public:
  CommandHandler(const CommandHandler &) = delete;
  CommandHandler &operator=(const CommandHandler &) = delete;
  ~CommandHandler(){};
#pragma endregion

public:
  void init(const int,
            const int,
            DynamicArray<Bullet> &,
            DynamicArray<Character> &,
            Character &);

public:
  void character_shoot(const Character &);

public:
  void move_enemies();
  void move_bullets();
  void move_player(const int,
                   const int);

public:
  void clean_up_objects();

public:
  void spawn_enemies(const int);

public:
  static CommandHandler *get_instance();

public:
  Character *get_player();
  DynamicArray<Character> *get_enemies();
  DynamicArray<Bullet> *get_bullets();
};