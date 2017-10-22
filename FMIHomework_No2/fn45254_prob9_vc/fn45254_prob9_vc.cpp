// fn45254_prob9_vc.cpp : Defines the entry point for the console application.
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
* @task 9
* @compiler VC
*
*/

#include "stdafx.h"
#include <iostream>

bool checker(unsigned long long a, unsigned long long b)
{
	while (b != 0 && a != 0) {
		if (a % 10 == b % 10) {
			b /= 10;
			a /= 10;
		}
		else {
			if ((a / 10) % 10 == b % 10)  return true;
			else return false;
		}
	}
	return true;
}

int main()
{
	unsigned long long a, b = 0;
	std::cin >> a;
	std::cin >> b;


	bool answer = checker(a, b);

	if (answer) std::cout << "Yes" << std::endl;
	else std::cout << "No" << std::endl;
	return 0;
}

