#pragma once
#include "String.h"

#include <stdio.h>

class Moderator;
class Administrator;

/*
    A class which represents the base user.
    A base user can only post and change it's own nickname. 
 */
class User
{
private:
  String nickname;
  bool isBlocked;

public:
  User();
  User(const String &);

  /*
        The destructor is virtual because
        we will be using pointers of this type
        as containers for derived objects.

        This ensures that 
        the derived constructors will be called.
  */
  virtual ~User();

public:
  bool operator==(const User &);

public:
  void change_nickname(const String &);
  void block_unblock();

public:
  const String &get_nickname() const;
  const bool is_blocked() const;
};