#include "User.h"

//Default ctor.
User::User() : nickname(),
               age(0),
               isBlocked(false)
{
}

//String parameter ctor.
User::User(const String &rhsNickname,
           const unsigned int rhsAge) : nickname(rhsNickname),
                                        age(rhsAge),
                                        isBlocked(false)
{    
}

//dtor.
User::~User()
{
}

//Operator==.
bool User::operator==(const User &rhs)
{
    return nickname == rhs.nickname;
}

/*
    Changes the nickname of the current User object
    to the passed in String nickname.

    @params rhsNickname- String object containing the new nickname.
 */

void User::change_nickname(const String & rhsNickname)
{
    nickname = rhsNickname;
}

/*
    Sets the isBlocked attribute to true/false
    depending on its previous state.
*/
void User::block_unblock()
{
    isBlocked =!isBlocked;
}   

//Getter method for the nickname attribute.
const String& User::get_nickname() const
{
    return nickname;
}

//Getter method for the age attribute.
const unsigned int User::get_age() const
{
    return age;
}

//Getter method for the isBlocked attribute.
const bool User::is_blocked() const
{
    return isBlocked;
}
