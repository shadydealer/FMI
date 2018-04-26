#include "ElectricalDevice.h"

bool Date::_valid_day(const unsigned short day)
{
	return (day >= 1 && day <= 31);
}

bool Date::_valid_month(const unsigned short month)
{
	return (month >= 1 && month <= 12);
}

bool Date::_valid_year(const unsigned short year)
{
	return (year >= 2018);
}

bool Date::_valid_date(const unsigned short rhsDay,
	const unsigned short rhsMonth,
	const unsigned short rhsYear)
{
	if (_valid_day(rhsDay))
	{
		if (_valid_month(rhsMonth))
		{
			if (_valid_year(rhsYear))
			{
				return true;
			}
		}
	}
	return false;
}
Date::Date(const unsigned short rhsDay,
	const unsigned short rhsMonth,
	const unsigned short rhsYear)

{
	if (_valid_date(rhsDay, rhsMonth, rhsYear))
	{
		day = rhsDay;
		month = rhsMonth;
		year = rhsYear;
	}
	else
		throw "Invalid date values.\n";
}

Date& Date::operator=(const Date& rhs)
{
	if (this != &rhs)
	{
		day = rhs.day;
		month = rhs.month;
		year = rhs.year;
	}

	return *this;
}

void ElectricalDevice::_strcpy(char *& dest, const char * from)
{
	if (from)
	{
		const unsigned int fromLen = strlen(from);


		char * temp = new char[fromLen + 1];

		if (temp)
		{
			strcpy(temp, from);
			delete[] dest;
			dest = temp;
		}
		else
		{
			"Failed to allocate enough memory.\n";
		}
	}
	else
	{
		delete[] dest;
		dest = nullptr;
	}
}

ElectricalDevice::ElectricalDevice() :wats(0),
guarantee(1, 1, 2018),
name(nullptr),
brand(nullptr)
{
}

ElectricalDevice::ElectricalDevice(const char * rhsName,
	const char * rhsBrand,
	const Date& rhsDate,
	const unsigned int rhsPower) : ElectricalDevice()
{
	try
	{
		set_name(rhsName);
		set_brand(rhsBrand);
		set_guarantee(rhsDate);
		set_power(rhsPower);
	}
	catch (const char* msg)
	{
		delete[] name;
		delete[] brand;
	}
}


ElectricalDevice::ElectricalDevice(const ElectricalDevice & rhs) :ElectricalDevice()
{
	try
	{
		_copyED(rhs);
	}
	catch (const char * errMsg)
	{
		delete[] name;
		delete[] brand;

		throw errMsg;
	}
}

void ElectricalDevice::_copyED(const ElectricalDevice &rhs)
{
	wats = rhs.wats;
	guarantee = rhs.guarantee;
	_strcpy(name, rhs.name);
	_strcpy(brand, rhs.brand);
}
ElectricalDevice& ElectricalDevice::operator=(const ElectricalDevice &rhs)
{
	if (this != &rhs)
	{
		_copyED(rhs);
	}
	return *this;
}
ElectricalDevice::~ElectricalDevice()
{
	delete[] name;
	delete[] brand;
}

void ElectricalDevice::set_name(const char * str)
{
	_strcpy(name, str);
}

void ElectricalDevice::set_brand(const char * str)
{
	_strcpy(brand, str);
}

void ElectricalDevice::set_guarantee(const Date & rhs)
{
	try
	{
		guarantee = rhs;
	}
	catch (const char * errMsg)
	{
		std::cout << "Failed to set date to: "
			<< rhs.day << "."
			<< rhs.month << "."
			<< rhs.year << "\n";

		throw "Invalid date input.\n";
	}
}

void ElectricalDevice::set_power(const unsigned int rhsWats)
{
	wats = rhsWats;
}

const char * ElectricalDevice::get_name() const
{
	if (name)
		return name;
	else
		return "";
}

const char * ElectricalDevice::get_brand() const
{
	if (brand)
		return brand;
	else
		return "";
}

const Date& ElectricalDevice::get_guarantee() const
{
	return guarantee;
}

const unsigned int ElectricalDevice::get_power() const
{
	return wats;
}