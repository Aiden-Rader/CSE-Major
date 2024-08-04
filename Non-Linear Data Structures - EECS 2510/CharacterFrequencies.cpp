/* Aiden Rader
*  Non-Linear Data Structures
*  Dr. Ahmed Kishwar
*  Homework 2
*/

#include <iostream>
#include <vector>
#include <string>
#include "CharacterFrequencies.h"

using namespace std;

//=======================================================================//

CharacterFrequencies::CharacterFrequencies()
{
	//Leave blank, consrtuctor for vector <frequencies>
}

CharacterFrequencies::CharacterFrequencies(string line)
{
	// for each character in the string line.
		for (char character : line)
		{
			//make a placeholder for boolean true or false
			bool isCondition = false;

			//loops for each pair in the ector frequencies.
			for (int i = 0; i < frequencies.size(); i++) 
			{
				//if the character already prent in it then increments the count.
				if (frequencies[i].first == character)
				{
					frequencies[i].second++;
					isCondition = true;
					break;
				}
			}
			//if the character is not in the vector then adds the new pair with (character,1).
			if (isCondition == false)
			{	
				//inserts a character into the vector space
				frequencies.push_back(make_pair(character, 1));
			}
		}
}

//Same as the last procedure
void CharacterFrequencies::readString(string line)
{
	// for each character in the string line.
	for (char character : line)
	{
		//make a placeholder for boolean true or false
		bool isCondition = false;

		//loops for each pair in the ector frequencies.
		for (int i = 0; i < frequencies.size(); i++)
		{
			//if the character already prent in it then increments the count.
			if (frequencies[i].first == character)
			{
				frequencies[i].second++;
				isCondition = true;
				break;
			}
		}
		//if the character is not in the vector then adds the new pair with (character,1).
		if (isCondition == false)
		{
			//insets and element into the vector space, in other words this inserts the character if the character has not already been inserted
			frequencies.push_back(make_pair(character, 1));
		}
	}
}

void CharacterFrequencies::reset()
{
	//changes the all the frequencies of the characters to 0 
	for (int i = 0; i < frequencies.size(); i++) 
	{
		//change the second stored value in the vector which is the int
		frequencies[i].second = 0;
	}
}

int CharacterFrequencies::getFrequency(char character)
{
	//for each pair in the vector
	for (int i = 0; i < frequencies.size(); i++)
	{
		//if the character matches the parameter charecter 
		if (frequencies[i].first == character)
		{
			//return corresponding count of character
			return frequencies[i].second;
		}
	}
	//needed because we have to return an int
	return 0;
}

void CharacterFrequencies::printFrequencies()
{
	//for each pair in the vector
	for (int i = 0; i < frequencies.size(); i++)
	{
		//if the count in the vector is higher then 0
		if (frequencies[i].second > 0)
		{	
			//print out statment with letter and frequency we see the letter in the line
			cout << frequencies[i].first << ": " << frequencies[i].second << endl;

		}
	}
}

//=======================================================================//

//Given Code
int main()
{
	string line = "The quick brown fox jumps over the lazy dog. The quick brown fox jumps over the lazy dog.";
	CharacterFrequencies lineCharFreq;
	lineCharFreq.printFrequencies();

	cout << line << endl;
	lineCharFreq.readString(line);
	lineCharFreq.printFrequencies();

	lineCharFreq.reset();
	lineCharFreq.printFrequencies();

	//=======================================================================//

	string line2 = "Twinkle twinkle little star, how I wonder what you are.";
	cout << line2 << endl;
	CharacterFrequencies line2CharFreq(line2);
	line2CharFreq.printFrequencies();
	line2CharFreq.readString(line2);
	line2CharFreq.printFrequencies();

	//=======================================================================//

	char char1 = 'x';
	cout << "Number of occurrences of character " << char1 << ": ";
	cout << line2CharFreq.getFrequency(char1) << endl;
	char char2 = 'w';
	cout << "Number of occurrences of character " << char2 << ": ";
	cout << line2CharFreq.getFrequency(char2) << endl;

	//=======================================================================//

	return 0;
}