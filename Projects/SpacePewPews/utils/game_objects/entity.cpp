#include "entity.h"

#pragma region Big Four
Entity::Entity() : avatar(),
                   coords(0, 0),
                   direction(RIGHT)
{
}

Entity::Entity(const Entity &rhs) : avatar(rhs.avatar),
                                    coords(rhs.coords),
                                    direction(RIGHT)
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
Entity::Entity(const char *filePath,
               const int rhsX,
               const int rhsY,
               const Direction rhsDirection) : avatar(filePath),
                                               coords((avatar.get_data().get_width() / 2) + rhsX,
                                                      (avatar.get_data().get_height() / 2) + rhsY),
                                               direction(rhsDirection)
{
}

/*
    Entity avatar,int and direction parameter ctor.

    @params rhsAvatar - path to a file containing a charMap for the avatar.
    @params rhsX - x coordinate.
    @params rhsY - y coordinate.
    @params rhsDirection - the direction the entity is facing.
 */
Entity::Entity(const Avatar &rhsAvatar,
               const int rhsX,
               const int rhsY,
               const Direction rhsDirection) : avatar(rhsAvatar),
                                               coords((avatar.get_data().get_width() / 2) + rhsX,
                                                      (avatar.get_data().get_height() / 2) + rhsY),
                                               direction(rhsDirection)
{
}

/*
    Checks if the passed in coordinates overlap
    with the entities hitbox.

    @params rhsCoords - coords to check if are overlaping.

    @return value: 
        True if they are.
        False otherwise.
 */
bool Entity::within_hitbox(const Pair<int, int> &rhsCoords) const
{
    int widthPadding = avatar.get_data().get_width() / 2;
    int heightPadding = avatar.get_data().get_height() / 2;

    return (rhsCoords.first >= (coords.first - widthPadding) &&
            rhsCoords.first <= (coords.first + widthPadding) &&
            rhsCoords.second >= (coords.second - heightPadding) &&
            rhsCoords.second <= (coords.second + heightPadding));
}

/*
    Increments the instances x and y
    coordinates by multiplying the x coordinate
    by the direction in order to move the object
    in the window without constantly thinking whether
    you should add a minus or not infront of the
    number of steps you would like the
    object to take. 
 */
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

void Entity::set_coords(const Pair<int, int> &rhs)
{
    coords.first = rhs.first;
    coords.second = rhs.second;
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