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

void Sort(double** studentInfo, size_t size);
void Print(double** studentInfo, size_t size);

int main()
{
	size_t lines = 0;
	std::cin >> lines;

	
	double** studentInfo = new (std::nothrow) double*[lines];

	if (studentInfo != nullptr)
	{
		for (size_t i = 0; i < lines; i++)
		{
			studentInfo[i] = new (std::nothrow) double[3];
			if (studentInfo[i] != nullptr)
			{
				std::cin >> studentInfo[i][0];
				std::cin >> studentInfo[i][1];
				std::cin >> studentInfo[i][2];
			}
		}

		Sort(studentInfo, lines);
		Print(studentInfo, lines);
	}

	for (size_t i = 0; i < lines; i++)
	{
		delete studentInfo[i];
	}
	delete studentInfo;
	return 0;
}

void Sort(double** studentInfo, size_t size) {

	double min = 0;
	int index = 0;
	double * d = 0;

	for (size_t i = 0; i < size - 1; i++)
	{
		index = i;
		min = studentInfo[i][0];
		for (size_t j = i; j < size - 1; j++)
		{
			//checks if the faculty numbers are even
			if (min == studentInfo[j + 1][0])
			{
				//checks which of the problem numbers is bigger
				if (studentInfo[index][1] > studentInfo[j + 1][1])
				{
					min = studentInfo[j + 1][0];
					index = j + 1;
				}
			}

			//checks for smaller faculty numbers
			if (min > studentInfo[j + 1][0])
			{
				min = studentInfo[j + 1][0];
				index = j + 1;
			}

		}

		//switches the student info depending on whether there's a new minimum faculty number/problem number
		if (index != i)
		{
			d = studentInfo[index];
			studentInfo[index] = studentInfo[i];
			studentInfo[i] = d;
		}
	}
}
void Print(double** studentInfo, size_t size) {
	for (size_t i = 0; i < size; i++)
	{
		std::cout << studentInfo[i][0] << ' ' << studentInfo[i][1] << ' ' << studentInfo[i][2];
		std::cout << std::endl;
	}
}

