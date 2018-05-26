#pragma once

#include "PolymorphicList.h"
#include "htmlController.h"

#include "Post.h"
#include "PicturePost.h"
#include "TextPost.h"
#include "LinkPost.h"

enum PostType
{
  PICTURE_POST,
  LINK_POST,
  TEXT_POST
};

class PostController
{
private:
  PolymorphicList<Post> posts;

private:
  PolymorphicList<Post>::Iterator _fetch_post(const unsigned int);

public:
  Post *create_post(const String &, const User *, const PostType);
  void add_post(Post *);
  void remove_post(const unsigned int);
  Post * fetch_post(const unsigned int);
  void generate_single_post_html(const unsigned int);
  void generate_full_post_history(const String &);
};