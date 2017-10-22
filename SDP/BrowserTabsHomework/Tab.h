#pragma once

#include <iostream>
#include "string.h"

class Tab
{
  private:
    size_t _timeStamp;
    const char * _url;

  private:
    void SetURL(const char *);

  public:
    Tab();
    Tab(const char *);
    Tab(const Tab &);
    ~Tab();

  public:
    Tab& operator=(const Tab &);
  
  public:
    const size_t timeStamp() const;
    const char * url() const;
};