/*
 * Mitch Siegel
 * Advent of Code 2021
 * Day 6: Part 1
 * https://adventofcode.com/2021/day/6
 *
 */

#include <iostream>
#include <fstream>
#include <vector>

int main()
{
	// setup
	std::ifstream inFile;
	inFile.open("./input", std::ifstream::in);

	// create a list denoting how many fish there are of a given age (by index)
	std::vector<long int> fishList(9);

	// only 1 line in the input
	std::string line;
	std::getline(inFile, line);

	// parse in all numbers from that line
	size_t pos = 0;
	while ((pos = line.find(',')) != std::string::npos)
	{
		// increment the count of the corresponding age of the fish
		fishList[(std::stoi(line.substr(0, pos)))]++;
		line.erase(0, pos + 1);
	}
	// make sure to catch the last one
	fishList[(std::stoi(line.substr(0, pos)))]++;

	// loop for days
	for (int day = 1; day <= 256; day++)
	{
		// keep track of the number of fish whose cycles just ended
		// this value will be overwritten by updating the other counters
		long int reproducingFish = fishList[0];
		// reduce the time remaining on all fish in the list
		for (int i = 1; i < 9; i++)
			fishList[i - 1] = fishList[i];

		// fish with 0 days remaining reproduce a fish with an 8 day timer
		// SET this value since fish with a 9 day timer don't get overwritten
		fishList[8] = reproducingFish;

		// and the reproducing fish's timer resets to 6
		// ADD to this value since fish with a 6 day timer were fish who previously had a 7 day timer
		// and we don't want to destroy that value in the process
		fishList[6] += reproducingFish;

		// calculate the total number of fish
		long int totalFish = 0;
		for (long int i : fishList)
			totalFish += i;

		std::cout << "After day " << day << " there are " << totalFish << " fish" << std::endl;
	}
}
