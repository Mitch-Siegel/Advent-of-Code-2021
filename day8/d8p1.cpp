/*
 * Mitch Siegel
 * Advent of Code 2021
 * Day 8: Part 1
 * https://adventofcode.com/2021/day/8
 *
 */

#include <iostream>
#include <fstream>
#include <vector>

// returns 1 if the signal pattern is one of the ones we know based on the number of segments it has illuminated
int patternIsUnique(std::string signalPattern)
{
	switch (signalPattern.length())
	{
	case 2:
	case 3:
	case 4:
	case 7:
		return 1;
		break;
	default:
		return 0;
		break;
	}
}

int main()
{
	// setup
	std::ifstream inFile;
	inFile.open("./input", std::ifstream::in);

	int count = 0;

	// for every line in the input file
	for (std::string line; std::getline(inFile, line);)
	{
		std::string outputVals = line.substr(line.find('|') + 1);
		size_t pos = 0;
		// for every value in the output values
		while ((pos = outputVals.find(' ')) != std::string::npos)
		{
			// update the count if this value is one of the ones with a unique number of illuminated segments
			count += patternIsUnique(outputVals.substr(0, pos));
			outputVals.erase(0, pos + 1);
		}
		// be sure to catch the last value on the line
		count += patternIsUnique(outputVals.substr(0, pos));
	}

	std::cout << count << std::endl;
}
