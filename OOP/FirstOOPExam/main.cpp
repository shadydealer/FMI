#include <iostream>
#include <fstream>
#include "Installation.h"

std::ofstream& operator <<(std::ofstream & out, const Installation& rhs);

int main()
{
	try
	{

	Installation inst(1024);
	Date currDate(22,4,2018);
	ElectricalDevice ed("ivan","vsemogushti",currDate, 1000);
	
	inst.add_device(ed);
	inst.remove_device("ivan");
	}
	catch (const char * msg)
	{
		std::cout << msg;
	}
	return 0;
}

std::ofstream& operator <<(std::ofstream & out,const Installation& rhs)
{
	const unsigned int size = rhs.get_size();
	if (out.good())
		out.write(reinterpret_cast<const char*>((rhs.get_max_power())), sizeof(unsigned int));

	for (unsigned int ed = 0; ed < size; ++ed)
	{
		if (out.good())
		{
			out.write(reinterpret_cast<const char*>(rhs.get_devices()[ed].get_power()), sizeof(unsigned int));
			out.write(reinterpret_cast<const char*>(rhs.get_devices()[ed].get_guarantee().day), sizeof(unsigned short));
			out.write(reinterpret_cast<const char*>(rhs.get_devices()[ed].get_guarantee().month), sizeof(unsigned short));
			out.write(reinterpret_cast<const char*>(rhs.get_devices()[ed].get_guarantee().year), sizeof(unsigned short));
			out.write(reinterpret_cast<const char*>(rhs.get_devices()[ed].get_brand()), strlen(rhs.get_devices()[ed].get_brand()));
			out.write(reinterpret_cast<const char*>(rhs.get_devices()[ed].get_name()), strlen(rhs.get_devices()[ed].get_name()));
		}
	}

	return out;
}

std::ifstream& operator >>(std::ifstream& in, const Installation& rhs)
{
	const unsigned int size = rhs.get_size();


	return in;
}