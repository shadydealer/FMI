#pragma once
#include "Post.h"

class TextPost : public Post
{
  public:
    TextPost();
    TextPost(const String &,
             const User *);

  public:
    const String generate_html_string() const override;
};