#pragma once

#include "PolymorphicList.h"
#include "User.h"
#include "Moderator.h"
#include "Administrator.h"

enum UserType
{
  USER,
  MODERATOR
};

class UserController
{
private:
  PolymorphicList<User> users;

private:
  PolymorphicList<User>::Iterator _fetch_user(const String &);

public:
  UserController();

public:
  void add_user(const String &, const unsigned int, const UserType);
  void remove_user(const String &);
  User *fetch_user(const String &);
  
  void block_user(const String &, const String &);
  void unblock_user(const String &, const String &);
};