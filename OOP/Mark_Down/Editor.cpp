#include "Editor.h"
#include <iostream>

Editor::Editor() : filePath(), lines()
{
}

Editor::Editor(const char *rhsFilePath) : filePath(rhsFilePath), lines()
{
    _extract_data_for_editing();
}

/* 
    Sets the filePath Word attribute to a new FileName
    and extracts the files data for editing.

    @params rhsFilePath- str containing the file path.

    NOTE:
    The rhsFilePath should NOT contain the .txt extension.
 */
void Editor::init_file(const char *rhsFilePath)
{
    filePath.set_string(rhsFilePath);
    _extract_data_for_editing();
}
/* 
    Appends a specified extension
    to a copy of the FilePath's data attribute.

    @params extension- extension to be appened to the end of the coppied string.

    @return- copy of the FilePath's data attribute
    appended with the extension string.
 */
const char *Editor::_append_extension(const char *extension)
{
    unsigned short filePathLength = strlen(filePath.get_data());
    unsigned short extensionLength = strlen(extension);

    char *result = new char[filePathLength + extensionLength + 1];
    strcpy(result, filePath.get_data());
    result += filePathLength;
    strcpy(result, extension);
    result -= filePathLength;

    return result;
}

/* 
    Extracts the file's data line by line
    and stores it in the DynamicArray<Line> lines attribute.
 */
void Editor::_extract_data_for_editing()
{
    const char *tempPath = _append_extension(".txt");

    std::ifstream in(tempPath);

    if (in.is_open())
    {
        char currLine[MAX_LINE_LENGTH + 1];

        while (in.getline(currLine, MAX_LINE_LENGTH + 1))
        {
            if (strcmp(currLine, "") != 0)
            {
                std::cout << currLine << std::endl;
                lines.push_back(currLine);
            }
        }

        in.close();

        delete[] tempPath;
    }

    else
    {
        delete[] tempPath;
        throw "Invalid file path.\n";
    }
}

/*
    Sets a line's heading attribute by given line index.

    @params lineIndex- index of the line which flag we'll be setting.
    
    WARNING:
    May throw std::out_of_range()
 */
void Editor::make_heading(const unsigned int lineIndex)
{
    lines[lineIndex].make_heading();
}

/*
    Sets the FontFlags flags attrbute of a given range of words
    in a specific line to italic.

    @params lineIndex- index of the line which words' flags we're altering.
    @params fromWord- index of the first word which flag will be changed.
    @params toWord- index of the last word which flag will be changed.

    WARNING:
    MAy throw std::out_of_range()
*/
void Editor::make_italic(const unsigned int lineIndex,
                         const unsigned short fromWord,
                         const unsigned short toWord)
{
    for (unsigned short w = fromWord; w <= toWord; ++w)
        lines[lineIndex][w].set_flag(ITALIC);
}
/*
    Sets the FontFlags flags attrbute of a given range of words
    in a specific line to bold.

    @params lineIndex- index of the line which words' flags we're altering.
    @params fromWord- index of the first word which flag will be changed.
    @params toWord- index of the last word which flag will be changed.

    WARNING:
    MAy throw std::out_of_range()
*/
void Editor::make_bold(const unsigned int lineIndex,
                       const unsigned short fromWord,
                       const unsigned short toWord)
{
    for (unsigned short w = fromWord; w <= toWord; ++w)
        lines[lineIndex][w].set_flag(BOLD);
}

/*
    Sets the FontFlags flags attrbute of a given range of words
    in a specific line to bold and italic.

    @params lineIndex- index of the line which words' flags we're altering.
    @params fromWord- index of the first word which flag will be changed.
    @params toWord- index of the last word which flag will be changed.

    WARNING:
    MAy throw std::out_of_range()
*/
void Editor::make_combine(const unsigned int lineIndex,
                          const unsigned short fromWord,
                          const unsigned short toWord)
{
    for (unsigned short w = fromWord; w <= toWord; ++w)
        lines[lineIndex][w].set_flag((ITALIC | BOLD));
}

/*
    Adds a new line to the DynamicArray<Line> lines attribute.

    @params rhsLine- line to be added.
 */
void Editor::add_line(const char *rhsLine)
{
    lines.push_back(rhsLine);
}

/* 
    Removes a line from the DynamicArray<Line> lines attribute by given index.

    @params lineIndex- index of the line to be removed.

    WARNING:
    May throw std::out_of_range()
 */
void Editor::remove_line(const unsigned int lineIndex)
{
    lines.remove(lineIndex);
}

/* 
    Writes the given format chars into a binary file.

    @params out- binary file stream.
    @params chars- format char we have to write into the stream object.
*/
void Editor::_write_format_chars(std::ofstream &out, const char *chars)
{
    if (out.good())
        out.write(chars, strlen(chars));
    else
        throw "Bad output stream state.";
}

/*
    Writes the given word into a binary file,
    while appending any font chars needed specified by the flags parameter.

    @params out- binary file stream.
    @params word- word to be written into the binary file.
    @params flags- flags to be checked for each word.
 */
void Editor::_dump_word(std::ofstream &out,
                        const Word &word,
                        FontFlags &flags)
{
    if (out.good())
    {
        if (flags == NONE)
        {
            flags = flags | word.get_flags();

            if (flags & BOLD)
                _write_format_chars(out, BOLD_CHARS);

            if (flags & ITALIC)
                _write_format_chars(out, ITALIC_CHARS);
        }

        else if (!(flags & word.get_flags()))
        {
            if ((flags & ITALIC))
            {
                flags = flags ^ ITALIC;
                _write_format_chars(out, ITALIC_CHARS);
            }

            if ((flags & BOLD))
            {
                flags = flags ^ BOLD;
                _write_format_chars(out, BOLD_CHARS);
            }
        }

        out.write(word.get_data(), strlen(word.get_data()));
    }
}

/* 
    Writes a whole line into a binary file.

    @params out- binary file stream.
    @params line- line to be written in the binary file.
 */
void Editor::_dump_line(std::ofstream &out,
                        const Line &line)
{
    if (out.good())
    {
        if (line.is_heading())
            _write_format_chars(out, HEADING_CHARS);

        unsigned int wordCount = line.get_word_count();

        FontFlags currFlags = NONE;
        for (unsigned int word = 0; word < wordCount - 1; ++word)
        {
            _dump_word(out, line[word], currFlags);
            out.write(" ", 1);
        }

        _dump_word(out, line[wordCount - 1], currFlags);

        if (currFlags & ITALIC)
            _write_format_chars(out, ITALIC_CHARS);

        if (currFlags & BOLD)
            _write_format_chars(out, BOLD_CHARS);

        out.write("\n", 1);
    }
}

/*
    Outputs the DynamicArray<Line> lines attribute
    into a file with a .md extension.
 */
void Editor::dump_to_md()
{
    const char *tempFilePath = _append_extension(".md");

    std::ofstream out(tempFilePath, std::ios::binary);

    if (out.is_open())
    {
        const unsigned int lineCount = lines.get_size();

        for (unsigned int line = 0; line < lineCount; ++line)
        {
            _dump_line(out, lines[line]);
        }

        out.close();
    }
    delete[] tempFilePath;
}