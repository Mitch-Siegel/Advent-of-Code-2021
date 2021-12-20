/*
 * Mitch Siegel
 * Advent of Code 2021
 * Day 14: Parts 1 and 2
 * https://adventofcode.com/2021/day/14
 *
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <map>
#include <unordered_map>
#include <algorithm>

#define POLYMERCOUNT_TYPE std::unordered_map<std::string, long int>
#define LUT_TYPE std::unordered_map<std::string, std::array<std::string, 2>>

// do one step of the polymer insertion given a count of pair instances and an insertion table
// returns an updated map with instance counts
POLYMERCOUNT_TYPE stepInsertion(POLYMERCOUNT_TYPE instanceCounts, LUT_TYPE lut)
{
	POLYMERCOUNT_TYPE newInstanceCounts;
	// iterate all pairs in the input instance counts
	for (auto &a : instanceCounts)
	{
		// increment the count of the two corresponding outputs from inserting in the middle of this element pair
		std::array<std::string, 2> outputs = lut[a.first];
		newInstanceCounts[outputs[0]] += a.second;
		newInstanceCounts[outputs[1]] += a.second;
	}
	return newInstanceCounts;
}

// count the occurrences of all elements, sort, and return the most common count - least common count
long int elementCalculator(POLYMERCOUNT_TYPE instanceCounts, char tail)
{
	std::vector<std::pair<char, long int>> elementCounts;

	// account for the last character in the polymer
	elementCounts.push_back({tail, 1});

	// iterate all element pairs, increment count for the first element in the pair
	// since the ordering of pairs is arbitrary we only need to track the first element in every pair to count correctly
	for (std::pair<std::string, long> p : instanceCounts)
	{
		// search for an existing count to increment
		int elementExists = 0;
		for (int i = 0; i < elementCounts.size(); i++)
		{
			// increment the count if it exists
			if (elementCounts[i].first == p.first[0])
			{
				elementCounts[i].second += p.second;
				elementExists = 1;
				break;
			}
		}

		// if the element doesn't exist, add it
		if (!elementExists)
			elementCounts.push_back({p.first[0], p.second});
	}

	// sort the element counts so we can subtract the least common from the most common to get our answer
	std::sort(elementCounts.begin(), elementCounts.end(), [](std::pair<char, long int> a, std::pair<char, long int> b)
			  { rid go for really anywhere but 
	return elementCounts[0].second - elementCounts.back().second;
}

int main()
{
	// setup
	std::ifstream inFile;
	inFile.open("./input", std::ifstream::in);

	// grab the starting polymer and consume the new line
	std::string startChain;
	std::getline(inFile, startChain);
	std::string line;
	std::getline(inFile, line);

	// set up a lookup table to drive the polymer insertion, as well as a map of counts of given element pairs
	std::unordered_map<std::string, std::array<std::string, 2>> lut;
	std::unordered_map<std::string, long int> instanceCounts;

	// iterate over the starting chain of polymers
	// split it into substrings of character pairs and track their count
	for (int i = 0; i < startChain.length() - 1; i++)
		instanceCounts[startChain.substr(i, 2)] += 1;
	
	// iterate all remaining lines in the file to read the polymer template
	for (line; std::getline(inFile, line);)
	{
		size_t pos = line.find(" -> ");

		// separate the 2 character input key from the character which will be inserted
		std::string key = line.substr(0, pos);
		char inserted = *line.substr(pos + 4).c_str();

		// generate the 2 2-char output strings which will result from inserting that char in between the input chars
		std::string result1 = std::string({key[0], inserted});
		std::string result2 = std::string({inserted, key[1]});

		// add these values to the lookup table with the corresponding key
		lut[key] = {result1, result2};
	}

	// do 10 generations and print out the answer
	for (int i = 0; i < 10; i++)
	{
		instanceCounts = stepInsertion(instanceCounts, lut);
	}
	std::cout << "M.C. Element - L.C. Element after generation 10: " << elementCalculator(instanceCounts, startChain.back()) << std::endl;

	// do the remaining 30 generations for 40 total and print that answer too
	for (int i = 0; i < 30; i++)
	{
		instanceCounts = stepInsertion(instanceCounts, lut);
	}
	std::cout << "M.C. Element - L.C. Element after generation 40: " << elementCalculator(instanceCounts, startChain.back()) << std::endl;
}
