#pragma once
#include <iostream>
#include <string.h>
#include <list>


#include "file_map.h"

class prefix_tree
{
private:
  struct node
  {
  public:
    std::string directory;
    file_map files;
    std::list<node *> folders;

  public:
    node();
    node(const std::string &);
    ~node();
  } root;

public:
  class iterator
  {
    friend class prefix_tree;

  private:
    node *data;

  public:
    iterator();
    iterator(node &);
    iterator &operator=(const iterator &);

  public:
    operator bool();
    node * operator->();
  };

public:
  prefix_tree();
  prefix_tree(const std::string &);

public:
  void print();

private:
  void _print(std::string, node *) const;
public:
  prefix_tree::iterator push_folder(const prefix_tree::iterator &, const std::string &);
  void push_file(const prefix_tree::iterator &, const std::string &);
public:
  prefix_tree::iterator get_root();
};