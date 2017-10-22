// fn45254_prob4_vc.cpp : Defines the entry point for the console application.
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
* @task 4
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

int checker(int a, int b)
{
	int counter = 0;
	int safety = b;
	while (b != 0 && a !=0) {
		if (a % 10 == b % 10) {
			b = safety;
			a /= 10;
			counter++;
		}
		else b /= 10;
	}
	return counter;
}

int main()
{

	int firstNumber = 0;
	int secondNumber = 0;

	bool same = true;
	std::cin >> firstNumber;
	std::cin >> secondNumber;

	firstNumber = abs(firstNumber);
	secondNumber = abs(secondNumber);

	int firstNumberMatches = 0;
	int secondNumberMatches = 0;

	int firstLength = numberLength(firstNumber);
	int secondLength = numberLength(secondNumber);

	firstNumberMatches = checker(firstNumber, secondNumber);
	secondNumberMatches = checker(secondNumber, firstNumber);

	if (firstNumberMatches == firstLength && secondNumberMatches == secondLength) std::cout << "Yes" << std::endl;
	else std::cout << "No" << std::endl;

	return 0;
}

