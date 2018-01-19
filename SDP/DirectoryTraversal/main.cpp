#include <iostream>
#include <dirent.h>
#include <string.h>

#include "filedata.h"
#include "prefix_tree.h"

#define ALLOC_FAILURE "Failed to allocate enough memory.\n"

void GetFiles(const std::string &, prefix_tree &, prefix_tree::iterator);
void traverse_tree(const std::string &, prefix_tree &, prefix_tree::iterator);
int main()
{
    try
    {
        std::string path;
        std::cin >> path;

        prefix_tree tree(path);
        prefix_tree::iterator root = tree.get_root();

        GetFiles(path, tree, root);

        std::string input;
        std::cin >> input;

        while (strcmp(input.c_str(), "quit") != 0)
        {

            if (strcmp(input.c_str(), "print") == 0)
                tree.print();

            if (strcmp(input.c_str(), "refresh") == 0)
            {
                root = tree.get_root();
                traverse_tree(path,tree,root);
            }
            std::cin >> input;
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

void GetFiles(const std::string &rhs_path, prefix_tree &tree, prefix_tree::iterator root)
{

    DIR *dp;
    struct dirent *ep;

    prefix_tree::iterator root_c = root;
    dp = opendir(rhs_path.c_str());

    if (dp != NULL)
    {
        while ((ep = readdir(dp)))
        {
            if (strcmp(ep->d_name, ".") && strcmp(ep->d_name, ".."))
            {
                //puts(ep->d_name);
                std::string name(ep->d_name);
                std::string path(rhs_path);
                path.append("/");
                path.append(name);

                //puts(path.get_data());

                if (ep->d_type == DT_DIR)
                {
                    name.append("/");
                    root_c = tree.push_folder(root, name);
                    //std::cout << (*root).get_data() << std::endl;

                    //std::cout << (*root).get_data() << std::endl;
                    GetFiles(path, tree, root_c);
                }

                else
                {
                    tree.push_file(root, path,' ');
                }
            }
        }
    }
    else
        perror("Couldn't open the directory");

    closedir(dp);
}

void traverse_tree(const std::string &rhs_path, prefix_tree &tree, prefix_tree::iterator root)
{

    DIR *dp;
    struct dirent *ep;

    prefix_tree::iterator root_c = root;
    dp = opendir(rhs_path.c_str());

    if (dp != NULL)
    {
        while ((ep = readdir(dp)))
        {
            if (strcmp(ep->d_name, ".") && strcmp(ep->d_name, ".."))
            {

                std::string name(ep->d_name);
                std::string path(rhs_path);
                path.append("/");
                path.append(name);

                //puts(path.get_data());

                if (ep->d_type == DT_DIR)
                {
                    traverse_tree(path, tree, root_c);
                }

                else
                {
                    if (!tree.check_files(name, root))
                        tree.push_file(root, path, ADDED);
                }
            }
        }
    }
    else
        perror("Couldn't open the directory");

    closedir(dp);
}