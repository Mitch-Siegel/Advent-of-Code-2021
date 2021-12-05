/*
 * Mitch Siegel
 * Advent of Code 2021
 * Day 3: Part 1
 * https://adventofcode.com/2021/day/3
 *
 */

#include <iostream>
#include <fstream>

// converts a c style array of 12 binary digits to the corresponding integer
int b12tod (int* array) {
	int decimalValue = 0;
	for (int i = 0; i < 12; i++){
		decimalValue += (array[i] << (11 - i));
	}
	return decimalValue;
}


int main()
{
	// setup
	std::ifstream inFile;
	inFile.open("./input", std::ifstream::in);
	int bits[12] = {0};
	int gammaBits[12];
	int epsilonBits[12];
	int lineCount = 0;
	int gammaRate, epsilonRate;

	// read all inputs and count the occurrences of 1's in each index
	for (std::string line; std::getline(inFile, line);)
	{
		for (int i = 0; i < 12; i++) {
			bits[i] += (line[i] == '1');
		}
		lineCount++;	
	}
	
	std::cout << "Proportion of 1's by index: ";
	for (int i = 0; i < 12; i++){
		std::cout << (float)bits[i]/lineCount << " ";
	}
	std::cout << std::endl;
	
	// populate the gamma and epsilon bits based on the occurrence rate of 1's in each digit
	for (int i = 0; i < 12; i++){
		gammaBits[i] = ((float)bits[i]/lineCount >= 0.5);
		epsilonBits[i] = ((float)bits[i]/lineCount < 0.5);
	}

	// convert and print the rates as well as the total power consumption
	gammaRate = b12tod(gammaBits);
	epsilonRate = b12tod(epsilonBits);

	std::cout << "Gamma rate: ";
	for (int i = 0; i < 12; i++){
		std::cout << gammaBits[i];
	}
	std::cout << " = " << gammaRate << std::endl << "Epsilon rate: ";
	for (int i = 0; i < 12; i++){
		std::cout << epsilonBits[i];
	}
	std::cout << " = " << epsilonRate << std::endl << "Total power consumption: " << gammaRate * epsilonRate << std::endl;
}
