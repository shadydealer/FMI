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
int ValidPlans(int** plans, size_t size);
void Print(int** plans, size_t size);
int main()
{
	size_t numberOfPlans = 0;
	std::cin >> numberOfPlans;

	int** plans = new (std::nothrow) int*[numberOfPlans + 1];

	if (plans != nullptr) {
		for (size_t plan = 0; plan < numberOfPlans; plan++)
		{
			plans[plan] = new (std::nothrow) int[4];

			if (plans[plan] != nullptr) {
				for (size_t inf = 0; inf < 4; inf++)
				{
					std::cin >> plans[plan][inf];
				}
			}
		}

		//stores what Baba Penka is looking for in a plan
		plans[numberOfPlans] = new (std::nothrow) int[3];

		if (plans[numberOfPlans] != nullptr) {
			for (size_t inf = 0; inf < 3; inf++)
			{
				std::cin >> plans[numberOfPlans][inf];
			}
		}

		int validPlans = ValidPlans(plans, numberOfPlans);
		if (validPlans > 0) Print(plans, validPlans);
		else std::cout << "No solution" << std::endl;
	}


	for (size_t plan = 0; plan < numberOfPlans; plan++)
	{
		delete plans[plan];
	}
	delete plans;

	return 0;
}
int ValidPlans(int** plans, size_t size) {

	int numberOfValidPlans = 0;
	int cost = 0;
	int* safety = 0;

	//shifts the plans that are not valid to the end of the array
	for (size_t i = 0; i < size -1; i++)
	{
		for (size_t j = i; j <= size-1; j++)
		{
			if (plans[j][1] >= plans[size][0] && plans[j][2] >= plans[size][1] && plans[j][3] >= plans[size][2]) { 
				safety = plans[i];
				plans[i] = plans[j];
				plans[j] = safety;
				numberOfValidPlans++;
				break;
			}
		}
	}

	//sorts the part of the array that matters
	for (size_t i = 0; i < numberOfValidPlans; i++)
	{
		cost = plans[i][0];
		for (size_t j = i; j < numberOfValidPlans - 1; j++)
		{
			if (cost > plans[j + 1][0])
			{
				cost = plans[j + 1][0];
				for (size_t i = numberOfValidPlans - 1; i > 0; i--)
				{
					safety = plans[i];
					plans[i] = plans[i - 1];
					plans[i - 1] = safety;
				}
			}
		}
	}
	return numberOfValidPlans;
}

void Print(int** plans, size_t size) {
	for (size_t i = 0; i < size; i++)
	{
		std::cout << plans[i][0] << ' ' << plans[i][1] << ' ' << plans[i][2] << ' ' << plans[i][3];
		std::cout << std::endl;
	}
}

