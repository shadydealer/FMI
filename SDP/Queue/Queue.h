#pragma once
#include "iostream"

template <typename T>
class Queue
{
  private:
    struct Node
    {
      public:
        T data;
        Node *p_prev;
        Node *p_next;

      public:
        Node();
        Node(const Node &);
        Node (const T&);
        Node &operator=(const Node &) = delete;
    } sentinel;

  private:
    void copy_nodes(const Queue &);
    void clean();
  public:
    Queue();
    Queue(const Queue &);
    Queue &operator=(const Queue &);
    ~Queue();

  public:
    void push(const T &);
    T pop();
    T &head();
};