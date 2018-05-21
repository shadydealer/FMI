#pragma once
#include "Post.h"

class PicturePost : public Post
{
  public:
    PicturePost();
    PicturePost(const String &,
                const User *);

  public:

    const String generate_html_string() const override;
};