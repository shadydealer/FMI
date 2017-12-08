#pragma once
#include <iostream>

#include "examData.h"

class linked_list
{
private:
  struct node
  {
  public:
    char data;      //will hold the character which we've currently read from the string.
    node **next;
    const examData *obj;  //NULL if the character that data is pointing to is not the last character.

  public:
    node();
    node(const char );
    ~node();
  } * *nodes;

  int size;
private:
  void add(node *&,const char);
public:
  linked_list();
  linked_list(const int );
  ~linked_list();

public:
  void push(const examData &);
};
