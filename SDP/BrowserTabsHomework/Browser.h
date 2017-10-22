#pragma once
#include "Tab.h"

class Browser
{
  private:
    Tab ** _data;       //pointer to tab "chunks".
    size_t _size;     //amount of tabs currently in use.
    size_t _capacity; //amount of allocated space for tabs.

  public:
    Browser();
    ~Browser();
    Browser(const Browser &) = delete;
    Browser &operator=(const Browser &) = delete;

  public:
    const size_t size() const;
    const size_t capacity() const;
    const Tab * const * data() const;
};