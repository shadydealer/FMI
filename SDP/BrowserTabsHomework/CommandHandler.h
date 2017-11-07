#pragma once
#include "LinkedList.h"

class CommandHandler
{
  private:
    LinkedList* data;
    LinkedList::Iterator data_it;

  private:
    CommandHandler(){};
    CommandHandler(const CommandHandler &) = delete;
    CommandHandler &operator=(const CommandHandler &) = delete;
  private:
    void go(const char *);
    void insert(const char *);
    void back();
    void forward();
    void remove();
    void print();
public:
    CommandHandler(LinkedList &);
    ~CommandHandler(){};
  public:
    void execute_command(const char *);
};