#include <vector>
#include <iostream>
#include "TestsRunner.h"
#include "OutputProcessor.h"
#include <filesystem>

double* OShift, * M, * y, * z, * x_bound;
int ini_flag = 0, n_flag, func_flag, * SS;

void main()
{
	/*int seedsNumber = 10;
	std::vector<int> seeds;
	for(int i = 1;i <= seedsNumber;i++)
		seeds.push_back(i);
	std::vector<int> dimensions = { 20};
	
	TestsRunner::Run(seeds, dimensions);*/
	std::cout << std::filesystem::current_path();
	OutputProcessor op;
	/*std::map<int, std::vector<double>> a1;
	std::map<int, std::vector<double>> a2;
	std::map<int, std::vector<double>> a3;
	op.GetDimData(a1, a2, a3, 10); */
	op.Parse10Dim(".\\parsed_data");
}