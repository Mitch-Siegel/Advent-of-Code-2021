/*
 * Mitch Siegel
 * Advent of Code 2021
 * Day 2: Part 1
 * https://adventofcode.com/2021/day/2
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
	int pos_h = 0;
	int pos_v = 0;
	for (std::string line; std::getline(inFile, line);)
	{
		// find the index of the space separating the dirction from the magnitude
		size_t spaceIndex = line.find(' ');

		// parse direction and magnitude from either side of the space
		std::string direction = line.substr(0, spaceIndex);
		int value = std::stoi(line.substr(spaceIndex));

		// figure out which value to modify, and modify it accordingly
		if (!direction.compare("forward"))
		{
			pos_h += value;
		}
		else if (!direction.compare("up"))
		{
			pos_v -= value;
		}
		else if (!direction.compare("down"))
		{
			pos_v += value;
		}
		else
		{
			std::cerr << "illegal instruction: " << direction;
			exit(1);
		}
	}

	std::cout << (pos_h * pos_v) << std::endl;
}
