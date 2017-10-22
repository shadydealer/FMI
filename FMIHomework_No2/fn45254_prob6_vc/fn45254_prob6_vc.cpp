// fn45254_prob6_vc.cpp : Defines the entry point for the console application.
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
* @task 6
* @compiler VC
*
*/
#include "stdafx.h"
#include <iostream>

unsigned long long binomFactor(unsigned int n, unsigned int k)
{
	unsigned long long sum = 1;

	for (size_t i = 0; i < k ; ++i)
	{
		sum *= n - i;
		if (sum %(i + 1) == 0)
		{
			sum /= (i + 1);
		}
	}
	return sum;

}
int main()
{
	unsigned int n = 0;
	std::cin >> n;
	unsigned long long sum = 1;
	
	std::cout << 1  << " ";
	for (size_t k = 1; k < n; ++k)
	{
		std::cout << binomFactor(n,k) << " ";
	}
	std::cout << 1 << std::endl;
	return 0;
}

