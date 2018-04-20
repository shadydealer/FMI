#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>

bool operator<(std::string left, std::string right);
void quick_sort(std::vector<std::string> &vec, int left, int right);
int main()
{
    unsigned short nameCount = 0;
    std::vector<std::string> names;
    std::cin >> nameCount;
    std::cin.get();

    std::string name;
    for (unsigned int i = 0; i < nameCount; ++i)
    {
        std::cin >> name;
        names.push_back(name);
    }

    quick_sort(names, 0, names.size() - 1);

    std::vector<std::string>::iterator curr_name = names.begin();
    curr_name = names.begin();
    for (; curr_name != names.end(); ++curr_name)
    {
        printf("%s", curr_name->c_str());
    }
    printf("\n");

    return 0;
}

bool operator<(std::string left, std::string right)
{
    std::string dummy = left;
    left.append(right);
    right.append(dummy);

    unsigned int len = left.length();
    for (unsigned int i = 0; i < len; ++i)
    {
        if (left[i] < right[i])
            return true;
        else if (left[i] > right[i])
            return false;
    }
    return false;
}

void quick_sort(std::vector<std::string> &vec, int left, int right)
{
    std::string median = vec[(left + right) / 2];
    int i = left;
    int j = right;

    std::string temp;

    while (i <= j)
    {
        while (vec[i] < median)
            ++i;
        while (median < vec[j])
            --j;

        if (i <= j)
        {
            temp = vec[i];
            vec[i] = vec[j];
            vec[j] = temp;
            ++i;
            --j;
        }
    }

    if (left < j)
        quick_sort(vec, left, j);
    if (i < right)
        quick_sort(vec, i, right);
}