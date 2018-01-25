#include "prefix_tree.h"

prefix_tree::prefix_tree() : root()
{
}

prefix_tree::prefix_tree(const std::string &rhs_dir) : root(rhs_dir)
{
}

prefix_tree::iterator prefix_tree::push_folder(const prefix_tree::iterator &it, const std::string &folder_name)
{
    node *temp = new node(folder_name);
    it.data->folders.push_back(temp);

    return (*(*(--(it.data)->folders.end())));
}

void prefix_tree::push_file(const prefix_tree::iterator &it, const std::string &file_name)
{
    it.data->files.push_back(file_name);
}

void prefix_tree::print()
{
    prefix_tree::iterator root_it(root);
    std::string dir;
    _print(dir, &root);
}

void prefix_tree::_print(std::string full_path, node *root) const
{
    if (root)
    {
        full_path.append((*root).directory.c_str());
        file_map::iterator file_it = root->files.begin();

        if (file_it)
        {

            for (; file_it != root->files.end(); ++file_it)
            {
                std::cout << full_path
                          << (*file_it).get_name()
                          << " "
                          << std::endl;
            }
        }
        std::list<node *>::iterator folder_it = root->folders.begin();
        for (; folder_it != root->folders.end(); ++folder_it)
        {
            _print(full_path, (*folder_it));
        }
    }
}

prefix_tree::iterator prefix_tree::get_root()
{
    prefix_tree::iterator r(root);
    return r;
}

prefix_tree::node::node() : directory(), files(), folders()
{
}

prefix_tree::node::node(const std::string &rhs_dir) : directory(rhs_dir), files(), folders()
{
}

prefix_tree::node::~node()
{
    std::list<node *>::iterator temp =
        folders.begin();
    std::list<node *>::iterator dummy = temp;
    while (temp != folders.end())
    {
        ++dummy;
        delete *temp;
        temp = dummy;
    }
    //std::cout << "size:" << size << std::endl;
}

prefix_tree::iterator::iterator() : data(NULL)
{
}

prefix_tree::iterator::iterator(node &rhs) : data(&rhs)
{
}

prefix_tree::iterator &prefix_tree::iterator::operator=(const iterator &rhs)
{
    if (this != &rhs)
    {
        data = rhs.data;
    }

    return *this;
}

prefix_tree::iterator::operator bool()
{
    return data;
}

prefix_tree::node *prefix_tree::iterator::operator->()
{
    return data;
}