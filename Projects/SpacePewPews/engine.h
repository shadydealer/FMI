#pragma once
#include <stdio.h>
#include <termios.h>

#include "utils/game_objects/character.h"
#include "utils/game_objects/bullet.h"
#include "utils/containers/dynamic_array.h"
#include "utils/window.h"
#include "utils/handlers/command_handler.h"

enum Dificulty
{
  NONE = 0,
  EASY = 10,
  MEDIUM = 5,
  HARD = 1
};

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

  Dificulty dificulty;

private:
  void set_keyboard_blocking(termios *);
  void set_keyboard_non_blocking(termios *);
private:
  bool hasPickedDificulty();
public:
  Engine();
  Engine(const Engine &) = delete;
  Engine &operator=(const Engine &) = delete;
  ~Engine(){};

public:
  void run();
};