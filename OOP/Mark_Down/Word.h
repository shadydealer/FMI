#pragma once
#include <string.h> //strcpy()
#include <iostream>

enum FontFlags
{
  NONE = 0,
  ITALIC = 1,
  BOLD = 2
};


inline FontFlags operator|(const FontFlags &left,
                           const FontFlags &right)
{
    return static_cast<FontFlags>(static_cast<int>(left) | static_cast<int>(right));
}

inline FontFlags operator&(const FontFlags &left,
                           const FontFlags &right)
{
  std::cout << "left: " << static_cast<int>(left) << 
            "right: " << static_cast<int>(right) << std::endl;

    return static_cast<FontFlags>(static_cast<int>(left) & static_cast<int>(right));
}

inline FontFlags operator^(const FontFlags &left,
                           const FontFlags &right)
{
    return static_cast<FontFlags>(static_cast<int>(left) ^ static_cast<int>(right));
}

class Word
{
  char *data;
  FontFlags flags;

private:
  void _strcpy(const char *);

public:
  Word();
  Word(const char *);
  Word &operator=(const Word &);
  ~Word();

public:
  void set_string(const char *);
  void set_flag(const FontFlags &);

public:
  const char *get_data() const;
  const FontFlags get_flags() const;
};