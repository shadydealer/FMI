#include "date.h"

//
// Combines the data into one number.
//

//
// Default date ctor.
//
date::date() : data(0)
{
}

//
// date parameter ctor.
//
date::date(const unsigned int rhs_year,
           const unsigned int rhs_month,
           const unsigned int rhs_day) : data(0)
{
    data = rhs_year * 10000 + rhs_month * 100 + rhs_day;
}

bool date::operator>(const date &rhs) const
{
    return data > rhs.data;
}

bool date::operator<(const date &rhs) const
{
    return rhs > *this;
}

bool date::operator<=(const date &rhs) const
{
    return !(*this > rhs);
}

bool date::operator>=(const date &rhs) const
{
    return !(*this < rhs);
}

bool date::operator==(const date &rhs) const
{
    return data == rhs.data;
}

bool date::operator!=(const date &rhs) const
{
    return !(*this == rhs);
}

const unsigned int date::get_year() const
{
    return data / 10000;
}

const unsigned int date::get_month() const
{
    return (data % 10000) / 100;
}

const unsigned int date::get_day() const
{
    return data % 100;
}

const unsigned long long date::get_data() const
{
    return data;
}