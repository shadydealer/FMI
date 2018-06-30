#include "character.h"

#pragma region Big Four
Character::Character() : Entity(),
                         lives(DEFAULT_CHARACTER_LIVES)
{
}

Character::Character(const Character &rhs) : Entity(rhs),
                                             lives(rhs.lives)
{
}

Character &Character::operator=(const Character &rhs)
{
    if (this != &rhs)
    {
        Entity::operator=(rhs);
        lives = rhs.lives;
    }

    return *this;
}

Character::~Character()
{
}
#pragma endregion

Character::Character(const char *filePath,
                     const int rhsX,
                     const int rhsY,
                     const int rhsLives,
                     const Direction rhsDir) : lives(rhsLives),
                                               Entity(filePath,
                                                      rhsX,
                                                      rhsY,
                                                      rhsDir)
{
}

Character::Character(const Avatar &rhsAvatar,
                     const int rhsX,
                     const int rhsY,
                     const int rhsLives,
                     const Direction rhsDir) : lives(rhsLives),
                                               Entity(rhsAvatar,
                                                      rhsX,
                                                      rhsY,
                                                      rhsDir)
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
    result.first = (direction * (avatar.get_data().get_width() / 2)) + coords.first + direction;
    result.second = (avatar.get_data().get_height() / 2) + coords.second -1;

    return result;
}

void Character::take_damage()
{
    --lives;
}

const int Character::get_lives() const
{
    return lives;
}

const bool Character::is_alive() const
{
    return lives > 0;
}