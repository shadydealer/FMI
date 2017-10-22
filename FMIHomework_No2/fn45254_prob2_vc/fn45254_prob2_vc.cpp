// fn45254_prob2_vc.cpp : Defines the entry point for the console application.
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
* @task 2
* @compiler VC
*
*/

#include "stdafx.h"
#include <iostream>
#include <ctime>
int main()
{
	int n = 0;
	std::cin >> n;

	int twins = 0;

	bool firstIsPrime = true;
	bool secondIsPrime = true;

	size_t currNum = 3;
	size_t secondNum = 0;

	clock_t start = clock();
	double duration;

	while (twins < n)
	{
		firstIsPrime = true;
		secondIsPrime = true;

		for (size_t i = 3; i*i <= currNum; i += 2)
		{
			if (currNum % i == 0)
			{
				firstIsPrime = false;
				break;
			}
		}
		if (firstIsPrime)
		{
			secondNum = currNum + 2;
			for (size_t j = 3; j*j <= secondNum; j += 2)
			{
				if ((secondNum) % j == 0)
				{
					secondIsPrime = false;
					break;
				}
			}
			if (secondIsPrime)
			{
				twins++;
				std::cout << currNum << " " << currNum + 2 << std::endl;

			}
		}
		currNum += 2;
	}
	
	duration = (clock() - start) / (double)CLOCKS_PER_SEC;
	std::cout << duration << std::endl;
	return 0;
}

