#pragma once
#include "Moderator.h"
#include "String.h"

/*
    A class which represents the Administrator.
    An administrator can do everything a Moderator can,
    but can also add/remove users and moderators from the system.
 */
class Administrator : public Moderator
{
  public:
    Administrator();
    Administrator(const String &);

  public:
    Moderator  add_moderator(const String&) const;
    User  add_user(const String&) const;
};