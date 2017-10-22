// fn45254_prob7_vc.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
void ConvertToPigLatin(char* text);

int main()
{
	char text[10000];
	std::cin.getline(text, 10000);
	ConvertToPigLatin(text);
	return 0;
}
void ConvertToPigLatin(char* text) {

	char *beginning; //stores the begining of the word
	size_t wordSize = 0; //stores the length of the word
	bool beginsWithAConsonant = false; //stores whether the word begins with a consonant or not
	bool isUpperCase = false; //stores whether the word is uppercased or only one of the letters is upper cased
	size_t startLength = 0; // size of the letters in the beginning
	for (size_t i = 0; text[i-1] != '\0'; i++)
	{
		//checks íf it's a word
		if ((text[i] >= 'A' && text[i] <= 'Z') || (text[i] >= 'a' && text[i] <= 'z')
			|| (text[i] == '-' && (((text[i - 1] >= 'A' && text[i - 1] <= 'Z') || (text[i - 1] >= 'a' && text[i - 1] <= 'z'))
				&& (text[i + 1] >= 'A' && text[i + 1] <= 'Z') || (text[i + 1] >= 'a' && text[i + 1] <= 'z'))))
		{
			//checks if it begins with a consonant
			if (!beginsWithAConsonant && wordSize == 0)
			{
				while (!(text[i] == 'A' || text[i] == 'a' || text[i] == 'E' || text[i] == 'e'
					|| text[i] == 'I' || text[i] == 'i' || text[i] == 'O' || text[i] == 'o'
					|| text[i] == 'U' || text[i] == 'u' || text[i] == 'Y' || text[i] == 'y'))
				{
					//checks if the next letter is upper cased in order to distinguish the words which are fully upper cased
					if (text[i] >= 'A' && text[i] <= 'Z' && text[i +1] >= 'a' && text[i +1] <= 'z') {
						text[i] += ('a' - 'A'); // switches from upper to lower case
						isUpperCase = true;
					}

					wordSize++;
					startLength++;
					i++;
					beginsWithAConsonant = true;
				}
			}
			wordSize++;
		}
		else {
			if (wordSize > 0)
			{
				beginning = &text[i - (wordSize)];
				if (isUpperCase) beginning[startLength] -= ('a' - 'A'); //switches from lower to upper case if needed

				//prints the second part of the word
				for (size_t j = startLength; j < wordSize; j++)
				{
					std::cout << beginning[j];
				}
				//print the first part of the word
				for (size_t j = 0; j < startLength; j++)
				{
					std::cout << beginning[j];
				}

				//prints "ay" depending on the casing of the word
				if (beginsWithAConsonant)
				{
					if (wordSize != 1 && beginning[startLength +1] >= 'A' && beginning[startLength +1] <= 'Z') std::cout << "AY";
					else std::cout << "ay";
				}

				//prints "way" depending on the casing of the word
				else
				{
					if (wordSize != 1 && beginning[startLength+1] >= 'A' && beginning[startLength+1] <= 'Z') std::cout << "WAY";
					else std::cout << "way";
				}
			}
			if (text[i] != '\0') std::cout << text[i];

			wordSize = 0;
			startLength = 0;
			beginsWithAConsonant = false;
			isUpperCase = false;
		}
	}
	std::cout << std::endl;
}


