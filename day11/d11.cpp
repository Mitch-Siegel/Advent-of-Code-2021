/*
 * Mitch Siegel
 * Advent of Code 2021
 * Day 11: Parts 1 and 2
 * https://adventofcode.com/2021/day/11
 *
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <array>

std::vector<std::vector<int>> neigborDeltas = {{-1, -1},
											   {-1, 0},
											   {-1, 1},
											   {0, -1},
											   {0, 1},
											   {1, -1},
											   {1, 0},
											   {1, 1}};

// helper function to stick 2 vectors of arrays together into one larger vector
std::vector<std::array<int, 2>> joinFlashLists(std::vector<std::array<int, 2>> a, std::vector<std::array<int, 2>> b)
{
	std::vector<std::array<int, 2>> returnVector;
	returnVector.reserve(a.size() + b.size());
	returnVector.insert(returnVector.end(), a.begin(), a.end());
	returnVector.insert(returnVector.end(), b.begin(), b.end());
	return returnVector;
}

// flashes the octopus at the given coordinate
// recursively flashes any octopi whose energy level crosses the threshold as a result of the flash
// returns a list of the coordinates of all the octopi who have flashed as a result of this operation
std::vector<std::array<int, 2>> flash(std::vector<std::vector<std::array<int, 2>>> *octopi, int y, int x)
{
	// if this octopus has already flashed, return an empty list
	if ((*octopi)[y][x][1])
		return std::vector<std::array<int, 2>>();
	else // otherwise flag it as having flashed
		(*octopi)[y][x][1] = 1;

	// create a list containing this octopus
	std::vector<std::array<int, 2>> flashList = {{y, x}};

	// iterate over all possible neighbors of the flashing octopus
	for (int n = 0; n < 8; n++)
	{
		int newY = y + neigborDeltas[n][0];
		int newX = x + neigborDeltas[n][1];
		
		// if both the coordinates are within a valid range
		if (newY >= 0 && newY < (*octopi).size() && newX >= 0 && newX < (*octopi)[0].size()){
			// increment the energy level of the octopus at these coordinates
			(*octopi)[newY][newX][0]++;
			// if this octopus is now over the flash threshold, make it flash, join the octopi it causes to flash to the running list
			if ((*octopi)[newY][newX][0] > 9)
				flashList = joinFlashLists(flashList, flash(octopi, newY, newX));
		}
	}

	return flashList;
}

int doStep(std::vector<std::vector<std::array<int, 2>>> *octopi)
{
	std::vector<std::array<int, 2>> needFlash;
	for (int i = 0; i < (*octopi).size(); i++)
		for (int j = 0; j < (*octopi)[i].size(); j++)
		{
			// increment the count for each octopus
			// keep track of a list of locations of octopi that will flash as a result of the base increment
			(*octopi)[i][j][0]++;
			if ((*octopi)[i][j][0] > 9)
				needFlash.push_back({i, j});
			
			// clear the "has flashed" flag for each octopus
			(*octopi)[i][j][1] = 0;
		}

	// for every octopus that will flash
	// compute its flash and join all the octopi that will flash as a result of it to the list
	std::vector<std::array<int, 2>> completeFlashList;
	for (std::array<int, 2> i : needFlash)
		completeFlashList = joinFlashLists(completeFlashList, flash(octopi, i[0], i[1]));
	
	// reset the energy level of all octopi who have flashed to 0
	for (std::array<int, 2> i : completeFlashList)
		(*octopi)[i[0]][i[1]][0] = 0;
	

	return completeFlashList.size();
}

int main()
{
	// setup
	std::ifstream inFile;
	inFile.open("./input", std::ifstream::in);

	std::vector<std::vector<std::array<int, 2>>> octopi;

	// read in the starting grid of octopi, parse as ints
	for (std::string line; std::getline(inFile, line);)
	{
		std::vector<std::array<int, 2>> octopiLine;
		for (char c : line)
		{
			octopiLine.push_back({c - 48, 0});
		}
		octopi.push_back(octopiLine);
	}

	std::vector<std::vector<std::array<int, 2>>> octopiCopy = octopi;

	// do part 1 (100 step flash count)
	int totalFlashes = 0;
	for (int step = 0; step < 100; step++)
	
		totalFlashes += doStep(&octopiCopy);
	
	std::cout << "After 100 steps there have been " << totalFlashes << " flashes" << std::endl;

	// loop until all octopi flash, counting generations
	int generationCount = 1;
	while (doStep(&octopi) < (octopi.size() * octopi[0].size()))
		generationCount++;

	std::cout << "It will take " << generationCount << " steps for all octopi to flash simultaneously" << std::endl;
	
	
}
