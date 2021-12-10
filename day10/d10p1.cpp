/*
 * Mitch Siegel
 * Advent of Code 2021
 * Day 10: Part 1
 * https://adventofcode.com/2021/day/10
 *
 */

#include <iostream>
#include <fstream>
#include <vector>

// determine the score of a line based on opening and cosing pairs of characters
int scoreLine(std::string input)
{
	std::vector<char> parseStack;
	// iiterate over the input char by char
	for (char c : input)
	{
		switch (c)
		{
		// if the char opens a pair, push it to the stack
		case '(':
		case '[':
		case '{':
		case '<':
			parseStack.push_back(c);
			break;

		// if the char closes a pair correctly, pop the opener from the stack and move on
		// otherwise, we have a corrupted line, return the score corresponding to the broken char
		case ')':
			if (parseStack[parseStack.size() - 1] != '(')
				return 3;
			else
				parseStack.pop_back();

			break;

		case ']':
			if (parseStack[parseStack.size() - 1] != '[')
				return 57;
			else
				parseStack.pop_back();

			break;

		case '}':
			if (parseStack[parseStack.size() - 1] != '{')
				return 1197;
			else
				parseStack.pop_back();

			break;

		case '>':
			if (parseStack[parseStack.size() - 1] != '<')
				return 25137;
			else
				parseStack.pop_back();

			break;
		}
	}

	// if we made it through all characters in the line without breaking, the score is 0
	return 0;
}

int main()
{
	// setup
	std::ifstream inFile;
	inFile.open("./input", std::ifstream::in);

	int score;
	// iterate all lines and sum up the score
	for (std::string line; std::getline(inFile, line);)
		score += scoreLine(line);

	std::cout << score << std::endl;
}
