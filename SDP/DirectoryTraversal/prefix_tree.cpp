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
    node *d = *it.data->folders.beg();
    int n = 0;
    linked_list<node *>::iterator nit = it.data->folders.beg(); //node iterator.
    for (linked_list<node *>::iterator f = nit; f != it.data->folders.end(); ++f)
    {
        //std::cout << ++n << std::endl;
        if (strcmp(temp->directory.c_str(), (*f)->directory.c_str()) < 0)
        {
            /*             puts(temp->directory.c_str());
            puts((*f)->directory.c_str());
            puts((*nit)->directory.c_str());
            puts("========");
            */
            nit = f;
            break;
        }
    }
    it.data->folders.insert_after(nit, temp);

    return prefix_tree::iterator(*(*(nit)));
}

void prefix_tree::push_file(const prefix_tree::iterator &it, const std::string &file_name, const char marker)
{
    file_data temp(file_name, marker);

    linked_list<file_data>::iterator nit = it.data->files.beg(); //node iterator.
    for (linked_list<file_data>::iterator f = nit; f != it.data->files.end(); ++f)
    {
        if (strcmp(temp.get_name().c_str(), f->get_name().c_str()) < 0)
        {
            nit = f;
            break;
        }
    }
    it.data->files.insert_after(--nit, temp);
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
        linked_list<file_data>::iterator file_it = root->files.beg();
        for (linked_list<file_data>::iterator i = file_it; i != root->files.end(); ++i)
        {
            std::cout << full_path
                      << i->get_name()
                      << " "
                      << i->get_marker()
                      << std::endl;
        }

        linked_list<node *>::iterator it = root->folders.beg();
        for (linked_list<node *>::iterator i = it; i != root->folders.end(); ++i)
        {
            _print(full_path, (*i));
        }
    }
}

bool prefix_tree::check_files(const std::string &rhs_name, prefix_tree::iterator &iter)
{
    node *it = iter.data;
    linked_list<file_data>::iterator file_it = it->files.beg();

    for (linked_list<file_data>::iterator f = file_it; f != it->files.end(); ++f)
    {
        if (strcmp(rhs_name.c_str(), f->get_name().c_str()) == 0)
            return true;
    }
    std::cout << "add me!" << std::endl;
    return false;
}

prefix_tree::iterator prefix_tree::get_root()
{
    prefix_tree::iterator r;
    r.data = &root;
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
    linked_list<node *>::iterator temp =
        folders.beg();
    linked_list<node *>::iterator dummy = temp;
    while (temp != folders.end())
    {
        ++dummy;
        delete *temp;
        temp = dummy;
    }
    //std::cout << "size:" << size << std::endl;
}

prefix_tree::iterator::iterator() : data(NULL), it()
{
}

prefix_tree::iterator::iterator(node &rhs) : data(&rhs), it()
{
}

prefix_tree::iterator &prefix_tree::iterator::operator=(const iterator &rhs)
{
    if (this != &rhs)
        data = rhs.data;

    return *this;
}
/* 
prefix_tree::iterator prefix_tree::iterator::operator++(const int)
{
    prefix_tree::iterator iter = *this;
    iter = 
    return iter;
} */

prefix_tree::iterator::operator bool()
{
    return data;
}

std::string &prefix_tree::iterator::operator*()
{
    return data->directory;
}

const std::string &prefix_tree::iterator::operator*() const
{
    return data->directory;
}
