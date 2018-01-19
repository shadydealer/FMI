#include <iostream>
#include <stdlib.h>
#include <string.h>

const unsigned int words_count = 4;
const char *words[] = {"apple", "orange", "month", "vehicle"};
unsigned int picked_word = 0;
char *fillable_word = NULL;

unsigned int max_mistakes = 0;
unsigned int mistakes_made = 0;

unsigned int *picked_indexes = NULL;
unsigned int picked_count = 0;

const char *used_letters = NULL;
unsigned int letters_count = 0;

void push_index(const unsigned int);
bool prev_picked(const unsigned int);

const unsigned int pick_word();
void generate_fillable_word(const unsigned int);

const char pick_letter();
void push_letter(const char letter);
bool check_for_letter(const char);
void log();

bool guessed_word();

int main()
{
    try
    {

        std::cout << "Input how many mistakes are allowed: ";
        std::cin >> max_mistakes;

        std::cout << "Guess the word (max "
                  << max_mistakes
                  << " mistakes):\n\n";

        while (true)
        {
            picked_word = pick_word();
            generate_fillable_word(picked_word);

            while (mistakes_made != max_mistakes)
            {
                log();

                char letter = pick_letter();
                if (check_for_letter(letter))
                    std::cout << "OK\n\n";

                else
                {
                    std::cout << "No such letter!\n\n";
                    ++mistakes_made;
                }

                if (guessed_word())
                {
                    log();
                    break;
                }
            }

            delete[] used_letters;
            used_letters = NULL;
            letters_count = 0;

            if (picked_count == words_count)
                break;

            if (mistakes_made != max_mistakes)
            {
                std::cout << "Congratulations! Now on to the next one !\n\n";
                mistakes_made = 0;
            }
            else
                throw "Game over!\n";
        }
        throw "G to the G!\n";
    }
    catch (std::bad_alloc())
    {
        std::cout << "Failed to allocate enough memory.\n";
    }
    catch (const char *msg)
    {
        std::cout << msg;
        delete[] fillable_word;
        fillable_word = NULL;
        delete[] picked_indexes;
        picked_indexes = NULL;
    }
    return 0;
}

void generate_fillable_word(const unsigned int index)
{
    char *buffer = new char[strlen(words[index]) + 1]();
    memset(buffer, '_', strlen(words[index]));
    delete[] fillable_word;
    fillable_word = buffer;
}
const unsigned int pick_word()
{
    unsigned int index = rand() % words_count;

    while (prev_picked(index))
        index = rand() % words_count;

    push_index(index);
    std::cout << index << std::endl;

    return index;
}

bool prev_picked(const unsigned int index)
{
    for (unsigned int i = 0; i < picked_count; ++i)
    {
        if (index == picked_indexes[i])
            return true;
    }
    return false;
}

void push_index(const unsigned int index)
{
    unsigned int *buffer = new unsigned int[picked_count + 1];

    if (picked_indexes)
        memcpy(buffer, picked_indexes, picked_count * (sizeof(unsigned int)));

    buffer[picked_count++] = index;
    delete[] picked_indexes;

    picked_indexes = buffer;
}

const char pick_letter()
{
    char c = 0;
    std::cout << "Choose a letter: ";
    std::cin >> c;
    push_letter(c);

    return c;
}

bool check_for_letter(const char c)
{
    bool has_letter = 0;
    int index = 0;
    while (words[picked_word][index] != 0)
    {
        if (words[picked_word][index] == c)
        {
            has_letter = 1;
            fillable_word[index] = c;
        }
        ++index;
    }
    return has_letter;
}

void push_letter(const char letter)
{
    char *buffer = new char[letters_count + 2]();
    memcpy(buffer, used_letters, letters_count);
    buffer[letters_count++] = letter;
    delete[] used_letters;

    used_letters = buffer;
}
void log()
{
    std::cout << "["
              << mistakes_made
              << "/"
              << max_mistakes
              << "] "
              << fillable_word
              << " History: ";

    if (used_letters)
    {
        const char *runner = used_letters;
        while (*runner != 0)
            std::cout << *runner++ << " ";
    }

    std::cout << std::endl;
}

bool guessed_word()
{
    char *runner = fillable_word;
    while (*runner != 0)
    {
        if (*runner++ == '_')
            return false;
    }
    return true;
}