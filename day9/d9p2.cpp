/*
 * Mitch Siegel
 * Advent of Code 2021
 * Day 9: Part 2
 * https://adventofcode.com/2021/day/9
 *
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <ncurses.h>
// must be compiled with '-lncurses' !

// this class will help us to pass around info about what has been seen
// and where to look next
class Point
{
public:
	int x, y;
	Point(int newY, int newX)
	{
		this->x = newX;
		this->y = newY;
	}
};

// helper function to read the map at a given point
int readHeightmap(std::vector<std::vector<int>> *map, Point p)
{
	return (*map)[p.y][p.x];
}

// return 1 if a vector of points contains a given point
int pointListContains(std::vector<Point> *list, Point p)
{
	for (Point check : *list)
		if (check.x == p.x && check.y == p.y)
			return 1;

	return 0;
}

int findBasinSize(Point startPoint, std::vector<Point> *seenList, std::vector<std::vector<int>> *map)
{
	// spin for a bit for the animation
	for (int i = 0; i < 0x1fffff; i++)
	{
	}
	int totalSize = 0;
	// we have seen the point we are looking at
	(*seenList).push_back(startPoint);
	// color in this space
	move(startPoint.y, startPoint.x);
	addch(readHeightmap(map, startPoint) + 48);
	attron(COLOR_PAIR(2));
	refresh();

	// 1 if block for each possible neighboring cell
	// check whether the cell has been seen already
	// if not and it is higher than the current cell and not 9
	// increment the size count and recurse to the neighbor
	if (startPoint.y > 0)
	{
		Point next = Point(startPoint.y - 1, startPoint.x);
		if (!pointListContains(seenList, next))
			if ((readHeightmap(map, next) > readHeightmap(map, startPoint)) && readHeightmap(map, next) != 9)
				++totalSize += findBasinSize(next, seenList, map);
	}

	if (startPoint.y < (*map).size() - 1)
	{
		Point next = Point(startPoint.y + 1, startPoint.x);
		if (!pointListContains(seenList, next))
			if ((readHeightmap(map, next) > readHeightmap(map, startPoint)) && readHeightmap(map, next) != 9)
				++totalSize += findBasinSize(next, seenList, map);
	}

	if (startPoint.x > 0)
	{
		Point next = Point(startPoint.y, startPoint.x - 1);
		if (!pointListContains(seenList, next))
			if ((readHeightmap(map, next) > readHeightmap(map, startPoint)) && readHeightmap(map, next) != 9)
				++totalSize += findBasinSize(next, seenList, map);
		
	}

	if (startPoint.x < (*map)[0].size() - 1)
	{
		Point next = Point(startPoint.y, startPoint.x + 1);
		if (!pointListContains(seenList, next))
			if ((readHeightmap(map, next) > readHeightmap(map, startPoint)) && readHeightmap(map, next) != 9)
				++totalSize += findBasinSize(next, seenList, map);
	}
	
	return totalSize;
}

int main()
{
	// setup
	initscr();
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(2, COLOR_WHITE, COLOR_GREEN);
	init_pair(3, COLOR_WHITE, COLOR_RED);

	std::ifstream inFile;
	inFile.open("./input", std::ifstream::in);

	std::vector<std::vector<int>> map;
	// read in the map
	for (std::string line; std::getline(inFile, line);)
	{
		std::vector<int> thisLine;
		for (char c : line)
		{
			thisLine.push_back(c - 48);
		}
		map.push_back(thisLine);
	}

	// print out the map
	attron(COLOR_PAIR(1));
	for (int y = 0; y < map.size(); y++)
	{
		move(y, 0);
		for (int x = 0; x < map[0].size(); x++)
			addch(map[y][x] + 48);
	}

	std::vector<int> basinSizes;
	for (int y = 0; y < map.size(); y++)
	{
		for (int x = 0; x < map[0].size(); x++)
		{
			int examinedCell = map[y][x];
			// same logic as part 1
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
				// call the basin finder, push back the size of the found basin to the list
				std::vector<Point> *seenList = new std::vector<Point>();
				// set the color to red so all low points will show up in red
				attron(COLOR_PAIR(3));
				basinSizes.push_back(findBasinSize(Point(y, x), seenList, &map) + 1);
				delete seenList;
			}
		}
	}

	getch();
	clear();

	// sort the basins by size, multiply the top 3
	std::sort(basinSizes.begin(), basinSizes.end());
	int finalResult = 1;
	for (int i = 0; i < 3; i++)
		finalResult *= basinSizes[basinSizes.size() - i - 1];
	
	attron(COLOR_PAIR(1));
	// print the actual result here
	printw("%d\n", finalResult);
	refresh();
	getch();
}
