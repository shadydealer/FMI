// fn45254_prob5_vc.cpp : Defines the entry point for the console application.
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
* @task 5
* @compiler VC
*
*/

#include "stdafx.h"
#include <iostream>

unsigned long DistinguishNumbersAndSum(char* equation);
unsigned long ToBaseTen(char* equation, size_t size, short base);
void Print(char* number, size_t size);

int main()
{
	char equation[1000];
	std::cin.getline(equation, 1000);
	unsigned long result = DistinguishNumbersAndSum(equation);
	std::cout << result << std::endl;
	return 0;
}

unsigned long DistinguishNumbersAndSum(char* equation) {

	size_t numberLength = 0;
	short base = 0;
	long sum = 0;

	for (size_t i = 0; equation[i - 1] != '\0'; i++)
	{
		//sets the base of the number
		if (base == 0) {

			//checks if its a decimal number
			if (equation[i] >= '1' && equation[i] <= '9')
			{
				base = 10;
				numberLength++;
				i++;
			}
			//checks it's a hexadecimal, binary number or octal
			if (equation[i] == '0')
			{
				//checks of it's octal
				if (equation[i + 1] >= '1' && equation[i + 1] <= '8') {
					base = 8;
					i++;
				}
				//checks if it's binary
				if (equation[i + 1] == 'b') {
					base = 2;
					i += 2;
				}

				//checks if it's hexadecimal
				if (equation[i + 1] == 'x')
				{
					base = 16;
					i += 2;
				}
			}
		}

		//checks whether the input number is of a valid base
		if (base != 0)
		{
			//checks for zeros in the begining of the number
			if ((!(equation[i] == '0' && numberLength == 0))
				&& ((equation[i] >= '0' && equation[i] <= '9') || (equation[i] >= 'A' && equation[i] <= 'F')))
			{
				numberLength++;
			}
			else
			{
				//adds the number to the sum
				if (numberLength > 0) {
					sum += ToBaseTen(&equation[i - numberLength - 1], numberLength, base);
					numberLength = 0;
					base = 0;
				}
			}
		}
	}
	return sum;
}
unsigned long ToBaseTen(char* equation, size_t size, short base) {
	int sum = 0;
	long pow = 1;

	//converts from binary to decimal and returns the sum of the number
	if (base == 2)
	{
		for (size_t i = size; i > 0; i--)
		{
			sum += (equation[i] - 48) * pow;
			pow *= 2;
		}
		return sum;
	}

	//converts from octal to decimal and returns the sum of the number
	else if (base == 8)
	{
		for (size_t i = size; i > 0; i--)
		{
				sum += (equation[i] - 48) * pow;
				pow *= 8;
		}
		return sum;
	}

	//returns the sum of the number
	else if (base == 10)
	{
		for (size_t i = size; i > 0; i--)
		{
			sum += (equation[i] - 48) * pow;
			pow *= 10;
		}
		return sum;
	}

	//converts from hexadecimal to decimal and returns  the sum of the number
	else
	{
		for (size_t i = size; i > 0; i--)
		{
			if (equation[i] >= 'A' && equation[i] <= 'F')
			{
				sum += (equation[i] - 55) * pow;
				pow *= 16;
			}
			else
			{
				sum += (equation[i] - 48) * pow;
				pow *= 16;
			}
		}
		return sum;
	}
}
void Print(char* number, size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		std::cout << number[i];
	}
	std::cout << std::endl;
}
