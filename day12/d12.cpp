/*
 * Mitch Siegel
 * Advent of Code 2021
 * Day 12: Parts 1 and 2
 * https://adventofcode.com/2021/day/12
 *
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

// data structure to keep track of caves, their size, and their connected caves
class Cave
{
public:
	std::string name;
	int big;
	std::vector<Cave *> connections;
	Cave(std::string name)
	{
		this->name = name;

		// if the cave's name is the same thing in uppercase, this is a big cave
		std::string upper = name;
		for (int i = 0; i < upper.size(); i++)
			upper[i] = toupper(upper[i]);

		if (!name.compare(upper))
			this->big = 1;
		else
			this->big = 0;
	}

	void connect(Cave *newConnection)
	{
		this->connections.push_back(newConnection);
	}
};

// given a vector of cave pointers, return the cave with a given name if found
Cave *getCaveByName(std::vector<Cave *> *cavesList, std::string name)
{
	for (int i = 0; i < cavesList->size(); i++)
		if (!cavesList->at(i)->name.compare(name))
			return cavesList->at(i);
	
	return nullptr;
}

// take a pointer to a vector of caves
// make sure both caves exist in the list, if not add them
// then add each cave to the other's connections list
void addConnection(std::vector<Cave *> *cavesList, std::string cave1, std::string cave2)
{
	if (getCaveByName(cavesList, cave1) == nullptr)
		cavesList->push_back(new Cave(cave1));

	if (getCaveByName(cavesList, cave2) == nullptr)
		cavesList->push_back(new Cave(cave2));

	getCaveByName(cavesList, cave1)->connect(getCaveByName(cavesList, cave2));
	getCaveByName(cavesList, cave2)->connect(getCaveByName(cavesList, cave1));
}

int countPaths(std::vector<Cave *> currentPath, Cave *here, int revisitSmalls)
{
	// add the current cave to the path
	currentPath.push_back(here);
	// if we found the end of a path, return 1 
	if (!here->name.compare("end"))
		return 1;

	int pathsCount = 0;

	// look at all caves adjacent to where we are currently
	for (int ci = 0; ci < here->connections.size(); ci++)
	{
		Cave *neighbor = here->connections[ci];
		// never visit the start cave
		if (neighbor->name.compare("start"))
		{
			// always visit big caves
			if (neighbor->big)
				pathsCount += countPaths(currentPath, neighbor, revisitSmalls);
			else
			{
				// looking at only small caves
				// set a flag and look through where we've already been
				int allowVisit = 1;
				for (int i = 0; i < currentPath.size(); i++)
				{
					// if the neighbor we intend to visit has been seen before
					if (currentPath[i] == neighbor)
					{
						allowVisit = 0;
						// only visit it if we are allowed to revisit small caves
						if (revisitSmalls)
						{
							// since we have just revisited a small cave, we are no longer allowed to revisit small caves
							pathsCount += countPaths(currentPath, neighbor, 0);
							break;
						}
					}
				}
				// if looking at a small cave and we haven't seen it, visit it
				if (allowVisit)
					pathsCount += countPaths(currentPath, neighbor, revisitSmalls);
			}
		}
	}
	return pathsCount;
}

int main()
{
	// setup
	std::ifstream inFile;
	inFile.open("./input", std::ifstream::in);

	std::vector<Cave *> caves;
	// read in the caves, add them and their connections to the list
	for (std::string line; std::getline(inFile, line);)
	{
		size_t pos = line.find("-");
		addConnection(&caves, line.substr(0, pos), line.substr(pos + 1));
	}

	// calculate the number of paths with and without the small cave revisit rule
	int part1Paths = countPaths({}, getCaveByName(&caves, "start"), 0);
	int part2Paths = countPaths({}, getCaveByName(&caves, "start"), 1);

	std::cout << "Part 1 - don't revisit small caves: " << part1Paths << " paths" << std::endl;
	std::cout << "Part 2 - revisit one small cave twice: " << part2Paths << " paths" << std::endl;

	// cleanup
	for (Cave *c : caves)
	{
		delete c;
	}
}
