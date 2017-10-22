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

void NthNumber(short n);

int main()
{
	short input = 0;

	std::cin >> input;
	NthNumber(input);
	std::cout << std::endl;
}
void NthNumber(short n)
{
	if (n == 1) std::cout << 1;
	else
	{
		NthNumber(n - 1);
		std::cout << n;
		NthNumber(n - 1);
	}
}


