#include <stdio.h>
#include "window.h"
#include "bullet.h"
#include "character.h"

int main()
{
    try
    {

        Window win;
        while(true)
        {
            win.draw();
        }

        /*
        Character player(0, 0, RIGHT, "assets/character_avatars/player_avatar.txt");
        printf("height: %d, width: %d\n", player.get_avatar().get_data().get_height(),
               player.get_avatar().get_data().get_width());
        Pair<int, int> result(player.shoot());
        printf("x: %d, y: %d\n", result.first, result.second);
         */
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
    catch (InvalidFileFormat &iff)
    {
        iff.what();
    }
    catch (InvalidMapSize &ims)
    {
        ims.what();
    }
    return 0;
}
