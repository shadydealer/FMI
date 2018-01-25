#include "functions.h"

int main(int argc, char *const argv[])
{
    try
    {
        if (strcmp((argv[1]), "init") == 0)
        {
            if (init_repository(argv[2]))
                puts("Successfully initialized the repository.");
            else
                puts("Repository initialization failed.");
        }
        else if (strcmp(argv[1], "commit") == 0)
        {
            make_commit(argv[2], argv[3], argv[4]);
        }
        
        return 0;
    }
    catch (const char *msg)
    {
        puts(msg);
    }
}