#include "command_handler.h"

CommandHandler CommandHandler::instance;

/*
    Ctor with map height and map width.

    @params rhsMW - Map width.
    @params rhsMH - map height.
 */
void CommandHandler::init(const int rhsMW,
                          const int rhsMH,
                          DynamicArray<Bullet> &rhsBullets,
                          DynamicArray<Character> &rhsEnemies,
                          Character &rhsPlayers)
{
    mapWidth = rhsMW;
    mapHeight = rhsMH;
    bullets = &rhsBullets;
    enemies = &rhsEnemies;
    player = &rhsPlayers;
    set_character_starting_pos(*player, rhsMH / 2);
}

void CommandHandler::set_character_starting_pos(Character &rhs, const int height)
{
    Pair<int, int> coords(1 + rhs.get_coords().first,
                          height + rhs.get_coords().second);
    rhs.set_coords(coords);
}

/*
    Checks if the the move that we're making is allowed.

    @params rhs - entity we're moving.
    @params rhsX - x coordinate units.
    @params rhsY - y coordinate units.
 */
bool CommandHandler::is_within_bounds(const Entity *rhs,
                                      const int rhsX,
                                      const int rhsY) const
{
    int newX = rhs->get_coords().first + rhs->get_direction() * rhsX;
    int newY = rhs->get_coords().second + rhsY;

    return ((newX > (rhs->get_avatar().get_data().get_width() / 2) &&
             newX <= mapWidth - (rhs->get_avatar().get_data().get_width() / 2)) &&
            (newY > (rhs->get_avatar().get_data().get_height() / 2) &&
             newY <= mapHeight - (rhs->get_avatar().get_data().get_height() / 2)));
}

/*
    Moves all the enemies a single x unit in their respective direction.
 */
void CommandHandler::move_enemies()
{
    for (unsigned int e = 0; e < enemies->get_size(); ++e)
    {
        if (is_within_bounds(&(*enemies)[e], 1, 0))
            (*enemies)[e].move(1, 0);
        else
            enemies->remove(e--);
    }
}

/* 
    Moves all the bullets a single x unit in their respective direciton.
 */
void CommandHandler::move_bullets()
{
    for (unsigned int b = 0; b < bullets->get_size(); ++b)
    {
        if (is_within_bounds(&(*bullets)[b], 1, 0))
            (*bullets)[b].move(1, 0);
        else
            bullets->remove(b--);
    }
}

/*
    Checks if the two entities hitboxes collide.
 */
bool CommandHandler::hitboxes_collide(const Entity *e1, const Entity *e2) const
{
    int e1Width = e1->get_avatar().get_data().get_width();
    int e1Height = e1->get_avatar().get_data().get_height();

    Pair<int, int> coords(e1->get_coords().first - e1Width / 2,
                          e1->get_coords().second - e1Height / 2);
    for (unsigned int i = 0; i < e1Height; ++i)
    {
        coords.first = e1->get_coords().first - e1Width / 2;
        for (unsigned int j = 0; j < e1Width; ++j)
        {
            if (e2->within_hitbox(coords))
            {
                e2->within_hitbox(coords);
                return true;
            }
            ++coords.first;
        }
        ++coords.second;
    }
    return false;
}

/*
    Collides the entity with every other entity
    dealing damage to anything it has hit.
 */
bool CommandHandler::collide(const Entity *rhs)
{
    if (player != rhs)
    {
        if (hitboxes_collide(rhs, player))
        {
            player->take_damage();
            return true;
        }
    }

    unsigned int size = enemies->get_size();

    for (unsigned int e = 0; e < size; ++e)
    {
        if (rhs != &(*enemies)[e])
        {
            if (hitboxes_collide(rhs, &(*enemies)[e]))
            {
                hitboxes_collide(rhs, &(*enemies)[e]);
                (*enemies)[e].take_damage();
                if (!(*enemies)[e].is_alive())
                    enemies->remove(e);

                return true;
            }
        }
    }
    return false;
}

/*
    Causes the passed in character to shoot,
    appending a bullet to the bullet list.

    @params rhs - Character that will shoot.
 */
void CommandHandler::character_shoot(const Character &rhs)
{
    Pair<int, int> pos(rhs.shoot());
    bullets->push_back(Bullet(pos.first,
                              pos.second,
                              rhs.get_direction()));
}

/*
    Moves the player character by specified units.

    @params rhsX - x coordinate moves.
    @params rhsY - y coordinate moves.
 */
void CommandHandler::move_player(const int rhsX,
                                 const int rhsY)
{
    if (is_within_bounds(player, rhsX, rhsY))
        player->move(rhsX, rhsY);
}

void CommandHandler::clean_up_objects()
{
    for (unsigned int b = 0; b < bullets->get_size(); ++b)
    {
        if (collide(&(*bullets)[b]))
            bullets->remove(b--);
    }
    if (collide(&(*player)))
        player->take_damage();
}

/* 
    Spawns an enemy appending it to the enemies list.
 */
void CommandHandler::spawn_enemies(const int count)
{

    Character enemy(DEFAULT_ENEMY_AVATAR_PATH,
                    mapWidth - 1,
                    0,
                    1,
                    LEFT);

    Pair<int, int> coords(enemy.get_coords().first, mapHeight / 2);

    for (unsigned int i = 0; i < count; ++i)
    {
        enemy.set_coords(coords);
        int lower = enemy.get_avatar().get_data().get_height() / 2;
        int upper = mapHeight - (enemy.get_avatar().get_data().get_height() / 2);

        coords.second = (rand() % upper + lower);

        bool collidingHitboxes = true;

        while (collidingHitboxes)
        {
            collidingHitboxes = false;
            for (unsigned int e = 0; e < enemies->get_size(); ++e)
            {
                if (hitboxes_collide(&(*enemies)[e], &enemy))
                {
                    collidingHitboxes = true;
                    coords.second = (rand() % upper + lower);
                    enemy.set_coords(coords);
                    break;
                }
            }
        }
        enemies->push_back(enemy);
    }
}

CommandHandler *CommandHandler::get_instance()
{
    return &instance;
}

Character *CommandHandler::get_player()
{
    return player;
}

DynamicArray<Character> *CommandHandler::get_enemies()
{
    return enemies;
}

DynamicArray<Bullet> *CommandHandler::get_bullets()
{
    return bullets;
}