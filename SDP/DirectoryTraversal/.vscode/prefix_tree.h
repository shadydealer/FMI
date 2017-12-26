#pragma once
#include "String.h"

#define MAX_KEYS 3;
#define FILE 1;
#define DIR 0;

class prefix_tree
{
private:
  struct node
  {
  public:
    String keys[MAX_KEYS];
    node *first,
        *second,
        *third,
        *fourth;
    bool type;

  public:
    node();
    node(const String &);
    node &operator=(const node &);
  } * root;

private:
  void clean(node *);

public:
  prefix_tree();
  ~prefix_tree();

public:
  void insert(const String &);
  void pop(const String &);
};