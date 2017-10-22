// fn45254_prob8_vc.cpp : Defines the entry point for the console application.
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
* @task 8
* @compiler VC
*
*/

#include "stdafx.h"
#include <iostream>
int numberLength(int number)
{
	int digitCounter = 0;
	while (number != 0)
	{
		number /= 10;
		digitCounter++;
	}
	return digitCounter;
}

bool areValidNumbers(unsigned int n, unsigned int m, unsigned int k, unsigned int nLength, unsigned int mLength) {

	int denom = 1;
	for (size_t i = 1; i <= nLength; i++)
	{
		if ((n / denom) % 10 >= k)
		{
			return false;
		}
		denom *= 10;
	}

	denom = 1;
	for (size_t i = 1; i < mLength; i++)
	{
		if ((m / denom) % 10 >= k)
		{
			return false;
		}
		denom *= 10;
	}

	return true;
}

int toBaseTen(unsigned int number, unsigned int k, unsigned int numberLength)
{
	int denom = 1;
	int mult = 1;
	int sum = 0;

	for (size_t i = 0; i < numberLength; i++)
	{
		sum += ((number / denom) % 10) *mult;
		denom *= 10;
		mult *= k;
	}
	return sum;
}

int toHomeBase(unsigned int number, unsigned int k, unsigned int numberLength)
{
	int sum = 0;
	int currDigit = 0;
	int mult = 1;

	while (number != 0)
	{
		currDigit = number % k;
		number = (number - currDigit) / k;
		sum += currDigit *mult;
		mult *= 10;
	}
	return sum;
}

int main()
{
	unsigned int n, m, k = 0;
	std::cin >> n;
	std::cin >> m;
	std::cin >> k;

	int nLength = numberLength(n);
	int mLength = numberLength(m);
	if (k == 10)
	{
		std::cout << n + m << std::endl;
	}
	else
	{
		if (areValidNumbers(n, m, k, nLength, mLength) == false)
		{
			std::cout << "Bad input data!" << std::endl;
		}
		else
		{
			int nTen = toBaseTen(n, k, nLength);
			int mTen = toBaseTen(m, k, mLength);

			int sum = nTen + mTen;
			int sumLength = numberLength(sum);

			int homeBaseSum = toHomeBase(sum, k, sumLength);
			std::cout << homeBaseSum << std::endl;

		}
	}

	return 0;
}

