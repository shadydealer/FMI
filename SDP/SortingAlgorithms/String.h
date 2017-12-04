#pragma once
#include <iostream>
#include <string.h>

class String
{
private:
  char *data;
  int length;

private:
  void copy_string(const char *);

public:
  String();
  String(const char *);
  String(const String &);
  ~String();
  String &operator=(const String &);
  String &operator=(const char *);

public:
  void append(const char *);
  String substr(const int = 0, const char = 0) const;

public:
  bool operator==(const String&) const;
  bool operator==(const char*) const;

public:
  const char *get_data() const;
  const int get_length() const;
};