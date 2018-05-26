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
    */
void UserController::add_user(const String &nickName,
                              const unsigned int age,
                              const UserType type)
{
    PolymorphicList<User>::Iterator userExists = _fetch_user(nickName);

    if (!userExists)
    {
        User *temp;

        if (type == USER)
            temp = new User(nickName, age);
        else if (type == MODERATOR)
            temp = new Moderator(nickName, age);

        users.push_back(temp);

        printf("%s\n", nickName.get_cstr());

        printf("Added user %s.\n", nickName.get_cstr());
        return;
    }

    printf("Nickname %s is already in use.\n", nickName.get_cstr());
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

/*
    Blocks a user with nickname receiverNickName 
    if the user with nickname value of actorNickName
    has rights to do so.

    @params actorNickName - nickname of the user that's doing the blocking.
    @params receiverNickname - nickname of the user the actor is blocking.
 */
void UserController::block_user(const String &actorNickName, const String &receiverNickName)
{

    User *actor = fetch_user(actorNickName);
    User *receiver = fetch_user(receiverNickName);
    if (actor && receiver)
    {
        Moderator *mod = dynamic_cast<Moderator *>(actor);
        if (mod)
        {
            if (!receiver->is_blocked())
            {
                receiver->block_unblock();
                printf("%s blocked %s.\n", actorNickName.get_cstr(), receiverNickName.get_cstr());
                return;
            }
            printf("%s is already blocked.\n", receiverNickName.get_cstr());
        }
        printf("%s doesn't have permission to block.\n", actorNickName.get_cstr());
    }
}

/*
    Unblocks a user with nickname receiverNickName 
    if the user with nickname value of actorNickName
    has rights to do so.

    @params actorNickName - nickname of the user that's doing the blocking.
    @params receiverNickname - nickname of the user the actor is blocking.
 */
void UserController::unblock_user(const String &actorNickName, const String &receiverNickName)
{

    User *actor = fetch_user(actorNickName);
    User *receiver = fetch_user(receiverNickName);
    if (actor && receiver)
    {
        Moderator *mod = dynamic_cast<Moderator *>(actor);
        if (mod)
        {
            if (receiver->is_blocked())
            {
                receiver->block_unblock();
                printf("%s unblocked %s.\n", actorNickName.get_cstr(), receiverNickName.get_cstr());
                return;
            }
            printf("%s is already unblocked.\n", receiverNickName.get_cstr());
        }
        printf("%s doesn't have permission to unblock.\n", actorNickName.get_cstr());
    }
}