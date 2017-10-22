// fn45254_prob3_vc.cpp : Defines the entry point for the console application.
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
* @task 3
* @compiler VC
*
*/
#include "stdafx.h"
#include <iostream>

long long denominatorPow(int pow)
{
	long long denominator = 1;
	for (size_t i = 0; i < pow; ++i)
	{
		denominator *= 10;
	}
	return denominator;
}

int numberLength(long long number)
{
	int digitCounter = 0;
	while (number != 0)
	{
		number /= 10;
		digitCounter++;
	}
	return digitCounter;
}

int main()
{
	long long a = 0;
	long long b = 0;

	int counter = 0;
	std::cin >> a;
	std::cin >> b;

	if (a <= b)
	{
		int aDigits = numberLength(a);
		int bDigits = numberLength(b);

		long long denominator = denominatorPow(aDigits);

		while (bDigits >= aDigits)
		{
			if (a == b % denominator)
			{
				counter++;
			}
			b /= 10;
			bDigits--;
		}
	}
	std::cout << counter << std::endl;

	return 0;
}