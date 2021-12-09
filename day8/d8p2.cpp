/*
 * Mitch Siegel
 * Advent of Code 2021
 * Day 8: Part 2
 * https://adventofcode.com/2021/day/8
 *
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

// determines whether a given string contains at least all the characters in another
int containsAll(std::string query, std::string comparator)
{
	for (char c : query)
		if (comparator.find(c) == std::string::npos)
			return 0;

	return 1;
}

// string lookup, returns index of key corresponding to input
int decode(std::vector<std::string> keys, std::string input)
{
	for (int i = 0; i < keys.size(); i++)
		if (!input.compare(keys[i]))
			return i;
	std::cout << "Something broke while decoding :(" << std::endl;
	exit(1);
}

int main(int argc, char *argv[])
{
	// setup
	std::ifstream inFile;
	inFile.open("./input", std::ifstream::in);

	std::vector<int> powers = {1, 10, 100, 1000};
	int outputSum = 0;
	for (std::string line; std::getline(inFile, line);)
	{
		std::vector<std::string> sixSegmentUnknowns;
		std::vector<std::string> fiveSegmentUnknowns;
		std::vector<std::string> decodedInputs(10);

		std::string inputValues = line.substr(0, line.find('|'));
		std::string outputValues = line.substr(line.find("| ") + 2);
		size_t pos = 0;

		// loop over all 10 of the input values
		// assign the unique values (which we know by number of illuminated segments)
		// list the ones we don't by their length so we can reason them out
		for (int i = 0; i < 10; i++)
		{
			pos = inputValues.find(' ');
			std::string signalPattern = inputValues.substr(0, pos);

			switch (signalPattern.length())
			{
			case 2:
				decodedInputs[1] = signalPattern;
				break;
			case 3:
				decodedInputs[7] = signalPattern;
				break;
			case 4:
				decodedInputs[4] = signalPattern;
				break;
			case 7:
				decodedInputs[8] = signalPattern;
				break;
			case 6:
				sixSegmentUnknowns.push_back(signalPattern);
				break;
			case 5:
				fiveSegmentUnknowns.push_back(signalPattern);
				break;
			}

			inputValues.erase(0, pos + 1);
		}

		// deduce 9
		for (int i = 0; i < 3; i++)
		{
			// 9 will be the only one containing all of 4's segments
			if (containsAll(decodedInputs[4], sixSegmentUnknowns[i]))
			{
				decodedInputs[9] = sixSegmentUnknowns[i];
				sixSegmentUnknowns.erase(sixSegmentUnknowns.begin() + i);
				break;
			}
		}
		// deduce 0
		for (int i = 0; i < 2; i++)
		{
			// 0 will be the only remaining 6 segment digit containing all of 1's segments
			if (containsAll(decodedInputs[1], sixSegmentUnknowns[i]))
			{
				decodedInputs[0] = sixSegmentUnknowns[i];
				sixSegmentUnknowns.erase(sixSegmentUnknowns.begin() + i);
				break;
			}
		}
		// the last digit with 6 segments illuminated will be 6
		decodedInputs[6] = sixSegmentUnknowns[0];

		// deduce 3
		for (int i = 0; i < 3; i++)
		{
			// 3 will be the only 5 segment number containing all of 1's segments
			if (containsAll(decodedInputs[1], fiveSegmentUnknowns[i]))
			{
				decodedInputs[3] = fiveSegmentUnknowns[i];
				fiveSegmentUnknowns.erase(fiveSegmentUnknowns.begin() + i);
				break;
			}
		}

		// deduce 5
		for (int i = 0; i < 2; i++)
		{
			// 5 will be the only 5 segment number, and all its segments will be contained in 9
			// operand order is swapped here because 9 has all segments from 5 but not vice versa
			if (containsAll(fiveSegmentUnknowns[i], decodedInputs[9]))
			{
				decodedInputs[5] = fiveSegmentUnknowns[i];
				fiveSegmentUnknowns.erase(fiveSegmentUnknowns.begin() + i);
				break;
			}
		}
		// the remaining five segment number will be 2
		decodedInputs[2] = fiveSegmentUnknowns[0];

		// now we have decoded all of the numbers, so let's alphabetize them to make comparison easy
		for (int i = 0; i < 10; i++)
		{
			std::sort(decodedInputs[i].begin(), decodedInputs[i].end());
		}

		std::vector<int> thisOutput(4, -1);
		pos = 0;

		// scrape through the 4 digits the submarine displayed
		// decode each digit and add it (times its respective power of 10) to the total
		for (int i = 0; i < 5; i++)
		{
			pos = outputValues.find(' ');
			std::string value = outputValues.substr(0, pos);
			std::sort(value.begin(), value.end());
			thisOutput[i] = decode(decodedInputs, value);
			outputSum += decode(decodedInputs, value) * powers[3 - i];
			outputValues.erase(0, pos + 1);
		}
	}

	std::cout << outputSum << std::endl;
}
