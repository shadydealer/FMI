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
void Sort(int* numbers, size_t size);
void Print(int* numbers, size_t size);

int main()
{
	int amount = 0;
	std::cin >> amount;

	int* listOfNumbers = new (std::nothrow) int[amount];

	if (listOfNumbers != nullptr)
	{
		for (size_t i = 0; i < amount; i++)
		{
			std::cin >> listOfNumbers[i];
		}

		Sort(listOfNumbers, amount);
		Print(listOfNumbers, amount);
	}

	delete listOfNumbers;
	return 0;
}

void Sort(int* numbers, size_t size) {
	int safety = 0;
	int ind = 0; //index at which every nummbers should be placed in


	//sorts out the numbers that have a remainder of 1
	for (size_t i = 0; i < size; i++)
	{
		if (numbers[i] % 3 == 1) {
			ind++;
			for (size_t j = i; j >= ind; j--)
			{
				safety = numbers[j - 1];
				numbers[j - 1] = numbers[j];
				numbers[j] = safety;
			}
		}
	}

	ind = 0;

	//sorts out the numbers that have a remainder of 0
	for (size_t i = 0; i < size; i++)
	{
		if (numbers[i] % 3 == 0) {
			ind++;
			for (size_t j = i; j >= ind; j--)
			{
				safety = numbers[j - 1];
				numbers[j - 1] = numbers[j];
				numbers[j] = safety;
			}
		}
	}
}
void Print(int* numbers, size_t size) {

	std::cout << numbers[0];
	for (size_t i = 1; i < size; i++)
	{
		std::cout << ' ' << numbers[i];
	}
	std::cout << std::endl;
}


