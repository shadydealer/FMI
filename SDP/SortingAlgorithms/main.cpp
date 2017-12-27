#include <iomanip>
#include <iostream>
#include <fstream>

#include "examData.h"
#include "dynamic_array.h"
#include "algos.h"

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

void getline(std::istream &, String &, char = '\n');
command hash_token(const String &);
void execute_command(const String &, const command &, const command &);

void quick_sort(dynamic_array<examData> &, int, int);

std::ifstream &operator>>(std::ifstream &, dynamic_array<examData> &);
std::ostream &operator<<(std::ostream &, const String &);
std::ostream &operator<<(std::ostream &, const dynamic_array<examData> &);
int main(int argc, char * argv[])
{
    try
    {
        String tokens[3] = {};

        tokens[0] = argv[1]; //path to the file.
        tokens[1] = argv[2]; //column by which the data has to be sorted.
        tokens[2] = argv[3]; //order in which the data has to be sorted.

        command column = hash_token(tokens[1]);
        command order = hash_token(tokens[2]);

        execute_command(*tokens, column, order);
    }
    catch (const char *msg)
    {
        std::cout << msg;
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
    throw "Invalid column or order.\n";
}

void execute_command(const String &filePath, const command &column, const command &order)
{

    std::ifstream in((filePath).get_data());

    if (in.good())
    {
        in.seekg(32);

        dynamic_array<examData> data(DEF_SIZE);
        in >> data;

        if (column == DATE)
        {
            quick_sort(data, 0, data.get_size() - 1);
        }
        else if (column == AGE)
        {
            build_max_heap(data, data.get_size());
            heap_sort(data);
        }
        else if (column == GRADE)
        {
            order == DESC ? radix_sort(data, 0) : radix_sort(data);
        }
        else if (column == NAME)
        {
            radix_sort_name(data);
        }
        else
        {
            radix_sort_subject(data);
        }
        if (order == DESC && column != GRADE)
            data.reverse();

        std::cout << data;
    }
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
        //std::cout << name << std::endl;

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

        //std::cout << "------\n";

        if (is.peek() == '\n')
            break;
    }

    return is;
}

std::ostream &operator<<(std::ostream &os, const dynamic_array<examData> &rhs)
{
    int size = rhs.get_size();
    for (int ed = 0; ed < size; ++ed)
    {
        os << rhs[ed].get_name() << ','
           << rhs[ed].get_age() << ','
           << rhs[ed].get_subject() << ','
           << rhs[ed].get_grade() << ','
           << rhs[ed].get_date().get_year() << '-'
           << std::setfill('0') << std::setw(2)
           << rhs[ed].get_date().get_month() << '-'
           << std::setfill('0') << std::setw(2)
           << rhs[ed].get_date().get_day() << '\n';
    }

    return os;
}
std::ostream &operator<<(std::ostream &os, const String &str)
{
    std::cout << str.get_data();
    return os;
}
