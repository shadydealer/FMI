#include "Line.h"

Line::Line() : words(), isHeading(false)
{
}

Line::Line(const char *str) : Line()
{
    _extract_words(str);
}

Line &Line::operator=(const Line &rhs)
{
    if (this != &rhs)
    {
        words = rhs.words;
    }

    return *this;
}
void Line::_strncpy(char *dest,
                    const char *from,
                    unsigned short size)
{
    for (unsigned int i = 0; i < size; ++i)
        dest[i] = from[i];
}

bool Line::_is_white_space(const char rhsChar)
{
    return (rhsChar == ' ' || rhsChar == '\t' || rhsChar == '\n');
}

void Line::_add_word(const char *word, unsigned short wordLen)
{
    char *tempString = new char[wordLen + 1];

    _strncpy(tempString,
             word,
             wordLen);

    tempString[wordLen] = 0;

    words.push_back(Word(tempString));

    delete[] tempString;
}
void Line::_extract_words(const char *str)
{
    unsigned int currWordLen = 0;
    const char *iterator = str;

    while (*iterator)
    {
        if (_is_white_space(*iterator))
        {
            _add_word(iterator - (currWordLen),
                      currWordLen);
            currWordLen = 0;
        }
        else
            ++currWordLen;
        ++iterator;
    }

    _add_word(iterator - (currWordLen),
              currWordLen);
}

Word &Line::operator[](const unsigned int index)
{
    return words[index];
}

const Word &Line::operator[](const unsigned int index) const
{
    return words[index];
}

void Line::make_heading()
{
    isHeading = true;
}

void Line::set_font(const unsigned short from,
                    const unsigned short to,
                    const FontFlags font)
{
    for (unsigned short w = from - 1; w < to; ++w)
        words[w].set_flag(font);
}

const unsigned int Line::get_word_count() const
{
    return words.get_size();
}

bool Line::is_heading() const
{
    return isHeading;
}
