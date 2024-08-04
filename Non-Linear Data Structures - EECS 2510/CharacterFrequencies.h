#ifndef CHARACTERFREQUENCIES_H
#define CHARACTERFREQUENCIES_H

#include <iostream>
#include <string>
#include <utility>
#include <vector>
using namespace std;

class CharacterFrequencies
{
public:
	// Initialize empty instance with no characters
	CharacterFrequencies();


	// Initialize instance with character frequencies from line
	CharacterFrequencies(string line);

	// Read line and add character frequencies to already stored frequencies
	void readString(string line);

	// Reset all character frequencies to 0
	void reset();

	// Return the frequency of character c
	int getFrequency(char c);

	// Print the frequencies of all characters with non-zero frequencies to
	// the console in the following format:
	// r: 4
	// o: 8
	// w: 2
	// n: 2
	// Do not print a line for any element that has 0 frequency!
	void printFrequencies();


private:
	// List of (character, frequency) pairs
	vector<pair<char, int>> frequencies;
};

#endif // !CHARACTERFREQUENCIES_H
