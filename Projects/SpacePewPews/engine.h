#pragma once
#include <stdio.h>
#include <termios.h>

#include "utils/game_objects/character.h"
#include "utils/game_objects/bullet.h"
#include "utils/containers/dynamic_array.h"
#include "utils/window.h"
#include "utils/handlers/command_handler.h"

class Engine
{
private:
  DynamicArray<Character> enemies;
  DynamicArray<Bullet> bullets;
  Character player;

  int winHeight;
  int winWidth;

  CommandHandler *handler;
  Window *window;

private:
  void set_keyboard_blocking(termios *);
  void set_keyboard_non_blocking(termios *);

public:
  Engine();
  Engine(const Engine &) = delete;
  Engine &operator=(const Engine &) = delete;
  ~Engine(){};

public:
  void run();
};