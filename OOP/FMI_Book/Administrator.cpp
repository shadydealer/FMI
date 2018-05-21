#include "Administrator.h"

//Default ctor.
Administrator::Administrator() : Moderator()
{
}

//String parameter ctor.
Administrator::Administrator(const String &rhsNickName) : Moderator(rhsNickName)
{
}

/*
    Creates a moderator by given nickname.

    @params rhsNickname- nickname of the moderator.

    @return value- Moderator with rhsNickname as his nickname.
 */
Moderator * Administrator::add_moderator(const String& rhsNickname) const
{
    Moderator * temp = new Moderator(rhsNickname);
    printf("Added moderator %s.\n", rhsNickname.get_cstr());
    return temp;
}

/*
    Creates a user by given nickname.

    @params rhsNickName- nickname of the user.

    @return value- User with rhsNickname as his nickname.
 */
User* Administrator::add_user(const String & rhsNickname) const
{
    User * temp = new User(rhsNickname);
    printf("Added user %s.\n", rhsNickname.get_cstr());
    return temp;
}
