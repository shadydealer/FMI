#pragma once
#include "UserController.h"
#include "PostController.h"

class FMIBook
{
private:
  Administrator admin;
  UserController users;
  PostController posts;

public:
  FMIBook() = delete;
  FMIBook(const String &, const unsigned int);

public:
  void add_user(const String &, const unsigned int);
  void add_moderator(const String &, const unsigned int);
  void remove_user(const String &);
  void block_user(const String &, const String &);
  void unblock_user(const String &, const String &);
  void change_nickname(const String &, const String &);

public:
  void make_post(const String &, const String &, const String &);
  void remove_post(const String &, const unsigned long long);
  void look_at_single_post(const unsigned int);
  void look_at_all_posts(const String &);

public:
  Administrator& get_admin();
};