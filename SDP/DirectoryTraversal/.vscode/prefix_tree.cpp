#include "prefix_tree.h"

//
// default prefix_tree ctor.
//
prefix_tree::prefix_tree(): root(nullptr) {}

//
// prefix_tree dtor.
//
prefix_tree::~prefix_tree()
{
    clean(root);
}

//
// prefix_tree clean method.
//
void prefix_tree::clean(node * curr)
{
    if (curr->first)    clean(curr->first);
    if (curr->second)   clean(curr->second);
    if (curr->third)    clean (curr->third);
    if (curr->fourth)   clean (curr->fourth);

    delete curr;
}

//
// prefix_tree insert method.
//
void prefix_tree::insert(const String & rhs_key)
{
    node * curr = root;
    while(curr)
}

//
// default node ctor.
//
prefix_tree::node::node() : keys{},
                            first(nullptr),
                            second(nullptr),
                            third(nullptr),
                            fourth(nullptr) {}

//
// node String paramter ctor.
// NOTE: rhs_l_key stands for rhs first key.
//
prefix_tree::node::node(const String &rhs_l_key) : keys{rhs_l_key},
                                                   first(nullptr),
                                                   second(nullptr),
                                                   third(nullptr),
                                                   fourth(nullptr) {}
//
// node opretor=.
// NOTE: simply coppies the addresses to the children nodes (does not make coppies of the children nodes).
//
prefix_tree::node &prefix_tree::node::operator=(const node &rhs)
{
    for (size_t k = 0; k < MAX_KEYS; ++k)
        keys[k] = rhs.keys[k];

    first = rhs.first;
    second = rhs.second;
    third = rhs.third;
    fourth = rhs.fourth;
}