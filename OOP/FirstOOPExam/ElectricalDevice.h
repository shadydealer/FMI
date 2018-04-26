#pragma once
#include <string.h>
#include <iostream>

struct Date
{
	unsigned short day;
	unsigned short month;
	unsigned short year;
private:
	bool _valid_day(const unsigned short);
	bool _valid_month(const unsigned short);
	bool _valid_year(const unsigned short);

	bool _valid_date(const unsigned short,
		const unsigned short,
		const unsigned short);
public:
	Date() = delete;
	Date(const unsigned short, const unsigned short, const unsigned short);
	Date& operator=(const Date&);
};
class ElectricalDevice
{
private:
	unsigned int wats;
	Date guarantee;
	char * name;
	char * brand;
private:
	void _strcpy(char *&, const char *);
	void _copyED(const ElectricalDevice &);
public:
	ElectricalDevice();
	ElectricalDevice(const ElectricalDevice &);
	ElectricalDevice& operator=(const ElectricalDevice &);
	~ElectricalDevice();

	ElectricalDevice(const char *,
					 const char *,
					 const Date&,
					 const unsigned int);

public:
	void set_name(const char *);
	void set_brand(const char *);
	void set_guarantee(const Date &);
	void set_power(const unsigned int);

	const char * get_name() const;
	const char * get_brand() const;
	const Date& get_guarantee() const;
	const unsigned int get_power() const;
};