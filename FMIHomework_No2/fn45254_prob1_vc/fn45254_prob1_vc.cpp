// fn45254_prob1_vc.cpp : Defines the entry point for the console application.
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
* @task 1
* @compiler VC
*
*/

#include "stdafx.h"
#include <iostream>
#include <iomanip>

int main()
{
	unsigned int positions = 0;

	std::cin >> positions;

	double x = 0;
	double y = 0;
	double previousX = 0;
	double previousY = 0;

	double distance = 0;
	double length = 0;

	for (size_t i = 0; i < positions; i++)
	{
		previousX = x;
		previousY = y;

		std::cin >> x;
		std::cin >> y;

		if ((x >= -5 && x <= 5) && (y >= -2 && y <= 2)) //inside
		{
			length = sqrt((x - previousX)*(x - previousX) + (y - previousY)*(y - previousY));
			distance += ((length*3.14) / 2 + length) / 2;
		}
		if ((x >= -5 && x > 5) && (y >= -2 && y <= 2)) //right
		{

		}
		if ((x < -5 && x <= 5) && (y >= -2 && y <= 2)) //left
		{

		}
		if ((x >= -5 && x <= 5) && (y >= -2 && y > 2)) //over
		{

		}
		if ((x >= -5 && x <= 5) && (y < -2 && y <= 2)) //under
		{

		}
	}
	
	std::cout << std::setprecision(3) << std::fixed << distance << std::endl;
	return 0;
}

