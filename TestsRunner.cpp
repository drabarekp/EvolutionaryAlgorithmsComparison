#include "CEC17Wrapper.h"
#include "TestsRunner.h"
#include "MedianSuccessRuleDEAlgorithm.h"
#include "PopulationSuccessRuleDEAlgorithm.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

const std::string TestsRunner::PATH = "C:\\Users\\agowo\\Desktop\\DifferentialEvolutionModifications\\data\\";

void TestsRunner::Run(std::vector<int> seeds, std::vector<int> dimensions) {
	std::vector<double> recordValues = { .01, .02, .03, .05, .1, .2, .3, .4, .5, .6, .7, .8, .9, 1 };

	DifferentalEvolutionAlgorithm* algorithm = new DifferentalEvolutionAlgorithm(0);
	MedianSuccessRuleDEAlgorithm* MSRalgorithm = new MedianSuccessRuleDEAlgorithm(0);
	PopulationSuccessRuleDEAlgorithm* PSRalgorithm = new PopulationSuccessRuleDEAlgorithm(0);

	TestsRunner::RunAlgorithmTest(algorithm, seeds, dimensions, recordValues);
	TestsRunner::RunAlgorithmTest(MSRalgorithm, seeds, dimensions, recordValues);
	TestsRunner::RunAlgorithmTest(PSRalgorithm, seeds, dimensions, recordValues);
}

void TestsRunner::RunAlgorithmTest(DifferentalEvolutionAlgorithm* algorithm, std::vector<int> seeds, std::vector<int> dimensions, std::vector<double> recordValues) {

	for (int dim = 0;dim < dimensions.size();dim++) {
		for (int fun = 1; fun <= 30;fun++) {
			if (fun == 2)
				continue;

			std::vector<std::vector<double>> resultList;
			for (int i = 0;i < seeds.size();i++) {
				std::vector<double> result;
				algorithm->Reset(seeds[i]);
				algorithm->FindMinimum([fun](std::vector<double> x) 
					{ 
						return CEC17Wrapper::GetFunctionValue(x, fun);
					}, 
					dimensions[dim], recordValues, result, 100 * fun);
				resultList.push_back(result);
			}

			PrintResults(resultList, fun, dimensions[dim], algorithm->GetName());
		}
	}
}

void TestsRunner::PrintResults(std::vector<std::vector<double>> results, int fun, int dim, std::string algorithmName) {
	std::ofstream file;
	std::string filename = PATH + algorithmName + "_" + std::to_string(fun) + "_" + std::to_string(dim) + ".txt";
	file.open(filename);
	for (int i = 0;i < results[0].size();i++) {
		for (int j = 0;j < results.size();j++) {
			file << results[j][i] << " ";
		}
		file<<std::endl;
	}
	file.close();
}