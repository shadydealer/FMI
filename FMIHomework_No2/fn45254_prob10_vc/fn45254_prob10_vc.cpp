// fn45254_prob10_vc.cpp : Defines the entry point for the console application.
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
* @task 10
* @compiler VC
*
*/

#include "stdafx.h"
#include <iostream>
int max(int n1, int n2) {

	if (n1 >= n2)
	{
		return n1;
	}
	return n2;
}
int maxPow(unsigned long long number, unsigned long long ceiling)
{
	int pow = 0;
	while (ceiling % number == 0) {
		pow++;
		ceiling /= number;
	}
	return pow;
}
int main()
{
	unsigned long long nq, p1, n, p2 = 0;
	int p1MaxPow = 0;
	int p2MaxPow = 0;

	std::cin >> nq;
	for (size_t i = 0; i < nq; i++)
	{
		std::cin >> p1;
		std::cin >> n;
		std::cin >> p2;

		p1MaxPow = 0;
		p2MaxPow = 0;

		if (n == 0)
		{
			std::cout << "infinity" << std::endl;
		}
		else
		{
			p1MaxPow = maxPow(p1, n);
			p2MaxPow = maxPow(p2, n);

			std::cout << max(p1MaxPow, p2MaxPow) << std::endl;
		}
	}
	return 0;
}

