#include <stdio.h>
#include <unistd.h> //usleep()

#include "window.h"

Window Window::instance;

Window *Window::get_instance()
{
    return &instance;
}

void Window::init(const int rhsWidth,
                  const int rhsHeight,
                  DynamicArray<Bullet> &rhsBullets,
                  DynamicArray<Character> &rhsEnemies,
                  Character &rhsPlayer)
{
    if (rhsHeight >= rhsPlayer.get_avatar().get_data().get_height() &&
        rhsWidth >= rhsPlayer.get_avatar().get_data().get_width())
    {
        width = rhsWidth + 3;
        height = rhsHeight + 2;
        map = array2D<char>(width, height);
        bullets = &rhsBullets;
        enemies = &rhsEnemies;
        player = &rhsPlayer;
        generate_map();
    }
    else
    {
        throw InvalidMapSize(player->get_avatar().get_data().get_height(),
                             player->get_avatar().get_data().get_width());
    }
}

/*
    Generates the map for each frame.
 */
void Window::generate_map()
{
    unsigned int bulletsSize = bullets->get_size();
    unsigned int enemiesSize = enemies->get_size();

    Pair<int, int> indexes(0, 0);
    int row = 0, col = 0;
    bool alreadyFilled = false;

    for (indexes.first = 0; indexes.first < width - 1; ++indexes.first)
        map[0][indexes.first] = HORIZONTAL_BORDER_TILE;

    for (indexes.second = 1; indexes.second < height - 1; ++indexes.second)
    {
        for (indexes.first = 1; indexes.first < width - 2; ++indexes.first)
        {
            alreadyFilled = false;

            if (player->within_hitbox(indexes))
            {
                row = indexes.second - (player->get_coords().second - player->get_avatar().get_data().get_height() / 2);
                col = indexes.first - (player->get_coords().first - player->get_avatar().get_data().get_width() / 2);
                map[indexes.second][indexes.first] = player->get_avatar().get_data()[row][col];
                continue;
            }

            for (unsigned int e = 0; e < enemiesSize; ++e)
            {
                if ((*enemies)[e].within_hitbox(indexes))
                {
                    row = indexes.second - (((*enemies)[e].get_coords().second - ((*enemies)[e].get_avatar().get_data().get_height() / 2)));
                    col = indexes.first - (((*enemies)[e].get_coords().first - ((*enemies)[e].get_avatar().get_data().get_width() / 2)));
                    map[indexes.second][indexes.first] = (*enemies)[e].get_avatar().get_data()[row][col];
                    alreadyFilled = true;
                    break;
                }
            }

            if (!alreadyFilled)
            {
                for (unsigned int b = 0; b < bulletsSize; ++b)
                {
                    if ((*bullets)[b].within_hitbox(indexes))
                    {
                        row = indexes.second - (((*bullets)[b].get_coords().second - ((*bullets)[b].get_avatar().get_data().get_height() / 2)));
                        col = indexes.first - (((*bullets)[b].get_coords().first - ((*bullets)[b].get_avatar().get_data().get_width() / 2)));
                        map[indexes.second][indexes.first] = (*bullets)[b].get_avatar().get_data()[row][col];
                        alreadyFilled = true;
                        break;
                    }
                }
                if (!alreadyFilled)
                    map[indexes.second][indexes.first] = EMPTY_TILE;
            }
        }
        map[indexes.second][0] = map[indexes.second][width - 2] = VERTICAL_BORDER_TILE;
    }

    for (indexes.first = 0; indexes.first < width - 1; ++indexes.first)
        map[height - 1][indexes.first] = HORIZONTAL_BORDER_TILE;
}

/*
    Prints the level menu.
 */
void Window::print_level_menu() const
{
    printf("Pick a dificulty by entering one of the following numbers:\n");
    printf("1)Easy\n"
           "2)Medium\n"
           "3)Hard\n");
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

    usleep(DEFAULT_CLEAR_SPEED); // so that the console window doesn't flicker.
}

void Window::print_stats() const
{
    printf("LIVES: %d\n", player->get_lives());
}

void Window::draw()
{
    generate_map();

    Pair<int, int> indexes(0, 0);
    for (indexes.second; indexes.second < height; ++indexes.second)
    {
        for (indexes.first = 0; indexes.first < width; ++indexes.first)
        {
            printf("%c", map[indexes.second][indexes.first]);
        }
        printf("\n");
    }
    print_stats();
}
