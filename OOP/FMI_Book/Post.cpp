#include "Post.h"

static unsigned long long currID = 1;

//Default ctor.
Post::Post() : data(),
               id(currID++),
               creator(nullptr)
{
}

//Copy ctor.
Post::Post(const String &rhsData,
           const User * rhsCreator) : 
           data(rhsData),
           id(currID++),
           creator(rhsCreator)
{
}

//id getter method.
unsigned int Post::get_id() const
{
    return id;
}

//creator getter method.
const User * Post::get_creator() const
{
    return creator;
}
