#pragma once
#include <string.h> //strlen(), strcpy()

#define MAX_ULLONG_DIGITS 20

class String
{
private:
  char *data;
  unsigned int length;

private:
  void _copy(const char *);
  void _move(char *, const char *) const;
  void _append(char *, const char *) const;

public:
  String();
  String(const String &);
  String &operator=(const String &);
  ~String();

  String(const char *);
  String &operator=(const char *);

public:
  bool operator==(const String &) const;
  bool operator==(const char *) const;
  bool operator!=(const String &) const;
  bool operator!=(const char *) const;
public:
  void append(const char *);
  static String ull_to_string(unsigned long long);

public:
  const unsigned int get_length() const;
  const char *get_cstr() const;
};