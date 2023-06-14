#include <vector>
#include <iostream>
#include "TestsRunner.h"
#include "OutputProcessor.h"
#include <filesystem>

double* OShift, * M, * y, * z, * x_bound;
int ini_flag = 0, n_flag, func_flag, * SS;

int main()
{
	/*int seedsNumber = 10;
	std::vector<int> seeds;
	for(int i = 1;i <= seedsNumber;i++)
		seeds.push_back(i);
	std::vector<int> dimensions = { 10, 30};

	TestsRunner testsRunner;
	testsRunner.Run(seeds, dimensions);*/

	OutputProcessor op;
	op.ProcessAll("./parsed_data");
	
}