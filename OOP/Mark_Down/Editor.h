#pragma once
#include <fstream>
#include "Line.h"
#include "DynamicArray.h"

#define MAX_LINE_LENGTH 1024
#define HEADING_CHARS "#"
#define ITALIC_CHARS "_"
#define BOLD_CHARS "**"

class Editor
{
private:
  Word filePath;
  DynamicArray<Line> lines;

private:
  void _extract_data_for_editing();
  const char *_append_extension(const char *);
  void _write_format_chars(std::ofstream &, const char *);
  void _dump_word(std::ofstream &,
                  const Word &,
                  FontFlags &);
  void _dump_line(std::ofstream &,
                  const Line &);

public:
  Editor();
  Editor(const char *);

public:
  void init_file(const char *);

public:
  void make_heading(const unsigned int);
  void make_italic(const unsigned int,
                   const unsigned short,
                   const unsigned short);
  void make_bold(const unsigned int,
                 const unsigned short,
                 const unsigned short);
  void make_combine(const unsigned int,
                    const unsigned short,
                    const unsigned short);
  void add_line(const char *);
  void remove_line(const unsigned int);
  void dump_to_md();
};