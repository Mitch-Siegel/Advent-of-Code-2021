/*
 * Mitch Siegel
 * Advent of Code 2021
 * Day 7: Parts 1 and 2
 * https://adventofcode.com/2021/day/7
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

	// only 1 line in the input, grab it
	std::string line;
	std::getline(inFile, line);

	std::vector<int> crabsList;

	int xMax = 0;

	// parse in all numbers from that line
	size_t pos = 0;
	while ((pos = line.find(',')) != std::string::npos)
	{
		int thisX = std::stoi(line.substr(0, pos));

		if (thisX > xMax)
			xMax = thisX;

		crabsList.push_back(thisX);
		line.erase(0, pos + 1);
	}
	// make sure to catch the last one
	crabsList.push_back(std::stoi(line.substr(0, pos)));

	// calculate the costs of moving any possible distance (with the non-constant fuel burn rate)
	// store this at the index of that distance in the vector
	std::vector<int> nonConstantMoveCosts(xMax);
	nonConstantMoveCosts[0] = 0;
	for (int i = 1; i <= xMax; i++)
		nonConstantMoveCosts[i] = nonConstantMoveCosts[i - 1] + i;

	int leastFuel = INT32_MAX;
	int leastNCFuel = INT32_MAX;
	// examine all possible x values to align to
	for (int alignX = 0; alignX < xMax; alignX++)
	{
		// track fuel used for both fuel consumption rules
		int totalFuelUsed = 0;
		int totalFuelUsedNC = 0;
		// calculate every crab's cost to move to this x value
		for (int crabX : crabsList)
		{
			int deltaX = abs(crabX - alignX);

			// part 1 fuel burn rate
			totalFuelUsed += deltaX;

			// part 2 fuel burn rate
			totalFuelUsedNC += nonConstantMoveCosts[deltaX];
		}

		// track minimum consumptions with each fuel burn rate
		if (totalFuelUsed < leastFuel)
			leastFuel = totalFuelUsed;

		if (totalFuelUsedNC < leastNCFuel)
			leastNCFuel = totalFuelUsedNC;
	}

	std::cout << "It costs " << leastFuel << " with constant fuel burn" << std::endl;
	std::cout << "It costs " << leastNCFuel << " with non-constant fuel burn" << std::endl;
}
