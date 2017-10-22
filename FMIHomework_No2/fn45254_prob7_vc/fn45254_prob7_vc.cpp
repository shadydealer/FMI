// fn45254_prob7_vc.cpp : Defines the entry point for the console application.
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
* @task 7
* @compiler VC
*
*/

#include "stdafx.h"
#include <iostream>
#include <iomanip>

void mod(unsigned int n, unsigned int m, unsigned int y) {

	unsigned long long sum = 0;

	bool hasSolutions = false;

	for (size_t i = 1; i <= m - 1; i++)
	{
		sum = i;
		for (size_t j = 2; j <= n; j++)
		{
			sum *= i;
			sum %= m;
		}
		if (sum == y)
		{
			if (hasSolutions) std::cout << " ";
			std::cout << i;
			hasSolutions = true;
		}
	}
	if (hasSolutions == false) std::cout << -1;
	std::cout << std::endl;
}
int main()
{
	unsigned int n, m, y = 0;
	std::cin >> n;
	std::cin >> m;
	std::cin >> y;


	if ((n < 1000001) && (m > 1 && m < 100001) && (y < m))
	{
		mod(n, m, y);
	}

	return 0;
}

