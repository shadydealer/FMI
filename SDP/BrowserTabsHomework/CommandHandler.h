#pragma once
#include "LinkedList-impl.h"
#include "Tab.h"

class CommandHandler
{
  private:
    LinkedList<Tab>* reciever;
    LinkedList<Tab>::Iterator data_it;

    enum command
    {
      GO,
      INSERT,
      BACK,
      FORWARD,
      REMOVE,
      PRINT,
      SORT_URL,
      SORT_TIME,
      EXIT
    };

  private:
    CommandHandler(){};
    CommandHandler(const CommandHandler &) = delete;
    CommandHandler &operator=(const CommandHandler &) = delete;
  
  private:
    command hash_command(const char *) const;
    const char * extract_command(const char *) const;
    const char * extract_url(const char *, const size_t) const;
  private:
    void go(const char *);
    void insert(const char *);
    void back();
    void forward();
    void remove();
    void print();
public:
    CommandHandler(LinkedList<Tab> &);
    ~CommandHandler(){};
  public:
    void execute_command(const char *);
};