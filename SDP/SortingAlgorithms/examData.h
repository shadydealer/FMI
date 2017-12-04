#pragma once
#include "String.h"
#include "date.h"

class examData
{
private:
  date data;           // data that the exam was held.
  int age;   //age of the student.
  int grade; //grade on the current exam.
  String name;         //name of the student.
  String subject;      //name of the subject he's been examined on.

public:
  examData();
  examData(const  date&,
           const int,
           const int,
           const String &,
           const String &);
           
  examData(const examData &);
  //~examData(); the compiler generated one does the job.
  examData &operator=(const examData &);

public:
  const int get_age() const;
  const int get_grade() const;
  const String get_name() const;
  const String get_subject() const;
  const date get_date() const;
};