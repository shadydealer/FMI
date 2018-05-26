#pragma once
#include "User.h"
#include "String.h"


/*
    A class which represents the Moderator.
    A moderator can do everything a User can
    but can also block/unblock other 
    users, moderators or administrators.
 */
class Moderator:public User
{
  public:
    Moderator();
    Moderator(const String &, const unsigned int);
  
  public:
    void block(User &);
    void unblock(User &);
};