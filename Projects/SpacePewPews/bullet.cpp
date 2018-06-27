#include "bullet.h"

#pragma region Big Four
Bullet::Bullet() : Entity()
{
}

Bullet::Bullet(const Bullet &rhs) : Entity(rhs)
{
}

Bullet &Bullet::operator=(const Bullet &rhs)
{
    Entity::operator=(rhs);
}

Bullet::~Bullet()
{
}
#pragma endregion

Bullet::Bullet(const int rhsX,
               const int rhsY,
               const Direction rhsDirection,
               const char *filePath) : Entity(rhsX,
                                              rhsY,
                                              rhsDirection,
                                              filePath)
{
}
