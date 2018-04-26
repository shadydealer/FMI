#include <iostream>
#include <string.h>
#include <vector>
#include <algorithm>

#define DEFAULT_INPUT_SIZE 20000
void counting_sort(std::vector<unsigned int> &);
void print(const std::vector<unsigned int> &);

unsigned int maxLength = 0;

int main()
{
    char input[DEFAULT_INPUT_SIZE + 1] = {0};

    std::cin.getline(input, DEFAULT_INPUT_SIZE + 1);
    std::vector<unsigned int> wordLengths;

    unsigned int inputLen = strlen(input) + 1;
    unsigned int currWordLen = 0;

    char *str_p = input;

    while (*str_p != '\0')
    {
        if (*(str_p++) == ' ')
        {
            wordLengths.push_back(currWordLen);
            currWordLen = 0;
        }
        else
            ++currWordLen;
    }

    wordLengths.push_back(currWordLen);
    
    maxLength = *std::max_element(wordLengths.begin(),
                                  wordLengths.end());


    unsigned int rows = 0;

    std::cout << rows << ' ' << maxLength << '\n';

    return 0;
}

void counting_sort(std::vector<unsigned int> &rhs)
{
    unsigned int buckets[DEFAULT_INPUT_SIZE] = {0};

    std::vector<unsigned int>::iterator w = rhs.begin();

    for (; w != rhs.end(); ++w)
    {
        ++buckets[*w];
    }

    unsigned int index = 0;

    for (unsigned int i = 0; i < maxLength; ++i)
    {
        while (buckets[i])
        {
            rhs[index++] = i;
            --buckets[i];
        }
    }
}

void print(const std::vector<unsigned int> &rhs)
{
    std::vector<unsigned int>::const_iterator w = rhs.begin();

    for (; w != rhs.end(); ++w)
    {
        std::cout << *w << " ";
    }
    std::cout << std::endl;
}