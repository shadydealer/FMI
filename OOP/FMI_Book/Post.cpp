#include "Post.h"

static unsigned long long currID = 0;

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
