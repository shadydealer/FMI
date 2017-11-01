#include <iostream>
#include "string.h"
#include <ctime>

class LinkedList
{
  private:
    struct Node
    {
        char *url;
        Node *prev;
        Node *next;

        size_t timeStamp;

      public:
        void CopyString(const char *);

      public:
        Node();
        Node(const Node &);
        Node &operator=(const Node &);
        ~Node();

      public:
        Node(const char *);
        void Clean();
    }* dummy;

    int size;

  public:
    void Clean();

  public:
    LinkedList();
    LinkedList(const char *);
    LinkedList(const LinkedList &);
    LinkedList &operator=(const LinkedList &);
    ~LinkedList();

  public:
    void Print() const;
};