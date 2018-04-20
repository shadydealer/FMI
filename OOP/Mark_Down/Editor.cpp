#include "Editor.h"
#include <iostream>

Editor::Editor() : filePath(), lines()
{
}

Editor::Editor(const char *rhsFilePath) : filePath(rhsFilePath), lines()
{
    _extract_data_for_editing();
}

void Editor::init_file(const char *rhsFilePath)
{
    filePath.set_string(rhsFilePath);
    _extract_data_for_editing();
}

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
void Editor::_extract_data_for_editing()
{
    const char *tempPath = _append_extension(".txt");

    std::ifstream in(tempPath);

    if (in.is_open())
    {
        char currLine[MAX_LINE_LENGTH + 1];

        while (in.getline(currLine, MAX_LINE_LENGTH + 1))
        {
            std::cout << currLine << std::endl;
            lines.push_back(currLine);
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

void Editor::make_heading(const unsigned int lineIndex)
{
    lines[lineIndex].make_heading();
}

void Editor::make_italic(const unsigned int lineIndex,
                         const unsigned short fromWord,
                         const unsigned short toWord)
{
    for (unsigned short w = fromWord; w <= toWord; ++w)
        lines[lineIndex][w].set_flag(ITALIC);
}

void Editor::make_bold(const unsigned int lineIndex,
                       const unsigned short fromWord,
                       const unsigned short toWord)
{
    for (unsigned short w = fromWord; w <= toWord; ++w)
        lines[lineIndex][w].set_flag(BOLD);
}

void Editor::make_combine(const unsigned int lineIndex,
                          const unsigned short fromWord,
                          const unsigned short toWord)
{
    for (unsigned short w = fromWord; w <= toWord; ++w)
        lines[lineIndex][w].set_flag((ITALIC | BOLD));
}

void Editor::add_line(const char *rhsLine)
{
    lines.push_back(rhsLine);
}

void Editor::remove_line(const unsigned int lineIndex)
{
    lines.remove(lineIndex);
}

void Editor::_write_format_chars(std::ofstream &out, const char *chars)
{
    out.write(chars, strlen(chars));
}

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