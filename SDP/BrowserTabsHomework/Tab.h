#pragma once
#include "iostream"
#include "string.h"

class Tab
{
  private:
    size_t timeStamp; //holds a timestamp of when the Node was created.
    char *url;        //just a url.

  private:
    void clean();
    void copy_string(const char *);

  public:
    Tab();
    Tab(const char *);
    Tab(const Tab &);
    ~Tab();

  public:
    Tab &operator=(const Tab &);
  public:
    bool operator==(const Tab &) const;

  public:
    void set_time(const size_t);
    void set_url(const char *);
    const size_t get_time() const;
    const char * get_url() const;
  public:
};