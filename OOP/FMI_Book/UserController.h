#pragma once

#include "PolymorphicList.h"
#include "User.h"
#include "Moderator.h"
#include "Administrator.h"

class UserController
{
private:
  PolymorphicList<User> users;

private:
  PolymorphicList<User>::Iterator _fetch_user(const String &);

public:
  UserController();

public:
  bool add_user(User *);
  void remove_user(const String &);
  User *fetch_user(const String &);
};