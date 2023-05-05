#include "CEC17Wrapper.h"
#include "DifferentialEvolutionAlgorithm.h"
#include "MedianSuccessRuleDEAlgorithm.h"
#include "PopulationSuccessRuleDEAlgorithm.h"
#include <vector>
#include <iostream>

double* OShift, * M, * y, * z, * x_bound;
int ini_flag = 0, n_flag, func_flag, * SS;


void main()
{
	for (int i = 0;i < 30;i++)
	{
		if (i == 1)
			continue;
		std::cout << "Function " << i + 1 << " ";
		DifferentalEvolutionAlgorithm algorithm;
		std::vector<double> min = algorithm.FindMinimum([i](std::vector<double> x) { return CEC17Wrapper::GetFunctionValue(x, i+1);}, 10);
		std::cout<< "Basic - " << CEC17Wrapper::GetFunctionValue(min, i + 1) << " ";

		MedianSuccessRuleDEAlgorithm algorithm2;
		std::vector<double> min2 = algorithm2.FindMinimum([i](std::vector<double> x) { return CEC17Wrapper::GetFunctionValue(x, i+1);}, 10);
		std::cout << "MSR - " << CEC17Wrapper::GetFunctionValue(min2, i + 1) <<"  ";

		PopulationSuccessRuleDEAlgorithm algorithm3;
		std::vector<double> min3 = algorithm3.FindMinimum([i](std::vector<double> x) { return CEC17Wrapper::GetFunctionValue(x, i+1);}, 10);
		std::cout << "PSR - " << CEC17Wrapper::GetFunctionValue(min3, i + 1) <<std::endl;
	}
}