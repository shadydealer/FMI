#pragma once

#include <iostream>

class Tab
{
  private:
    size_t accessTime;
    const char *url;

  public:
    Tab();
    Tab(const char *);
    Tab(const Tab &);
    ~Tab();

  public:
    Tab& operator=(const Tab &);
};