#include <iostream>
#include <dirent.h>
#include <string.h>
#include <vector>

#include "filedata.h"

#define ALLOC_FAILURE "Failed to allocate enough memory.\n";

void GetFiles(const char *, std::vector<file_data> &);

int main()
{
    try
    {
        std::vector<file_data> vec;
        GetFiles("/home/shady/Desktop", vec);

        for (std::vector<file_data>::iterator it = vec.begin(); it != vec.end(); ++it)
        {
            std::cout << it->get_path() << " " << it->get_size() << std::endl;
        }
    }
    catch (std::bad_alloc())
    {
        throw ALLOC_FAILURE;
    }
    catch (const char *msg)
    {
        std::cout << msg;
    }
    return 0;
}

void GetFiles(const char *path, std::vector<file_data> &vec)
{

    DIR *dp;
    struct dirent *ep;

    dp = opendir(path);

    if (dp != NULL)
    {
        while ((ep = readdir(dp)))
        {
            if (strcmp(ep->d_name, ".") && strcmp(ep->d_name, ".."))
            {
                //puts(ep->d_name);

                size_t len = strlen(path) + strlen(ep->d_name) + 2;

                char *full_path = new char[len];
                // std::cout << strlen(ep->d_name) << '\n';

                strcpy(full_path, path);
                full_path += strlen(path);
                *full_path = '/';

                strcpy(full_path + 1, ep->d_name);
                full_path -= strlen(path);

                puts(full_path);
                if (ep->d_type == DT_DIR)
                    GetFiles(full_path, vec);
                else
                {
                    file_data temp(full_path);
                    vec.push_back(temp);
                }
                delete[] full_path;
            }
        }
    }
    else
        perror("Couldn't open the directory");

    closedir(dp);
}