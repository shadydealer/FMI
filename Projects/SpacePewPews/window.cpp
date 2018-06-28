#include <stdio.h>
#include <unistd.h> //usleep()

#include "window.h"

#pragma region Big Four

Window::Window() : width(DEFAULT_WIDTH + 3),   //+3 for the two borders and the null terminator
                   height(DEFAULT_HEIGHT + 2), //+2 for the two border rows.
                   map(width, height),
                   bullets(),
                   enemies(),
                   player(0,
                          0,
                          RIGHT,
                          DEFAULT_PLAYER_AVATAR_PATH)
{
    set_entity_starting_position(&player, height);
    generate_map();
}

Window::~Window()
{
}
#pragma endregion

Window::Window(const int rhsWidth,
               const int rhsHeight) : width(rhsWidth + 3),
                                      height(rhsHeight + 2),
                                      map(width, height),
                                      bullets(),
                                      enemies(),
                                      player(0,
                                             0,
                                             RIGHT,
                                             DEFAULT_PLAYER_AVATAR_PATH)
{
    if (height - 2 >= player.get_avatar().get_data().get_height() &&
        width - 3 >= player.get_avatar().get_data().get_width())
    {
        set_entity_starting_position(&player, height);
        generate_map();
    }
    else
    {
        throw InvalidMapSize(player.get_avatar().get_data().get_height(),
                             player.get_avatar().get_data().get_width());
    }
}

void Window::set_entity_starting_position(Entity *rhs, const int rhsHeight)
{
    rhs->move(rhs->get_avatar().get_data().get_width() / 2 + (rhs->get_avatar().get_data().get_width() % 2 != 0),
              rhsHeight / 2);
}

/*
    Generates the map for each frame.
 */
void Window::generate_map()
{
    LinkedList<Bullet>::iterator bulletIt = bullets.beg();
    LinkedList<Character>::iterator enemyIt = enemies.beg();

    Pair<int, int> indexes(0, 0);
    int row = 0, col = 0;

    for (indexes.first = 0; indexes.first < width - 1; ++indexes.first)
        map[0][indexes.first] = HORIZONTAL_BORDER_TILE;

    for (indexes.second = 1; indexes.second < height - 1; ++indexes.second)
    {
        for (indexes.first = 1; indexes.first < width - 2; ++indexes.first)
        {
            if (bulletIt != bullets.end())
            {
                if ((*bulletIt).within_hitbox(indexes))
                {
                    row = indexes.second - (((*bulletIt).get_coords().second - ((*bulletIt).get_avatar().get_data().get_height() / 2)));
                    col = indexes.first - (((*bulletIt).get_coords().first - ((*bulletIt).get_avatar().get_data().get_width() / 2)));
                    map[indexes.second][indexes.first] = (*bulletIt).get_avatar().get_data()[row][col];

                    ++bulletIt;
                }
            }
            else if (enemyIt != enemies.end())
            {
                if ((*enemyIt).within_hitbox(indexes))
                {
                    row = indexes.second - (((*enemyIt).get_coords().second - ((*enemyIt).get_avatar().get_data().get_height() / 2)));
                    col = indexes.first - (((*enemyIt).get_coords().first - ((*enemyIt).get_avatar().get_data().get_width() / 2)));
                    map[indexes.second][indexes.first] = (*enemyIt).get_avatar().get_data()[row][col];

                    ++enemyIt;
                }
            }
            else if (player.within_hitbox(indexes))
            {
                row = indexes.second - (player.get_coords().second - player.get_avatar().get_data().get_height() / 2);
                col = indexes.first - (player.get_coords().first - player.get_avatar().get_data().get_width() / 2);
                map[indexes.second][indexes.first] = player.get_avatar().get_data()[row][col];
            }
            else
                map[indexes.second][indexes.first] = EMPTY_TILE;
        }
        map[indexes.second][0] = map[indexes.second][width - 2] = VERTICAL_BORDER_TILE;
    }

    for (indexes.first = 0; indexes.first < width - 1; ++indexes.first)
        map[height - 1][indexes.first] = HORIZONTAL_BORDER_TILE;
}

void Window::clear() const
{
    /*
        Found in:
            https://stackoverflow.com/questions/4062045/clearing-terminal-in-linux-with-c-code

        Additional sources:
            https://en.wikipedia.org/wiki/ANSI_escape_code

        Explanation:
            \033 ASCII escape character octal representation.
            2J clears entire screen.
            1;1H moves the cursor to row 1 and col 1 of the terminal.
     */
    printf("\033[2J\033[1;1H");

    usleep(80000); // so that the console window doesn't flicker.
}

void Window::draw()
{
    clear();
    generate_map();

    if (player.get_coords().first < width - (player.get_avatar().get_data().get_width() + 1))
        player.move(1, 0);

    int row = 0, col = 0;
    Pair<int, int> indexes(0, 0);

    for (indexes.second; indexes.second < height; ++indexes.second)
    {
        for (indexes.first = 0; indexes.first < width; ++indexes.first)
        {
            printf("%c", map[indexes.second][indexes.first]);
        }
        printf("\n");
    }
}
