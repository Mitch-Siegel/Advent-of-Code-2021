/*
 * Mitch Siegel
 * Advent of Code 2021
 * Day 9: Part 1
 * https://adventofcode.com/2021/day/9
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

	std::vector<std::vector<int>> map;
	// read in the map
	for (std::string line; std::getline(inFile, line);)
	{
		std::vector<int> thisLine;
		for (char c : line)
			thisLine.push_back(c - 48);
		
		map.push_back(thisLine);
	}


	int risk = 0;
	std::vector<int> basinSizes;
	for (int y = 0; y < map.size(); y++)
	{
		for (int x = 0; x < map[0].size(); x++)
		{
			int examinedCell = map[y][x];

			// examine all points adjacent to this point
			// the 'lower' flag will only stay 1 if no neighboring points are lower than this one
			int lower = 1;
			if (x > 0)
				if (map[y][x - 1] <= examinedCell)
					lower &= 0;
			

			if (x < map[0].size() - 1)
				if (map[y][x + 1] <= examinedCell)
					lower &= 0;
			

			if (y > 0)
				if (map[y - 1][x] <= examinedCell)
					lower &= 0;
			

			if (y < map.size() - 1)
				if (map[y + 1][x] <= examinedCell)
					lower &= 0;
			

			// if this point is a low point
			if (lower)
			{
				// calculate the risk, add it to the total
				risk += (examinedCell + 1);
			}
		}
	}

	std::cout << risk << std::endl;
}
