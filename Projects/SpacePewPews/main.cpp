#include <stdio.h>
#include "window.h"
#include "utils/avatar.h"

int main()
{
    try
    {

        Window win;
        for (unsigned int i = 0; i < 10; ++i)
        {
            win.draw();
        }

        Avatar avatar("assets/player_avatar.txt");
        avatar.get_data().print();
    }
    catch (std::out_of_range &oor)
    {
        puts(oor.what());
    }
    catch (std::bad_alloc &ba)
    {
        puts("Failed to allocate enough space.");
    }
    catch (FileNotOpen &fno)
    {
        fno.what();
    }
    catch(InvalidFileFormat & iff)
    {
        iff.what();
    }

    return 0;
}
