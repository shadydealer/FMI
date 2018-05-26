#pragma once

#include "PolymorphicList.h"
#include "htmlController.h"

#include "Post.h"
#include "PicturePost.h"
#include "TextPost.h"
#include "LinkPost.h"

class PostController
{
  private:
    PolymorphicList<const Post> posts;

  private:
    PolymorphicList<const Post>::Iterator _fetch_post(const unsigned int);

  public:
    bool add_post(const Post *);
    bool remove_post(const unsigned int);
    void generate_single_post_html(const String &, const unsigned int);
    void generate_full_post_history(const String &, const String &);
};