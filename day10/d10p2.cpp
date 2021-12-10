/*
 * Mitch Siegel
 * Advent of Code 2021
 * Day 10: Part 2
 * https://adventofcode.com/2021/day/10
 *
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

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

// calculate the score of completing a line
long int completeLine(std::string input)
{
	long int lineScore = 0;
	std::vector<char> parseStack;

	// read in all the tokens we know of, manipulating the stack appropriately
	for (char c : input)
	{
		switch (c)
		{
		case '(':
		case '[':
		case '{':
		case '<':
			parseStack.push_back(c);
			break;
		case ')':
		case ']':
		case '}':
		case '>':
			parseStack.pop_back();
			break;
		}
	}

	// look at the remaining open pairs on the stack
	// add and multiply the score based on what we see on the top of the stack
	while (parseStack.size() > 0)
	{
		lineScore *= 5;
		switch (parseStack[parseStack.size() - 1])
		{
		case '(':
			lineScore += 1;
			break;
		case '[':
			lineScore += 2;
			break;
		case '{':
			lineScore += 3;
			break;
		case '<':
			lineScore += 4;
			break;
		}

		parseStack.pop_back();
	}

	return lineScore;
}

int main()
{
	// setup
	std::ifstream inFile;
	inFile.open("./input", std::ifstream::in);

	std::vector<std::string> incompleteLines;
	// the numbers get quite large with all that multiplication
	std::vector<long int> scores;

	// iterate all lines, if it is valid add its score to the list
	for (std::string line; std::getline(inFile, line);)
		if (!scoreLine(line))
			scores.push_back(completeLine(line));

	// sort the scores and find the middle
	std::sort(scores.begin(), scores.end());

	// integer division makes this easy because we know the number of scores will always be odd
	std::cout << scores[scores.size() / 2] << std::endl;
}
