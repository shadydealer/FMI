#pragma once
#include <iostream>
#include "string.h"
#include <ctime>

template <typename T>
class LinkedList
{
private:
  struct Node
  {
    T data;
    Node *prev; //pointer to the previous node.
    Node *next; //pointer to the next node.

  public:
    Node();
    Node(const T &);
    Node(const Node &);
    Node &operator=(const Node &);
    ~Node();

  } dummy;

private:
  void copy_list(const LinkedList &);
public:

  class Iterator
  {
    friend class LinkedList;
    Node* pnode;
 
 public:
    Iterator();
    Iterator(Node *);
    Iterator(const Iterator &);
    Iterator &operator=(const Iterator &);
    ~Iterator(){};
  
  public:
    T *   operator->();
    Iterator &operator++();
    Iterator operator++(const int);
    Iterator &operator--();
    Iterator operator--(const int);
    
  public:
    bool operator!=(const Iterator &) const;
    bool operator ==(const Iterator &) const;
  };

public:
  void clean();
  Iterator beg();
  Iterator end();
public:
  LinkedList();
  LinkedList(const LinkedList &);
  LinkedList<T> &operator=(const LinkedList &);
  ~LinkedList();

public:
  void push_back(const char *);
  void insert_after(Iterator &, const char *);
  void remove_at(Iterator &);
};
