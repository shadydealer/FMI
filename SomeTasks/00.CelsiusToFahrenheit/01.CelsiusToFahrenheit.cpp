// 01.CelsiusToFahrenheit.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "iostream"

using namespace std;

int main()
{
	double celsius = 0;
	double fahrenheit = 0;

	printf("Input a temperature measurement in Celsius:\n");
	scanf_s("%lf",&celsius);

	fahrenheit = (celsius * 1.8000) + 32.00;

	printf("%lf in Celsius is %lf in Fahrenheit\n",celsius, fahrenheit);
    return 0;
}

