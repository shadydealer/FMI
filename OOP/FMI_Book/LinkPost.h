#pragma once
#include "Post.h"

class LinkPost : public Post
{
  private:
    String description;

  public:
    LinkPost();
    LinkPost(const String &,
             const String &,
             const User *);

  public:
    const String generate_html_string() const override;
};