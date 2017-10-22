// fn45254_prob3.cpp : Defines the entry point for the console application.
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

void DistinguishWords(char* text, int moves);
void PushLetters(char* word, size_t size, int moves);
void Print(char* text);

int main()
{
	char text[10000];
	int n = 0;
	std::cin.getline(text, 10000);
	std::cin >> n;
	DistinguishWords(text, n);
	Print(text);

	return 0;
}
void PushLetters(char* word, size_t size, int moves) {
	char safety = 0;
	int shifts = 0;
	int a = 2; //multiplier for the next valuable position of our current letter, which we will switch with
	int left = 0; //index of the first letter that we have left to shift

	if (moves > size) moves %= size;
	if (moves == 0) return;

	int lettersToShift = size % moves; //number of letters left to shift

	shifts = (size / moves) - 1;

	for (size_t i = 0; i < moves; i++) // switches the positions of some letters using a pseudo selection sort
	{
		for (size_t j = 0; j < shifts; j++)
		{
			safety = word[size - a*moves + i];
			word[size - a*moves + i] = word[size - (a - 1)*moves + i];
			word[size - (a - 1)*moves + i] = safety;
			a++;
		}
		a = 2;
	}

	if (size % moves != 0) 
	{
		while (left < lettersToShift)
		{
			if (moves > size / 2)
			{
				for (size_t i = 0; i < moves; i++) //shifts from front to end
				{
					safety = word[size - moves + i - left];
					word[size - moves + i - left] = word[size - moves - 1 + i - left];
					word[size - moves - 1 + i - left] = safety;
				}
			}
			else 
			{
				for (size_t i = 0; i < moves; i++) //shift from end to front
				{
					safety = word[lettersToShift - left + i];
					word[lettersToShift - left + i] = word[lettersToShift - left + i - 1];
					word[lettersToShift - left + i - 1] = safety;
				}
			}
			left++;
		}
	}
}
void Print(char* text) {
	for (size_t i = 0; text[i] != '\0'; i++)
	{
		std::cout << text[i];
	}
	std::cout << std::endl;
}
void DistinguishWords(char* text, int moves) {

	char *beginning;
	size_t wordSize = 0;
	for (size_t i = 0; text[i - 1] != '\0'; i++)
	{
		//checks if its a word
		if ((text[i] >= 'A' && text[i] <= 'Z') || (text[i] >= 'a' && text[i] <= 'z')
			|| (text[i] == '-' && (((text[i - 1] >= 'A' && text[i - 1] <= 'Z') || (text[i - 1] >= 'a' && text[i - 1] <= 'z'))
				&& (text[i + 1] >= 'A' && text[i + 1] <= 'Z') || (text[i + 1] >= 'a' && text[i + 1] <= 'z'))))
		{
			wordSize++;
		}
		else {

			if (wordSize > 0)
			{
				beginning = &text[i - (wordSize)];
				PushLetters(beginning, wordSize, moves);
				wordSize = 0;
			}
		}
	}
}

