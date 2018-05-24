#pragma once
#include <fstream>

#include "String.h"

/*
    A class that will be used to manage html files.

    There's a single function here for now, but this allows for easier
    refactoring and for building better human readable code. 
 */
class HTMLController
{
  private:
    HTMLController();

  public:
    static bool create_html_file(const String &, const String &);
};