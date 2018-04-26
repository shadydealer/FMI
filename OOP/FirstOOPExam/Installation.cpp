#include "Installation.h"

Installation::Installation(const unsigned int powerCap) : maxPowerCapacity(powerCap),
														  currPowerCapacity(0),
														  size(0),
														  capacity(0),
														  devices(nullptr)
{
}

Installation::~Installation()
{
	delete[] devices;
}

void Installation::_resize()
{
	const unsigned int newCapacity = !capacity ? 2 : capacity * 2;
	ElectricalDevice * temp = new ElectricalDevice[newCapacity];
	
	for (unsigned int ed = 0; ed < size; ++ed)
		temp[ed] = devices[ed];

	delete[] devices;
	devices = temp;

	capacity = newCapacity;

}

void Installation::add_device(const ElectricalDevice& rhs)
{
	if (size == capacity - 1 || !capacity)
		_resize();
	
	if (currPowerCapacity + rhs.get_power() <= maxPowerCapacity)
	{
		devices[size++] = rhs;
		currPowerCapacity += maxPowerCapacity;
	}
	else
		std::cout << "Devices consumes too much power to be added"
				  << "to the installation with max capacity: " << maxPowerCapacity
				  << " and current capacity: " << currPowerCapacity << '\n';
}
void Installation::_remove(const unsigned int index)
{
	currPowerCapacity -= devices[index].get_power();

	for (unsigned int i = index; i < capacity -1; ++i)
		devices[i] = devices[i + 1];

	--size;
}

void Installation::remove_device(const char * deviceName)
{
	for (unsigned int ed = 0; ed < size; ++ed)
	{
		if (strcmp(devices[ed].get_name(), deviceName) == 0)
		{
			_remove(ed);
			break;
		}
	}
}

const unsigned int Installation::get_size() const
{
	return size;
}

const unsigned int Installation::get_max_power() const
{
	return maxPowerCapacity;
}

const ElectricalDevice * Installation::get_devices() const
{
	return devices;
}