#include "engine.h"

Engine::Engine() : enemies(),
                   bullets(),
                   player(DEFAULT_PLAYER_AVATAR_PATH,
                          0, 0, 3, RIGHT),
                   winWidth(DEFAULT_WIDTH),
                   winHeight(DEFAULT_HEIGHT),
                   handler(CommandHandler::get_instance()),
                   window(Window::get_instance())
{
    handler->init(winWidth, winHeight,
                  bullets, enemies, player);
    window->init(winWidth, winHeight, bullets,
                 enemies, player);
}

void Engine::set_keyboard_blocking(termios *settings)
{
    tcsetattr(0, TCSANOW, settings);
}
void Engine::set_keyboard_non_blocking(termios *settings)
{
    struct termios newSettings;
    tcgetattr(0, settings);

    newSettings = *settings;
    newSettings.c_lflag &= ~(ICANON | ECHO | ISIG);
    newSettings.c_iflag &= ~(ISTRIP | INLCR | ICRNL |
                             IGNCR | IXON | IXOFF);
    newSettings.c_cc[VMIN] = 0;

    tcsetattr(0, TCSANOW, &newSettings);
}

void Engine::run()
{
    struct termios termSettings;
    set_keyboard_non_blocking(&termSettings);
    try
    {
        int counter = 0;
        char c = 0;
        int rng = 0;
        while (c != 'q' && player.is_alive())
        {
            c = getchar();
            switch (c)
            {
            case 'w':
                handler->move_player(0, -1);
                break;
            case 's':
                handler->move_player(0, 1);
                break;
            case 'a':
                handler->move_player(-1, 0);
                break;
            case 'd':
                handler->move_player(1, 0);
                break;
            case ' ':
                handler->character_shoot(player);
                break;
            default:
                break;
            }

            window->clear();
            window->draw();
            handler->move_bullets();

            if (counter % 3 == 0)
            {
                handler->move_enemies();
            }
            if (counter % 15 == 0)
            {
                if (enemies.get_size() > 0)
                {
                    rng = rand() % (enemies.get_size());
                    handler->character_shoot(enemies[rng]);
                }
            }
            if (counter % 75 == 0)
            {
                rng = rand() % 5 + 1;
                handler->spawn_enemies(rng);
                counter = 0;
            }

            handler->clean_up_objects();
            ++counter;
        }
        window->clear();
        window->draw();
        printf("GAME OVER\n");
    }
    catch (std::out_of_range &oor)
    {
        puts(oor.what());
    }
    catch (std::bad_alloc &ba)
    {
        puts("Failed to allocate enough space.");
    }
    catch (FileNotOpen &fno)
    {
        fno.what();
    }
    catch (InvalidFileFormat &iff)
    {
        iff.what();
    }
    catch (InvalidMapSize &ims)
    {
        ims.what();
    };
    set_keyboard_blocking(&termSettings);
}