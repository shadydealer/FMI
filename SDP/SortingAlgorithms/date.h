#pragma once

class date
{
private:
  unsigned long long data;

public:
  date();
  date(const unsigned int,
       const unsigned int,
       const unsigned int);
  //
  //The compiler will generate the following:
  //date (const date&);
  //date& operator=(const date&);
  //~date();
  //
public:
  bool operator>(const date &) const;
  bool operator<(const date &) const;
  bool operator>=(const date &) const;
  bool operator<=(const date &) const;
  bool operator==(const date &) const;
  bool operator!=(const date &) const;

public:
  const unsigned int get_year() const;
  const unsigned int get_month() const;
  const unsigned int get_day() const;
  const unsigned long long get_data() const;
};