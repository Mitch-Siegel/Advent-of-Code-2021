/*
 * Mitch Siegel
 * Advent of Code 2021
 * Day 3: Part 2
 * https://adventofcode.com/2021/day/3
 *
 */

#include <iostream>
#include <fstream>
#include <vector>

// converts a vector of 12 binary digits to the corresponding integer
int b12tod(std::vector<int> array)
{
	int decimalValue = 0;
	for (int i = 0; i < 12; i++)
	{
		decimalValue += (array[i] << (11 - i));
	}
	return decimalValue;
}

// given a set of binary vectors
// return an equally sized vector containing the proportion of 1's in each corresponding index
std::vector<double> calculateProportions(std::vector<std::vector<int>> inputSet)
{
	std::vector<double> retVector(inputSet[0].size(), 0);
	for (std::vector<int> v : inputSet)
	{
		for (int i = 0; i < v.size(); i++)
			retVector[i] += v[i];
	}
	for (int i = 0; i < retVector.size(); i++)
		retVector[i] /= inputSet.size();

	return retVector;
}

int main()
{
	// setup
	std::ifstream inFile;
	inFile.open("./input", std::ifstream::in);
	int bits[12] = {0};

	// read all inputs into a vector of vectors with one index for each digit
	std::vector<std::vector<int>> reportValues;
	for (std::string line; std::getline(inFile, line);)
	{
		std::vector<int> currentValue(12);
		for (int i = 0; i < 12; i++)
		{
			bits[i] += (line[i] == '1');
			currentValue[i] = (line[i] == '1');
		}
		reportValues.push_back(currentValue);
	}

	int CO2Rating;
	int O2Rating;

	std::vector<std::vector<int>> inputValues(reportValues);
	std::vector<std::vector<int>> outputValues(1000);
	std::vector<int> foundValue;
	for (int i = 0; i < 12; i++)
	{
		// recalculate the proportions of each digit for every set of input values
		std::vector<double> proportions = calculateProportions(inputValues);

		outputValues.clear();
		int acceptedVal = (proportions[i]) >= 0.5;
		for (std::vector<int> input : inputValues)
		{
			// check every input at the index currently being examined
			if (input[i] == acceptedVal)
				// if the value at that index is valid, add it to the output set
				outputValues.push_back(input);
		}
		// only 1 value left in the filter, so stop the search
		if (outputValues.size() == 1)
		{
			foundValue = outputValues[0];
			break;
		}
		else // more than 1 value left in the filter, set input values to the remaining boards and repeat
			inputValues = outputValues;
	}

	O2Rating = b12tod(foundValue);
	std::cout << "Oxygen generator rating is: " << O2Rating << std::endl;

	// same algorithm as above, different filter
	inputValues = reportValues;
	for (int i = 0; i < 12; i++)
	{
		std::vector<double> proportions = calculateProportions(inputValues);

		outputValues.clear();
		// altered filter to sort for the least popular value for each bit
		int acceptedVal = (proportions[i]) < 0.5;
		for (std::vector<int> input : inputValues)
		{
			if (input[i] == acceptedVal)
				outputValues.push_back(input);
		}
		if (outputValues.size() == 1)
		{
			foundValue = outputValues[0];
			break;
		}
		else
			inputValues = outputValues;
	}
	CO2Rating = b12tod(foundValue);
	std::cout << "CO2 scrubber rating is: " << CO2Rating << std::endl;
	std::cout << "Life support rating is: " << (O2Rating * CO2Rating) << std::endl;
}
