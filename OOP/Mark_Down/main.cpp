#include <iostream>
#include <fstream>
#include "Editor.h"

#define MAX_PATH_LENGTH 260
int main()
{
    char fileName[MAX_PATH_LENGTH + 1];
    std::cin.getline(fileName, MAX_PATH_LENGTH + 1);
    try
    {

    Editor editor(fileName);
    editor.make_heading(0);
    editor.make_bold(0,0,4);
    editor.make_italic(1,0,7);
    editor.make_combine(2,1,2);

    editor.dump_to_md();

    }
    catch(const char * msg)
    {
        std::cout << msg << std::endl;
    }
    catch(std::out_of_range oor)
    {
        std::cout << oor.what();
    }

    return 0;
}
