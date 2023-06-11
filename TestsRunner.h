#pragma once
#include <vector>
#include "DifferentialEvolutionAlgorithm.h"

class TestsRunner {
private:
	const static std::string PATH;
public:
	static void Run(std::vector<int> seeds, std::vector<int> dimensions);
	static void RunAlgorithmTest(DifferentalEvolutionAlgorithm*, std::vector<int> seeds, std::vector<int> dimensions, std::vector<double> recordValues);
	static void PrintResults(std::vector<std::vector<double>> results, int fun, int dim, std::string algorithmName);
};