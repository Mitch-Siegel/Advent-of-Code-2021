/*
 * Mitch Siegel
 * Advent of Code 2021
 * Day 15: Parts 1 and 2
 * https://adventofcode.com/2021/day/15
 *
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <queue>
#include <unordered_map>
#include <math.h>

std::vector<std::pair<int, int>> deltas = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

// keep track of the size of the grid so we can easily calculate the heuristic
int gridMax;

// simple x, y point with equality operator
struct Point
{
	int x, y;
	bool operator==(const Point &other) const
	{
		return (other.x == this->x && other.y == this->y);
	}
};

// class for a node representing a path, with a current position and a total risk
class PathNode
{
public:
	Point pos;
	int totalRisk;
	PathNode(std::pair<int, int> coordinates, int totalRisk)
	{
		pos.y = coordinates.first;
		pos.x = coordinates.second;
		totalRisk = totalRisk;
	}
	void setPos(Point newPos)
	{
		pos.y = newPos.y;
		pos.x = newPos.x;
	}
};

// compare function for PathNode
struct ComparePathNode
{
	bool operator()(const PathNode &a, const PathNode &b) const
	{
		return a.totalRisk > b.totalRisk;
	}
};

// hash function for Point
namespace std
{
	template <>
	struct hash<Point>
	{
		long int operator()(const Point &point)
			const
		{
			long int y = std::hash<int>()(point.y);
			long int x = std::hash<int>()(point.x) << 1;
			return x ^ y;
		}
	};
}

int findPath(std::vector<std::vector<int>> riskMap)
{
	// map coordinate pairs to the lowest possible cost to move there
	std::unordered_map<Point, int> pointCosts;

	// keep track of a minheap of paths in progress, sorted by total cost
	std::priority_queue<PathNode, std::vector<PathNode>, ComparePathNode> openList;

	// start at the origin
	openList.push(PathNode({0, 0}, 0));
	// there is no cost for 0,0 to start since it isn't entered at the start
	pointCosts[{0, 0}] = 0;
	// max cost of solution so we can reduce as we find cheaper and cheaper paths
	pointCosts[{gridMax - 1, gridMax - 1}] = INT32_MAX;

	// look at all possible paths
	while (!openList.empty())
	{
		// pick the most promising path (lowest cost so far)
		PathNode p = openList.top();
		openList.pop();

		// if we have made it to the goal, return the cost
		// because if goal is the min in the minheap, this is the lowest cost path to the end
		if (p.pos.y == riskMap.size() - 1 && p.pos.x == riskMap.size() - 1)
			return p.totalRisk;

		// look at all possible directions to move from current coordinate
		for (int i = 0; i < 4; i++)
		{
			Point newPos = p.pos;
			newPos.y += deltas[i].first;
			newPos.x += deltas[i].second;
			if (newPos.y >= 0 && newPos.y < riskMap.size() && newPos.x >= 0 && newPos.x < riskMap.size())
			{
				int newRisk = pointCosts[p.pos] + riskMap[newPos.y][newPos.x];

				// if this path to this point would reduce the total risk to get here (or this point is previously unseen)
				if (pointCosts.find(newPos) == pointCosts.end() || newRisk < pointCosts[newPos])
				{
					// add a the new point to the frontier
					PathNode newP(p);
					newP.setPos(newPos);
					newP.totalRisk = newRisk;
					openList.push(newP);

					// and track the new lowest possible total risk to get to this destination in the cost map
					pointCosts[newP.pos] = newP.totalRisk;
				}
			}
		}
	}
	// not possible
	return -1;
}

int main()
{
	// setup
	std::ifstream inFile;
	inFile.open("./input", std::ifstream::in);

	std::vector<std::vector<int>> riskLevels;

	// read in the risk levels to an array of ints
	for (std::string line; std::getline(inFile, line);)
	{
		std::vector<int> riskLine;
		for (char c : line)
			riskLine.push_back((int)c - 48);

		riskLevels.push_back(riskLine);
	}

	gridMax = riskLevels.size();

	// calculate and print the answer for part 1
	std::cout << "Part 1 lowest possible risk: " << findPath(riskLevels) << std::endl;

	// generate and populate the 5x as large grid for part 2
	std::vector<std::vector<int>> fullRiskLevels;
	for (int y = 0; y < 5; y++)
	{
		for (std::vector<int> row : riskLevels)
		{
			std::vector<int> fullRiskRow;
			for (int x = 0; x < 5; x++)
			{
				for (int i = 0; i < row.size(); i++)
				{
					int theNum = row[i];
					theNum += (x + y);

					// enforce the range constraint of anything over 9 wrapping to 1
					while (theNum > 9)
						theNum -= 9;

					fullRiskRow.push_back(theNum);
				}
			}
			fullRiskLevels.push_back(fullRiskRow);
		}
	}
	gridMax = fullRiskLevels.size();

	// calculate and print the answer for part 2
	std::cout << "Part 2 lowest possible risk: " << findPath(fullRiskLevels) << std::endl;
}
