/*
 * Mitch Siegel
 * Advent of Code 2021
 * Day 13: Parts 1 and 2
 * https://adventofcode.com/2021/day/13
 *
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <array>

// helper function to print out the final points on the paper after folding is done
void printPointsList(std::vector<std::array<int, 2>> list)
{
	// our paper will be 7 units high and 40 units wide after we fold it
	// so this is as big as the grid of chars needs to be
	std::vector<std::vector<char>> output;
	for (int i = 1; i < 7; i++)
		output.push_back(std::vector<char>(40, ' '));

	// iterate all points in the list, add a '#' at their coordinates on the grid
	for (std::array<int, 2> p : list)
		output[p[1]][p[0]] = '#';

	// iterate and print all lines in the grid
	for (std::vector<char> line : output)
	{
		for (char c : line)
			std::cout << c;
		std::cout << std::endl;
	}
}

// helper function to insert non-duplicate points to a vector
void insertPoint(std::vector<std::array<int, 2>> *pointsList, std::array<int, 2> newPoint)
{
	for (std::array<int, 2> p : *pointsList)
		if (p[0] == newPoint[0] && p[1] == newPoint[1])
			return;

	pointsList->push_back(newPoint);
}

int main()
{
	// setup
	std::ifstream inFile;
	inFile.open("./input", std::ifstream::in);

	// read in all the points (all lines until a blank line)
	std::vector<std::array<int, 2>> pointsList;
	for (std::string line; std::getline(inFile, line);)
	{
		if (!line.compare(""))
			break;

		size_t pos = line.find(",");
		pointsList.push_back({std::stoi(line.substr(0, pos)), std::stoi(line.substr(pos + 1))});
	}

	// read in the folding instructions and fold accordingly (all lines after the blank line)
	int foldCount = 0;
	for (std::string line; std::getline(inFile, line);)
	{
		// parse which axis and coordinate to fold on
		std::string foldLine = line.substr(11);
		size_t pos = foldLine.find("=");
		std::string axis = foldLine.substr(0, pos);
		int coordinate = std::stoi(foldLine.substr(pos + 1));

		// track the points after this iteration of folding so we can easily omit duplicates
		std::vector<std::array<int, 2>> newPoints;
		// which axis are we folding on?
		if (!axis.compare("y"))
		{
			// iterate all points in the list
			for (int i = 0; i < pointsList.size(); i++)
				// if this point's y coordinate is after the fold line
				if (pointsList[i][1] > coordinate)
					// fold the y coordinate and add it
					insertPoint(&newPoints, {pointsList[i][0], pointsList[i][1] - ((pointsList[i][1] - coordinate) * 2)});
				else
					// otherwise do nothing and insert the point normally
					insertPoint(&newPoints, pointsList[i]);
		}
		else
		{
			// same as for y axis, just flipped to x axis
			for (int i = 0; i < pointsList.size(); i++)
				if (pointsList[i][0] > coordinate)
					insertPoint(&newPoints, {pointsList[i][0] - ((pointsList[i][0] - coordinate) * 2), pointsList[i][1]});
				else
					insertPoint(&newPoints, pointsList[i]);
		}

		pointsList = newPoints;
		foldCount++;
		std::cout << "Fold " << foldCount << ": " << pointsList.size() << " points left" << std::endl;
	}

	// finally, print the grid of points after the folding so we can read the letters
	printPointsList(pointsList);
}
