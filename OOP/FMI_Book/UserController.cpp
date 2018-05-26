#include "UserController.h"

//default ctor.
UserController::UserController() : users()
{
}

/*
    Finds a user in the user list by given nickname and
    returns an iterator pointing to the user.

    @params rhsNickName - which User nickname we're looking for.

    @return value:
        Iterator pointing to the user if we've found him.
        Iterator to null if we've failed to find him. 
 */
PolymorphicList<User>::Iterator UserController::_fetch_user(const String &rhsNickName)
{
    PolymorphicList<User>::Iterator it = users.beg();

    for (; it != users.end(); ++it)
        if ((it)->get_nickname() == rhsNickName)
            break;

    return it;
}

/*
    Adds a user to the list of users.
    The user must have a unique nickname in order
    to be added.

    @params rhs- the user we'll possibly be adding.
    
    @return value:
        True if the users nickname is unique.
        False otherwise.
 */
bool UserController::add_user(User * rhs)
{
    PolymorphicList<User>::Iterator userExists = _fetch_user(rhs->get_nickname());

    if (!userExists)
    {
        users.push_back(rhs);

        printf("%s\n", rhs->get_nickname().get_cstr());

        printf("Added user %s.\n", rhs->get_nickname().get_cstr());
        return true;
    }

    printf("Nickname %s is already in use.\n", rhs->get_nickname().get_cstr());
    return false;
}

/* 
    Removes a user from the list of users
    by given nickname.

    @params rhsNickName- nickname of the user we'd like to remove.
 */
void UserController::remove_user(const String &rhsNickName)
{
    PolymorphicList<User>::Iterator it = _fetch_user(rhsNickName);

    if (it)
    {
        users.remove(it);
        printf("Successfully removed %s from the system.\n", rhsNickName.get_cstr());
    }
    else
    {
        printf("User %s doesn't exists.\n", rhsNickName.get_cstr());
    }
}

/*
    Fetches a user by nickname.

    @params rhsNickName - nickname to locate the user by.

    @return value:
        Pointer to a user object if we've found the user.
        Pointer to null otherwise.
 */
User *UserController::fetch_user(const String &rhsNickName)
{
    PolymorphicList<User>::Iterator it = _fetch_user(rhsNickName);
    if (it)
        return (&(*it));

    return nullptr;
}