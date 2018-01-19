#include <iostream>
#include <string.h>
#include <stdlib.h>

#define DEFAULT_BUFFER_SIZE 256

void getline(std::istream &in, char *&buffer);
void decompress_string(char *, char *&);

int main(int argc, char *const argv[])
{
    try
    {
        char *data = NULL;
        decompress_string(argv[1], data);
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

void decompress_string(char *input, char *&data)
{

    if (*input)
    {

        size_t len = data ? strlen(data) + 2 : 2;
        char *buffer = new char[len]();

        if (data)
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
                    decompress_string(input, data);
                }
                while (*input != ')')
                    ++input;
                while (*input == ')')
                    ++input;

                decompress_string(input, data);
            }

            else if (*input != ')')
            {
                throw "String does not meet the requirements.\n";
            }
        }

        else
        {
            data[len - 2] = *input;
            decompress_string(++input, data);
        }
    }
}