#include "Moderator.h"

//Default ctor.
Moderator::Moderator(): User()
{
}

//String parameter ctor.
Moderator::Moderator(const String & rhsNickName,
                     const unsigned int rhsAge): User(rhsNickName,
                                                      rhsAge)
{
}

/*
    Blocks the passed in user
    by setting his isBlocked attribute to true.

    @params rhs- User object to be blocked.
 */
void Moderator::block(User & rhs)
{
    if(!(rhs.is_blocked()))
    {
        rhs.block_unblock();
        printf("Blocked %s.\n", rhs.get_nickname().get_cstr());
    }
    else
        printf("%s is already blocked.\n", rhs.get_nickname().get_cstr());
}

/*
    Unblocks the passed in user
    by setting his isBlocked attribute to false.

    @params rhs- User object to be unblocked. 
 */
void Moderator::unblock(User & rhs)
{
    if(rhs.is_blocked())
    {
        printf("Unblocked %s.\n", rhs.get_nickname().get_cstr());
        rhs.block_unblock();
    }
    else
        printf("%s is already unblocked.\n", rhs.get_nickname().get_cstr());
}