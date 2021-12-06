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

	std::vector<int> fishList;

	// only 1 line in the input
	std::string line;
	std::getline(inFile, line);
	size_t pos = 0;
	while ((pos = line.find(',')) != std::string::npos)
	{
		fishList.push_back(std::stoi(line.substr(0, pos)));
		line.erase(0, pos + 1);
	}
	// make sure to catch the last one
	fishList.push_back(std::stoi(line.substr(0, pos)));

	for (int day = 0; day < 256; day++)
	{
		int numToAdd = 0;
		for (int i = 0; i < fishList.size(); i++)
		{
			if (fishList[i] == 0)
			{
				numToAdd++;
				fishList[i] = 6;
			}
			else
				fishList[i]--;
		}
		for (numToAdd; numToAdd > 0; numToAdd--)
			fishList.push_back(8);

		std::cout << "After day " << day + 1 << " there are " << fishList.size() << " fish" << std::endl;
	}
}
