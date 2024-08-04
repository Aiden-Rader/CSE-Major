/* Aiden Rader
*  EECS 2510, Section 001
*  Dr.Kishwar Ahmed 
*  Homework 1 Assignment
*/

#include <iostream>
#include <fstream> 
#include <string>
using namespace std;

int countVowels(string wordToBeChecked) 
{
	
	//For each word check if it has atleast one vowel if it does then increase vowelCount
	int vowelCount = 0;
	for (char ch : wordToBeChecked) 
	{
		if (tolower(ch) == 'a' || tolower(ch) == 'e' || tolower(ch) == 'i' || tolower(ch) == 'o' || tolower(ch) == 'u') 
		{
			vowelCount++;
		}
	}
	return vowelCount;
}

//Function to convert a string to lowercase
string toLowercase(string wordToBeLowercase)
{	
	for (char& ch : wordToBeLowercase)
	{
		ch = tolower(ch);
	}
	return wordToBeLowercase;
}

//Main Driver Procedure

int main()
{
	//INITIAL SETUP 

	int wordCount = 0;
	string word;
	string oneVowel;
	string userInputedWord;

	//Read from the txt file
	ifstream inputFile("words.txt");

	//If we cannot find the text file, throw error
	if (!inputFile)
	{
		std::cerr << "The input file 'words.txt' could not be opened." << std::endl;
		return 1;
	}

	//TEST CASE 

	//While loop gets every word in text
	while (inputFile >> word)
	{

		//Convert the word to lowercase before counting vowels
		string lowercaseWord = toLowercase(word);
		int vowels = countVowels(lowercaseWord);
		

		//Check if the current word has exactly one vowel and is longer than the previous one-vowel word found
		if (vowels == 1 && word.length() >= oneVowel.length())
		{
			oneVowel = word;
		}
	}


	//FIRST PROBLEM

	if (!oneVowel.empty())
	{
		std::cout << "The longest word with one vowel is " << oneVowel << std::endl;
	}
	//Should never happen but if it ever did we would catch it
	else
	{
		std::cout << "No word with exactly one vowel found." << std::endl;
	}


	//SECOND PROBLEM

	std::cout << "Enter the word to search for: ";
	std::cin >> userInputedWord;
	bool isFound = false;

	//Close and reopen the input file to start reading from the beginning
	inputFile.close();

	inputFile.open("words.txt");

	while (inputFile >> word)
	{
		//Check if the current word matches the user input ad then exit the loop when word matches
		if (word == userInputedWord)
		{
			isFound = true;
			break; 
		}
	}

	if (isFound == true)
	{
		std::cout << "Found " << userInputedWord << std::endl;
	}
	else
	{
		std::cout << "Could not find " << userInputedWord << std::endl;
	}
	
	//Close File before terminating program
	inputFile.close();
	return 0;
}