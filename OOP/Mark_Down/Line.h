#pragma once
#include "Word.h"
#include "DynamicArray.h"

class Line
{
private:
  DynamicArray<Word> words;
  bool isHeading;

private:
  void _add_word(const char *, unsigned short);
  void _strncpy(char *,
                const char *,
                unsigned short);
  bool _is_white_space(const char);
  void _extract_words(const char *);

public:
  Line();
  Line(const char *);
  Line &operator=(const Line &);

public:
  Word &operator[](unsigned int);
  const Word & operator[](unsigned int) const;
public:
  void make_heading();
  void set_font(const unsigned short,
                const unsigned short,
                const FontFlags);

public:
  const unsigned int get_word_count() const;
  bool is_heading() const;
};