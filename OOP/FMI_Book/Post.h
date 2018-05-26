#pragma once
#include <fstream>

#include "String.h"
#include "User.h"

/*
    An abstract class that serves as a base for all types of posts.
*/
class Post
{
  protected:
    String data;
    unsigned long long id;
    const User * creator;
  
  protected:
    Post();
    Post(const String &,
         const User *);

  public:
    virtual ~Post(){};

  public:
    virtual const String generate_html_string() const =0;
    unsigned int get_id() const;
    const User* get_creator() const;
};