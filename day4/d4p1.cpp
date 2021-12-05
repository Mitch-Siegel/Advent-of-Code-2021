/*
 * Mitch Siegel
 * Advent of Code 2021
 * Day 4: Part 1
 * https://adventofcode.com/2021/day/3
 *
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

class BingoBoard
{
public:
	std::vector<std::vector<int>> board;
	BingoBoard()
	{
		for (int i = 0; i < 25; i++)
		{
			this->board.push_back(std::vector<int>(2, 0));
		}
	}

	int move(int number)
	{
		// iterate over all squares on the board
		for (int i = 0; i < this->board.size(); i++)
		{
			// if we find the number called, mark it
			if (this->board[i][0] == number)
				this->board[i][1] = 1;
		}
		return this->calculateScore();
	}

	int calculateScore()
	{
		for (int i = 0; i < 5; i++)
		{
			int hWin = 1;
			int vWin = 1;
			for (int j = 0; j < 5; j++)
			{
				// scan along the row at index i
				hWin &= this->board[(5 * i) + j][1];
				// scan along the col at index i
				vWin &= this->board[i + (5 * j)][1];
			}
			// if we find a win, figure out the sum of unmarked squares
			if (hWin || vWin)
				return sumUnmarked();
		}
		// if we don't find a win, return 0
		return 0;
	}

	int sumUnmarked()
	{
		int sum = 0;
		// iterate all squares on the board
		for (std::vector<int> thisSpace : this->board)
		{
			// add spaces which are unmarked
			if (!thisSpace[1])
				sum += thisSpace[0];
		}
		this->printBoard();
		std::cout << "Sum of unmarked squares on this board is: " << sum << std::endl;
		return sum;
	}

	void printBoard()
	{
		for (int i = 0; i < 25; i++)
		{
			// add line breaks every 5 squares
			if (i % 5 == 0)
				std::cout << std::endl;

			// print out each square, bracked if called
			if (this->board[i][1])
			{
				printf("[%2d]", this->board[i][0]);
			}
			else
			{
				printf(" %2d ", this->board[i][0]);
			}
		}
		std::cout << std::endl;
	}
};

int main()
{
	// setup
	std::ifstream inFile;
	inFile.open("./input", std::ifstream::in);
	// read in the first line containing the numbers to be drawy
	std::string line;
	std::getline(inFile, line);

	std::vector<int> numbersDrawn;
	// tokenize and parse the numbers from the line
	size_t pos = 0;
	while ((pos = line.find(',')) != std::string::npos)
	{
		numbersDrawn.push_back(std::stoi(line.substr(0, pos)));
		line.erase(0, pos + 1);
	}
	// be sure to catch the last number
	numbersDrawn.push_back(std::stoi(line.substr(0, pos)));

	int numRead = 0;
	std::vector<BingoBoard> boardsList;
	BingoBoard boardInProgress;

	// read until EOF
	for (line; std::getline(inFile, line);)
	{
		// ignore empty lines
		if (!line.compare(""))
		{
			continue;
		}
		// if we just finished parsing in a board
		// add it to the list and instantiate a new one to work on
		if (numRead % 25 == 0)
		{
			if (numRead > 0)
			{
				boardsList.push_back(boardInProgress);
				boardInProgress = BingoBoard();
			}
		}

		// parse the values contained within each line
		std::vector<int> thisLine;
		std::istringstream iss(line);
		// strip spaces and parse ints
		for (std::string s; iss >> s;)
			thisLine.push_back(std::stoi(s));

		// populate the 5 board slots
		boardInProgress.board[numRead % 25][0] = thisLine[0];
		boardInProgress.board[(numRead % 25) + 1][0] = thisLine[1];
		boardInProgress.board[(numRead % 25) + 2][0] = thisLine[2];
		boardInProgress.board[(numRead % 25) + 3][0] = thisLine[3];
		boardInProgress.board[(numRead % 25) + 4][0] = thisLine[4];
		numRead += 5;
	}
	// don't miss the last board which finished at the termination of the loop
	boardsList.push_back(boardInProgress);

	for (int theMove : numbersDrawn)
	{
		std::cout << "Calling " << theMove << std::endl;
		for (int i = 0; i < boardsList.size(); i++)
		{
			// execute the move on each board
			int result = boardsList[i].move(theMove);
			if (result) // catch the first one to win, print its score, and exit
			{
				std::cout << "Final score is: " << (result * theMove) << std::endl;
				exit(0);
			}
		}
	}
}
