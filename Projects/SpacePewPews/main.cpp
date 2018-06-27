#include <stdio.h>
#include "window.h"
#include "bullet.h"

int main()
{
    try
    {

        Window win;
        for (unsigned int i = 0; i < 10; ++i)
        {
            win.draw();
        }
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
    catch(InvalidDirection& id)
    {
        id.what();
    }

    return 0;
}
