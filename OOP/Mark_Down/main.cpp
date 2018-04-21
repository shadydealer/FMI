#include <iostream>
#include <fstream>
#include "Editor.h"

#define MAX_PATH_LENGTH 260

#define MAX_COMMAND_STR_LENGTH 11

#define MAKE_HEADING "makeHeading"
#define MAKE_ITALIC "makeItalic"
#define MAKE_BOLD "makeBold"
#define MAKE_COMBINE "makeCombine"
#define ADD_LINE "addLine"
#define REMOVE "remove"
#define EXIT "exit"

int main()
{
    try
    {
        char fileName[MAX_PATH_LENGTH + 1] = {0};

        std::cout << "Please input a path to a file WITHOUT the extension at the end:\n";

        std::cin.getline(fileName, MAX_PATH_LENGTH + 1);

        Editor editor(fileName);

        char inputCommand[MAX_COMMAND_STR_LENGTH + 1] = {0};

        unsigned int lineIndex = 0;
        unsigned int firstWordIndex = 0;
        unsigned int lastWordIndex = 0;

        char newLine[MAX_LINE_LENGTH + 1] = {0};

        std::cout << "Please input a command.\n";
        std::cin >> inputCommand;

        while (strcmp(inputCommand, EXIT) != 0)
        {
            if (strcmp(inputCommand, ADD_LINE) == 0)
            {
                std::cin.get();

                std::cin.getline(newLine, MAX_LINE_LENGTH);
                editor.add_line(newLine);
            }
            else
            {
                std::cin >> lineIndex;

                if (strcmp(inputCommand, MAKE_HEADING) == 0)
                    editor.make_heading(lineIndex - 1);

                else if (strcmp(inputCommand, REMOVE) == 0)
                    editor.remove_line(lineIndex - 1);

                else
                {
                    std::cin >> firstWordIndex >> lastWordIndex;

                    if (strcmp(inputCommand, MAKE_ITALIC) == 0)
                    {
                        editor.make_italic(lineIndex - 1,
                                           firstWordIndex - 1,
                                           lastWordIndex - 1);
                    }

                    else if (strcmp(inputCommand, MAKE_BOLD) == 0)
                    {
                        editor.make_bold(lineIndex - 1,
                                         firstWordIndex - 1,
                                         lastWordIndex - 1);
                    }

                    else if (strcmp(inputCommand, MAKE_COMBINE) == 0)
                    {
                        editor.make_combine(lineIndex - 1,
                                            firstWordIndex - 1,
                                            lastWordIndex - 1);
                    }
                    else
                    {
                        std::cout << "Invalid command.\n";
                    }
                }
            }
            
            std::cout << "Please input a command.\n";
            std::cin >> inputCommand;
        }

        editor.dump_to_md();
    }
    catch (const char *msg)
    {
        std::cout << msg << std::endl;
    }
    catch (std::out_of_range oor)
    {
        std::cout << oor.what();
    }
    catch (std::bad_alloc ba)
    {
        std::cout << ba.what();
    }

    return 0;
}
