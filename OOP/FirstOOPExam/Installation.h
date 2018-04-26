#pragma once
#include "ElectricalDevice.h"

class Installation
{
private:
	unsigned int maxPowerCapacity;
	unsigned int currPowerCapacity;
	
	unsigned int size;
	unsigned int capacity;
	ElectricalDevice * devices;

public:
	void _resize();
	void _remove(const unsigned int);
public:
	Installation() = delete;
	Installation(const unsigned int);
	~Installation();
public:
	void add_device(const ElectricalDevice &);
	void remove_device(const char *);

public:
	const unsigned int get_max_power() const;
	const unsigned int get_size() const;
	const ElectricalDevice * get_devices() const;
};