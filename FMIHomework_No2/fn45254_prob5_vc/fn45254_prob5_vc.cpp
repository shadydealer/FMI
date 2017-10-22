// fn45254_prob5_vc.cpp : Defines the entry point for the console application.
//

/**
*
* Solution to homework task
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2016/2017
*
* @author Dimitur Lukanov
* @idnumber 45254
* @task 5
* @compiler VC
*
*/

#include "stdafx.h"
#include <iostream>
#include <iomanip>

double distanceTraveled() {

	unsigned int n = 0; //number of readings
	std::cin >> n;

	double tbr = 0; //time between readings
	std::cin >> tbr;

	double sum = 0;
	double currReading = 0;
	double currDistance = 0;
	double previousSpeed = 0;
	double currSpeed = 0;


	for (size_t i = 0; i < n; i++)
	{
		std::cin >> currReading;

		currDistance = previousSpeed*tbr + 0.5*currReading*(tbr*tbr);
		if (currDistance > 0) sum += currDistance;

		currSpeed = previousSpeed + currReading*tbr;
		if (currSpeed < 0) previousSpeed = 0;
		else previousSpeed = currSpeed;
	}
	return sum;
}

int main()
{
	double sum = distanceTraveled();

	std::cout << std::fixed;
	std::cout.precision(5);
	std::cout << sum << std::endl;
	return 0;
}

