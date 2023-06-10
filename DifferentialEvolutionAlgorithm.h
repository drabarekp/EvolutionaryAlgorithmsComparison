#pragma once
#include <vector>
#define _CRT_SECURE_NO_WARNINGS

#include <WINDOWS.H>    
#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <functional>
#include <random>

class DifferentalEvolutionAlgorithm {
protected:
	const int POPULATION_SIZE_COEFFICIENT = 10;
	const double CROSSOVER_PROBABILITY = 0.9;
	const double DIFFERENTAL_WEIGHT = 0.8;
	const double RANGE_MIN = -100.0;
	const double RANGE_MAX = 100.0;
	const int ITERATIONS_COEFFICIENT = 1000;
	const double PRECISION = 0.00000001;

	std::mt19937 randomEngine;

public:
	virtual std::vector<double> FindMinimum(std::function<double(std::vector<double>)> f, int n, const std::vector<double>& recordValues, std::vector<double>& recordsError, double bestValue);
	DifferentalEvolutionAlgorithm(int seed);
	virtual std::string GetName();
	void Reset(int seed);

protected:
	std::vector<std::vector<double>> InitializePopulation(int populationSize, int n);
	std::vector<int> SelectRandomIndividuals(int populationSize, int currentIndividual);
	std::vector<double> Mutate(const std::vector<double>& P_j, const std::vector<double>& P_k, const std::vector<double>& P_l);
	std::vector<double> Crossover(const std::vector<double>& P_i, const std::vector<double>& M);
	double CalculateError(double actualValue, double bestValue);
};

