#include <iostream>
#include "FMIBook.h"
#include "typeinfo"

#define DEFAULT_ADMIN_NAME "Admin"
#define DEFAULT_ADMIN_AGE 0

#define DEAFULT_INPUT_BUFFER_SIZE 1024

void RunTests();
const char *get_input();
int main()
{
    FMIBook fmibook(DEFAULT_ADMIN_NAME, DEFAULT_ADMIN_AGE);

    const char *input = get_input();
    while (strcmp(input, "quit") != 0)
    {
        const char *runner = input;

        unsigned int length = 0;

        while (*(runner++) != ' ')
            ++length;

        char *actorNickName = new char[length + 1]{0};
        strncpy(actorNickName, input, length);

        String actor(actorNickName);
        delete[] actorNickName;

        length = 0;
        while (*(runner++) != ' ')
            ++length;

        char *command = new char[length + 1]{0};
        strncpy(command, runner - (length + 1), length);
        
        char * temp = nullptr;

        if (strcmp(command, "add_user") == 0)
        {
            if (fmibook.get_admin().get_nickname() != actor)
                printf("Only an admin can add users.\n");

            else
            {
                length = 0;
                while (*(runner++) != ' ')
                    ++length;

                temp = new char[length + 1]{0};
                strncpy(temp, runner - (length + 1), length);

                String newUserNickName(temp);

                unsigned int age = atoi(runner);

                fmibook.add_user(newUserNickName, age);

            }
        }
        else if (strcmp(command, "add_moderator") == 0)
        {
            if (fmibook.get_admin().get_nickname() != actor)
                printf("Only an admin can add moderators.\n");

            else
            {
                length = 0;
                while (*(runner++) != ' ')
                    ++length;

                temp = new char[length + 1]{0};
                strncpy(temp, runner - (length + 1), length);

                String newModeratorNickName(temp);
                
                unsigned int age = atoi(runner);

                fmibook.add_moderator(newModeratorNickName, age);

            }
        }
        else if (strcmp(command, "remove_user") == 0)
        {
            if (fmibook.get_admin().get_nickname() != actor)
                printf("Only an admin can remove users.\n");

            else
            {
                length = 0;
                while (*(runner++) != ' ')
                    ++length;

                temp = new char[length + 1]{0};
                strncpy(temp, runner - (length + 1), length);

                String userNickName(temp);

                fmibook.remove_user(userNickName);
            }
        }
        else if (strcmp(command, "post") == 0)
        {
            length = 0;
            while (*(runner++) != ' ')
                ++length;

            temp = new char[length + 1]{0};
            strncpy(temp, runner - (length + 1), length);

            String postType(temp);
            delete[] temp;

            length = 0;
            while (*(runner++) != 0)
                ++length;

            temp = new char[length + 1]{0};
            strncpy(temp, runner - (length + 1), length);

            String postData(temp);

            fmibook.make_post(actor,
                              postData,
                              postType);
        }
        else if (strcmp(command, "remove_post") == 0)
        {
            unsigned int id = atoi(runner);
            fmibook.remove_post(actor, id);
        }
        else if (strcmp(command, "view_post") == 0)
        {
            unsigned int id = atoi(runner);
            fmibook.look_at_single_post(id);
        }
        else if (strcmp(command, "view_all_posts") == 0)
        {
            length = 0;
            while (*(runner++) != 0)
                ++length;

            temp = new char[length + 1]{0};
            strncpy(temp, runner - (length + 1), length);
            
            String providerNickName(temp);

            fmibook.look_at_all_posts(providerNickName);
        }
        else if(strcmp(command, "rename") == 0)
        {
            length = 0;
            while (*(runner++) != 0)
                ++length;

            temp = new char[length + 1]{0};
            strncpy(temp, runner - (length + 1), length);
            
            String newNickName(temp);

            if(actor == fmibook.get_admin().get_nickname())
                fmibook.get_admin().change_nickname(newNickName);
        }
        else if(strcmp(command, "block") == 0)
        {
            length = 0;
            while (*(runner++) != 0)
                ++length;

            temp = new char[length + 1]{0};
            strncpy(temp, runner - (length + 1), length);
            
            String user(temp);

            fmibook.block_user(actor,temp);
        }
        else if(strcmp(command, "unblock") == 0)
        {
            length = 0;
            while (*(runner++) != 0)
                ++length;

            temp = new char[length + 1]{0};
            strncpy(temp, runner - (length + 1), length);
            
            String user(temp);

            fmibook.unblock_user(actor,temp);
        }
        else
            printf("Invalid command.\n");

        delete[] temp;
        delete[] command;
        delete[] input;
        input = get_input();
    }

    delete[] input;
    return 0;
}

void RunTests()
{
    String adminNickName("admin");
    FMIBook fmibook(adminNickName, 0);
    String firtUserNickName("Pepi");
    fmibook.add_user(firtUserNickName, 10);
    String postData("/home/shadydealer/Desktop/city_by_dabana-d5nwexv.jpg");
    fmibook.make_post(firtUserNickName, postData, "image");
    fmibook.look_at_single_post(1);
    fmibook.look_at_all_posts(firtUserNickName);
}
const char *get_input()
{
    const int length = DEAFULT_INPUT_BUFFER_SIZE;
    size_t count = 0; //stores the amount of characters read from the stream.

    char *buffer = new char[length]{0};
    char *temp;

    try
    {
        //
        // Loops until all the flags are set to false.
        //
        while (!std::cin.getline(buffer, length).good())
        {
            // move the buffer pointer to the beginning of the string.
            buffer -= count;

            // get the amount of characters extracted from the stream.
            count += std::cin.gcount();

            // allocate more space for a bigger string.
            temp = new char[length + count];

            // copy the alraedy read characters
            // from the buffer into the newly allocated space.
            strcpy(temp, buffer);

            delete[] buffer;
            buffer = temp;

            // Increment the pointer to the first place
            //in the newly allocated space where we can write
            //without writing over the previously extracted characters.
            buffer += count;

            //reset the stream state flags.
            std::cin.clear();
        }

        // move the buffer pointer to the beginning of the string.
        buffer -= count;
        // check if the input string is a valid command
        //and delete it if it isn't.

        return buffer;
    }
    catch (std::bad_alloc())
    {
        delete[] buffer;
        throw std::bad_alloc();
    }
}