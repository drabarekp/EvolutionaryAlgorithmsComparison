#pragma once
#include <vector>
#include "DifferentialEvolutionAlgorithm.h"

class TestsRunner {
private:
	const std::string PATH = "./data/";
public:
	void Run(std::vector<int> seeds, std::vector<int> dimensions);
	void RunAlgorithmTest(DifferentalEvolutionAlgorithm*, std::vector<int> seeds, std::vector<int> dimensions, std::vector<double> recordValues);
	void PrintResults(std::vector<std::vector<double>> results, int fun, int dim, std::string algorithmName);
};