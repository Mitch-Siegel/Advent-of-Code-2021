/*
 * Mitch Siegel
 * Advent of Code 2021
 * Day 5: Part 1
 * https://adventofcode.com/2021/day/5
 *
 */

#include <iostream>
#include <fstream>
#include <vector>

// a simple class for a point
// this enables keeping track of "points of interest"
// without needing to scan the entire grid for relevant parameters
class Point
{
public:
	int x, y;
	int *count;
	// point has explicit coordinates and a pointer the the count in the larger grid data structure
	// grid structure can be updated and all points' counts will follow
	Point(int newX, int newY, int *countP)
	{
		this->x = newX;
		this->y = newY;
		this->count = countP;
	}
};

int main()
{
	// setup
	std::ifstream inFile;
	inFile.open("./input", std::ifstream::in);
	std::vector<std::vector<int>> coordinateGrid;

	// instantiate a 1000x1000 grid of ints to count the lines
	for (int i = 0; i < 1000; i++)
		coordinateGrid.push_back(std::vector<int>(1000));

	// vector of points we are interested in
	std::vector<Point> pointsOfInterest;

	for (std::string line; std::getline(inFile, line);)
	{
		// parse the 2 sets of coordinates into ints
		size_t pos = line.find(" -> ");
		std::string c1 = line.substr(0, pos);
		std::string c2 = line.substr(pos + 4);
		pos = c1.find(',');
		int x1 = std::stoi(c1.substr(0, pos));
		int y1 = std::stoi(c1.substr(pos + 1));
		pos = c2.find(',');
		int x2 = std::stoi(c2.substr(0, pos));
		int y2 = std::stoi(c2.substr(pos + 1));

		// figure out whether we have a horizontal/vertical/diagonal line
		int xDiff = x1 - x2;
		int yDiff = y1 - y2;
		// if we have a diagonal line, ignore it
		if (xDiff && yDiff)
			continue;
		else if (xDiff) // horizontal line
		{
			// set up iterator driver variables so we can always iterate from smaller to larger x values
			int xDriver, xMax;
			if (x1 < x2)
			{
				// start iterating from the first point
				xDriver = x1;
				xMax = x2;
			}
			else
			{
				// start iterating from the second point
				xDriver = x2;
				xMax = x1;
			}

			for (xDriver; xDriver <= xMax; xDriver++)
			{
				// if the count of this point is exactly 1, we will need to be interested in it from now on
				if (coordinateGrid[xDriver][y1] == 1)
					// add it to a specific list of points of interest
					pointsOfInterest.push_back(Point(xDriver, y1, &coordinateGrid[xDriver][y1]));

				coordinateGrid[xDriver][y1]++;
			}
		}
		else if (yDiff)
		{
			// same as above but with y values driving the iteration
			int yDriver, yMax;
			if (y1 < y2)
			{
				yDriver = y1;
				yMax = y2;
			}
			else
			{
				yDriver = y2;
				yMax = y1;
			}

			for (yDriver; yDriver <= yMax; yDriver++)
			{
				if (coordinateGrid[x1][yDriver] == 1)
					pointsOfInterest.push_back(Point(x1, yDriver, &coordinateGrid[x1][yDriver]));

				coordinateGrid[x1][yDriver]++;
			}
		}
	}

	std::cout << "There are " << pointsOfInterest.size() << " points with count > 1" << std::endl;
}
