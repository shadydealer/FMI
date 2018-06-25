#include <stdio.h>
#include <unistd.h> //usleep()

#include "window.h"

#define DEFAULT_HEIGHT 35
#define DEFAULT_WIDTH 145

#define EMPTY_TILE ' '
#define HORIZONTAL_BORDER_TILE '|'
#define VERTICAL_BORDER_TILE '-'

Window::Window() : width(DEFAULT_WIDTH + 3),   //+3 for the two borders and the null terminator
                   height(DEFAULT_HEIGHT + 2), //+2 for the two border rows.
                   map(width, height)
{
    generate_map();
}

Window::Window(const int rhsWidth,
               const int rhsHeight) : width(rhsWidth + 1),
                                      height(rhsHeight + 1),
                                      map(width, height)
{
    generate_map();
}

Window::~Window()
{
}

/*
    Generates the base map.
 */
void Window::generate_map()
{
    for (int c = 0; c < width - 1; ++c)
        map[0][c] = VERTICAL_BORDER_TILE;

    for (int r = 1; r < height - 1; ++r)
    {
        for (int c = 1; c < width - 2; ++c)
            map[r][c] = EMPTY_TILE;

        map[r][0] = map[r][width - 2] = HORIZONTAL_BORDER_TILE;
    }

    for (int c = 0; c < width - 1; ++c)
        map[height - 1][c] = VERTICAL_BORDER_TILE;
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

    usleep(100000); // so that the console window doesn't flicker.
}

void Window::draw() const
{
    clear();
    map.print();
}