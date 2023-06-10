#include <vector>
#include <iostream>
#include "TestsRunner.h"

double* OShift, * M, * y, * z, * x_bound;
int ini_flag = 0, n_flag, func_flag, * SS;

void main()
{
	int seedsNumber = 10;
	std::vector<int> seeds;
	for(int i = 1;i <= seedsNumber;i++)
		seeds.push_back(i);
	std::vector<int> dimensions = { 20};

	TestsRunner::Run(seeds, dimensions);
}