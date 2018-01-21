#include <iostream>
#include <string.h>
#include <stdlib.h>

#define DEFAULT_BUFFER_SIZE 256

char *decompress_string(char *);

int main(int argc, char *const argv[])
{
    try
    {
        char *data = NULL;
        data = decompress_string(argv[1]);
        std::cout << data << std::endl;

        delete[] data;
    }
    catch (const char *msg)
    {
        std::cout << msg;
    }
    catch (std::bad_alloc())
    {
        std::cout << "Failed to allocate enough memory.\n";
    }
    return 0;
}

char *decompress_string(char *input)
{
    static char *data = new char[2]();

    if (*input)
    {
        size_t len = strlen(data) + 2;
        char *buffer = new char[len]();

        strcpy(buffer, data);

        delete[] data;
        data = buffer;

        if (!(*input >= 'A' && *input <= 'Z'))
        {
            if ((*input >= '1' && *input <= '9'))
            {
                size_t size = 0;
                char temp[DEFAULT_BUFFER_SIZE] = {};
                while (*input != '(')
                {
                    temp[size++] = *input++;
                }

                ++input;

                size_t num = atoi(temp);
                for (size_t n = 0; n < num; ++n)
                {
                    decompress_string(input);
                }
                while (*input != ')')
                    ++input;
                while (*input == ')')
                    ++input;

                decompress_string(input);
            }

            else if (*input != ')')
            {
                throw "String does not meet the requirements.\n";
            }
        }

        else
        {
            data[len - 2] = *input;
            decompress_string(++input);
        }
    }
    return data;
}