#include "Administrator.h"

//Default ctor.
Administrator::Administrator() : Moderator()
{
}

//String parameter ctor.
Administrator::Administrator(const String &rhsNickName,
                             const unsigned int rhsAge) : Moderator(rhsNickName,
                                                                    rhsAge)
{
}

/*
    Creates a moderator by given nickname.

    @params rhsNickname- nickname of the moderator.

    @return value- Moderator with rhsNickname as his nickname.
 */
Moderator Administrator::add_moderator(const String& rhsNickname,
                                       const unsigned int rhsAge) const
{
    Moderator temp(rhsNickname, rhsAge);
    return temp;
}

/*
    Creates a user by given nickname.

    @params rhsNickName- nickname of the user.

    @return value- User with rhsNickname as his nickname.
 */
User Administrator::add_user(const String & rhsNickname,
                             const unsigned int rhsAge) const
{
    User temp (rhsNickname, rhsAge);
    return temp;
}
