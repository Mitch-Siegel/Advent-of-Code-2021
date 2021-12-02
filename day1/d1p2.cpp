/*
 * Mitch Siegel
 * Advent of Code 2021
 * Day 1: Part 2
 * https://adventofcode.com/2021/day/1
 *
 */

#include <iostream>
#include <fstream>

int main()
{
	// same setup as for part 1
	std::ifstream inFile;
	inFile.open("./input", std::ifstream::in);
	int thisDepth;
	int prevDepth = INT32_MAX;
	int deeperCount = 0;
	// use a circular buffer to look through the sliding window at different points
	int c = 0;
	int windows[6];
	std::string line;

	// populate the first 2 slots in the buffer
	for (int i = 0; i < 2; i++)
	{
		std::getline(inFile, line);
		windows[c++] = std::stoi(line);
	}

	// since it is now ensured that we will always have a 3-wide window
	// (where the most recently updated index in the buffer is the last index in the window)
	// we can look at all input until EOF, with the start of the window trailing the index by 2
	for (line; std::getline(inFile, line);)
	{
		// popuate the next slot in the buffer
		windows[c] = std::stoi(line);

		// sum starting from 3 behind where the index is
		thisDepth = windows[(c + 3) % 6];
		thisDepth += windows[(c + 4) % 6];
		thisDepth += windows[(c + 5) % 6];

		if (thisDepth > prevDepth)
			deeperCount++;

		++c %= 6; // keep buffer index within bounds
		prevDepth = thisDepth;
	}
	
	std::cout << deeperCount << std::endl;
}
