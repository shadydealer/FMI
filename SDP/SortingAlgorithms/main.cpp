#include <iostream>
#include "examData.h"
#include "dynamic_array.h"
#include <fstream>
#include "string"

#define DEF_SIZE 1024 //default size for array.
enum command
{
    NAME,
    AGE,
    SUBJECT,
    GRADE,
    DATE,
    ASC,
    DESC
};

command hash_token(const String &);
void quick_sort_asc(dynamic_array<examData> &, int, int);
void quick_sort_desc(dynamic_array<examData> &, int, int);
void getline(std::istream &, String &, char = '\n');
std::ostream &operator<<(std::ostream &, const String &);
std::ifstream &operator>>(std::ifstream &, dynamic_array<examData> &);

int main()
{
    try
    {

        String input;
        getline(std::cin, input);
        String tokens[3] = {};

        tokens[0] = input.substr(0, ' ');                                          //path to the file.
        tokens[1] = input.substr(tokens[0].get_length(), ' ');                     //column by which the data has to be sorted.
        tokens[2] = input.substr(tokens[0].get_length() + tokens[1].get_length()); //order in which the data has to be sorted.

        std::ifstream in((*tokens).get_data());
        command column = hash_token(tokens[1]);
        command order = hash_token(tokens[2]);

        if (in.good())
        {
            dynamic_array<examData> dad;
            in.seekg(32);
            in >> dad;

            quick_sort_asc(dad, 0, dad.get_size() - 1);

            for (int e = 0; e < dad.get_size(); ++e)
            {
                std::cout << dad[e].get_name() << std::endl;
            }

            std::cout << "----------\n";

            quick_sort_desc(dad, 0, dad.get_size() - 1);

            for (int e = 0; e < dad.get_size(); ++e)
            {
                std::cout << dad[e].get_name() << std::endl;
            }
        }
    }
    catch (const char *msg)
    {
        std::cout << msg << std::endl;
    }
    catch (std::bad_alloc())
    {
        std::cout << "failed to allocate enough memory.\n"
                  << std::endl;
    }
    return 0;
}
command hash_token(const String &rhs)
{
    if (rhs == "name")
        return NAME;
    else if (rhs == "age")
        return AGE;
    else if (rhs == "subject")
        return SUBJECT;
    else if (rhs == "grade")
        return GRADE;
    else if (rhs == "date")
        return DATE;
    else if (rhs == "asc")
        return ASC;
    else if (rhs == "desc")
        return DESC;
    throw "Invalid column or order.";
}

//
// Quick Sort Ascending
//
// Unstable sorting algorithm.
// Avarage complexity of O(nlogn), where n is the size of the dynamic_array.
// In-place.
// What it does:
//  It takes a dynamic_array and 2 integers as input.
// The first of the two integers is the index of the "beginning" of the array
// and the second is the index of the "end" of the array.
// At first the two int are set to the beginning and the end of the array,
// but as the sorting algorithm works, the integers "gravitate" towards the center of the array.
void quick_sort_asc(dynamic_array<examData> &rhs, int left, int right)
{
    int i = left;
    int j = right;
    unsigned long long pivot = rhs[(left + right) / 2].get_date().get_data();
    while (i <= j)
    {
        while (rhs[i].get_date().get_data() < pivot)
            ++i;
        while (rhs[j].get_date().get_data() > pivot)
            --j;

        if (i <= j)
        {
            examData temp = rhs[i];
            rhs[i] = rhs[j];
            rhs[j] = temp;
            ++i;
            --j;
        }
    }

    if (left < j)
        quick_sort_asc(rhs, left, j);
    if (i < right)
        quick_sort_asc(rhs, i, right);
}

//
// Quick Sort Descending
//
void quick_sort_desc(dynamic_array<examData> &rhs, int left, int right)
{
    int i = left;
    int j = right;
    unsigned long long pivot = rhs[(left + right) / 2].get_date().get_data();
    while (i <= j)
    {
        while (rhs[i].get_date().get_data() > pivot)
            ++i;
        while (rhs[j].get_date().get_data() < pivot)
            --j;

        if (i <= j)
        {
            examData temp = rhs[i];
            rhs[i] = rhs[j];
            rhs[j] = temp;
            ++i;
            --j;
        }
    }

    if (left < j)
        quick_sort_desc(rhs, left, j);
    if (i < right)
        quick_sort_desc(rhs, i, right);
}

void getline(std::istream &is, String &str, char delim)
{

    int len = DEF_SIZE;
    char *buffer = new char[len];

    int jump = 0;

    char *temp;

    while (!is.getline(buffer, len, delim))
    {
        buffer -= jump;

        temp = new char[len * 2];
        strcpy(temp, buffer);

        delete[] buffer;
        buffer = temp;

        jump += len - 1;

        buffer += jump;
        len *= 2;
        is.clear();
    }

    buffer -= jump;

    str = buffer;

    delete[] buffer;
}

std::ifstream &operator>>(std::ifstream &is, dynamic_array<examData> &rhs)
{
    String name;
    int age;
    String subject;
    int grade;
    int data[3] = {};

    while (is.good())
    {
        getline(is, name, ',');
        std::cout << name << std::endl;

        is >> age;
        //std::cout << age << std::endl;

        is.get();

        getline(is, subject, ',');
        //std::cout << subject << std::endl;

        is >> grade;
        //std::cout << grade << std::endl;

        for (int i = 0; i < 3; ++i)
        {
            is.get();
            is >> data[i];
            //    std::cout << data[i] << std::endl;
        }

        is.get();
        date d(data[0], data[1], data[2]);
        rhs.push(examData(d, age, grade, name, subject));

        std::cout << "------\n";

        if (is.peek() == '\n')
            break;
    }

    return is;
}

std::ostream &operator<<(std::ostream &os, const String &str)
{
    std::cout << str.get_data() << std::endl;
    return os;
}
