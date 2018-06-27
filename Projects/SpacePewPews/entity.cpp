#include "entity.h"

#pragma region Big Four
Entity::Entity() : coords(0, 0),
                   direction(RIGHT),
                   avatar()
{
}

Entity::Entity(const Entity &rhs) : coords(rhs.coords),
                                    direction(RIGHT),
                                    avatar(rhs.avatar)
{
}

Entity &Entity::operator=(const Entity &rhs)
{
    if (this != &rhs)
    {
        coords = rhs.coords;
        direction = rhs.direction;
        avatar = rhs.avatar;
    }
    return *this;
}

Entity::~Entity()
{
}

#pragma endregion

/*
    Entity int and cstring param ctor.

    @params rhsY - y coordinate.
    @params rhsX - x coordinate.
    @params filePath - path to a file containing a charMap for the avatar.
 */
Entity::Entity(const int rhsX,
               const int rhsY,
               const Direction rhsDirection,
               const char *filePath) : coords(rhsX, rhsY),
                                       direction(RIGHT),
                                       avatar(filePath)
{
    if (rhsDirection == LEFT || rhsDirection == RIGHT)
        direction = rhsDirection;
    else
        throw InvalidDirection();
}

void Entity::move(const int rhsX,
                  const int rhsY)
{
    coords.first += rhsX * static_cast<int>(direction);
    coords.second += rhsY;
}

/*
    Sets the current entities avatar
    to the specified file containing the charMap.

    @params filePath- path containing the charMap.
 */
void Entity::set_avatar(const char *filePath)
{
    avatar.open_file(filePath);
}

const Pair<int, int> &Entity::get_coords() const
{
    return coords;
}

const Direction &Entity::get_direction() const
{
    return direction;
}

const Avatar &Entity::get_avatar() const
{
    return avatar;
}