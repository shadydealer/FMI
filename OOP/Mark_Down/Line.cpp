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

/* 
    Coppies n character into one char array from another.

    @params dest- char buffer which will store the coppied string.
    @params from- char buffer which we'll be copying from.
    @params size- amount of chars to be coppied over.
*/
void Line::_strncpy(char *dest,
                    const char *from,
                    unsigned short size)
{
    for (unsigned int i = 0; i < size; ++i)
        dest[i] = from[i];
}

/* 
    Checks whether a char is a whitespace char.

    @params rhsChar- char to be checked.
 */
bool Line::_is_white_space(const char rhsChar)
{
    return (rhsChar == ' ' || rhsChar == '\t' || rhsChar == '\n');
}

/*
    Creates a new Word object by given string
    and stores it into the DynamicArray<Word> words attribute.

    @params word- char pointer to the beginning of the word to be extracted.
    @params wordLen- amount of chars to be coppied over beggining from the word pointer.
 
    WARNING:
    May throw std::bad_alloc
 */
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

/*
    Extracts each individual word from 
    given string and stores it in
    the words DynamicArray<Word> words
    by calling the _add_word() method.

    @param str- string to be "disected".
*/
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

/*
    Sets the isHeading bool flag to true.
 */
void Line::make_heading()
{
    isHeading = true;
}

/*
    Sets the font of a range of words.

    @params from- index of the word to start iterating from.
    @params to- index of the word to which we have to iterate.
    @params font- font flag to be set for the words in the given range.

    WARNING:
    May throw std::out_of_range
*/
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
