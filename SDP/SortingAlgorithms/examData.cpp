#include "examData.h"

//
// examData default ctor.
//
examData::examData() : data(),
                       age(0),
                       grade(0),
                       name(),
                       subject()
{
}

//
// examData parameter ctor.
//
examData::examData(const date &rhs_data,
                   const int rhs_age,
                   const int rhs_grade,
                   const String &rhs_name,
                   const String &rhs_subject) :
                   data(rhs_data),
                   age(rhs_age),
                   grade(rhs_grade),
                   name(rhs_name),
                   subject(rhs_subject)
{
}

//
//examData copy ctor.
//
examData::examData(const examData &rhs) :
                   examData(rhs.data,
                            rhs.age,
                            rhs.grade,
                            rhs.name,
                            rhs.subject)
{
}

//
// examData operator=.
//
examData &examData::operator=(const examData &rhs)
{
    if (this != &rhs)
    {
        age = rhs.age;
        grade = rhs.grade;
        name = rhs.name;
        subject = rhs.subject;
        data = rhs.data;
    }
    return *this;
}

const int examData::get_age() const
{
    return age;
}

const int examData::get_grade() const
{
    return grade;
}

const String examData::get_name() const
{
    return name;
}

const String examData::get_subject() const
{
    return subject;
}

const date examData::get_date() const
{
    return data;
}