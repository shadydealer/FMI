#include "character.h"

#pragma region Big Four
Character::Character() : Entity()
{
}

Character::Character(const Character &rhs) : Entity(rhs)
{
}

Character &Character::operator=(const Character &rhs)
{
    if (this != &rhs)
        Entity::operator=(rhs);

    return *this;
}

Character::~Character()
{
}
#pragma endregion

Character::Character(const int rhsX,
                     const int rhsY,
                     const Direction rhsDir,
                     const char *filePath) : Entity(rhsX,
                                                    rhsY,
                                                    rhsDir,
                                                    filePath)
{
}


/*
    Returns the x and y coordinates
    from which the shot originated
    as a pair object, so it can later
    be assigned to a bullet object.
 */
Pair<int, int> Character::shoot() const
{
    Pair<int, int> result;
    result.first = (avatar.get_data().get_width() / 2) + coords.first;
    result.second = (avatar.get_data().get_height() / 2) + coords.second;

    return result;
}