#pragma once
#include <iostream>
#include "string.h"
#include <ctime>

class LinkedList
{
private:
  struct Node
  {
    Node *prev; //pointer to the previous node.
    Node *next; //pointer to the next node.

    size_t timeStamp; //holds a timestamp of when the Node was created.
    char *url;        //just a url.

  public:
    void CopyString(const char *);
    void clean_node();

  public:
    Node();
    Node(const char *);
    Node(const Node &);
    Node &operator=(const Node &);
    ~Node();

  } * dummy;

public:
  class Iterator
  {
    Node *data;
  public:
    Iterator();
    Iterator(Node *);
    Iterator(const Iterator &);
    Iterator &operator=(const Iterator &);
    ~Iterator(){};
  
  public:
    Iterator &operator++();
    Iterator operator++(const int);
    Iterator &operator--();
    Iterator operator--(const int);
    
  public:
    Node* operator*();
    bool operator!=(const Iterator &) const;
  };

public:
  void clean();
  Iterator beg();
  Iterator end();

public:
  LinkedList();
  LinkedList(const char *);
  LinkedList(const LinkedList &);
  LinkedList &operator=(const LinkedList &);
  ~LinkedList();
public:
  void insert_after(Iterator &, const char *);
  void remove_at(Iterator &);
};
