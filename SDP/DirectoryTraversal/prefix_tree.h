#pragma once
#include <string.h>
#include <iostream>

#include "filedata.h"
#include "dynamic_array.h"
#include "linked_list.h"

class prefix_tree
{
private:
  struct node
  {
  public:
    std::string directory;
    linked_list<file_data> files;
    linked_list<node *> folders;

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
    linked_list<node *>::iterator it;

  public:
    iterator();
    iterator(node &);
    iterator &operator=(const iterator &);

  public:
    iterator operator++(const int);
    operator bool();
    std::string &operator*();
    const std::string &operator*() const;
  };

public:
  prefix_tree();
  prefix_tree(const std::string &);

public:
  void print();

private:
  void _print(std::string, node *) const;
public:
  iterator push_folder(const prefix_tree::iterator &, const std::string &);
  void push_file(const prefix_tree::iterator &, const std::string &, const char);
public:
  bool check_files(const std::string &, prefix_tree::iterator&);

  prefix_tree::iterator get_root();
};