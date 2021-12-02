#include <iostream>
#include <fstream>

int main()
{
	// setup
	std::ifstream inFile;
	inFile.open("./input", std::ifstream::in);
	int thisDepth;
	int prevDepth = INT32_MAX;
	int deeperCount = 0;

	// iterate all lines in the input
	for (std::string line; std::getline(inFile, line);)
	{
		thisDepth = std::stoi(line);

		// increment count iff this line is deeper than the previous
		if (thisDepth > prevDepth)
			deeperCount++;

		prevDepth = thisDepth; // update previous depth
	}

	std::cout << deeperCount << std::endl;
}
