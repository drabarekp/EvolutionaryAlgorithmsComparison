
#include "DifferentialEvolutionAlgorithm.h"
#include <random>
#include<vector>

std::vector<double> DifferentalEvolutionAlgorithm::FindMinimum(std::function<double(std::vector<double>)> f, int n) {

	int populationSize = POPULATION_SIZE_COEFFICIENT * n;
	std::vector<std::vector<double>> population = InitializePopulation(populationSize, n);
	std::vector<double> populationValues;

	for (int i = 0;i < populationSize;i++) {
		populationValues.push_back(f(population[i]));
	}

	std::vector<double> result;
	double resultValue = std::numeric_limits<double>::infinity();

	int t = 0;
	while (t++ < ITERATIONS_NUMBER) {
		for (int i = 0;i < populationSize;i++) {
			std::vector<int> selectedIndividuals = SelectRandomIndividuals(populationSize, i);

			std::vector<double> P_i = population[i], P_j = population[selectedIndividuals[0]], P_k = population[selectedIndividuals[1]], P_l = population[selectedIndividuals[2]];
			
			std::vector<double> M = Mutate(P_j, P_k, P_l);

			std::vector<double> O = Crossover(P_i, M);

			double valueO = f(O);
			double valueP_i = populationValues[i];
			if (valueO < valueP_i) {
				population[i] = O;
				valueP_i = valueO;
				populationValues[i] = valueO;
			}

			if (valueP_i < resultValue) {
				result = population[i];
				resultValue = valueP_i;
			}
		}

	}

	return result;

}

std::vector<std::vector<double>> DifferentalEvolutionAlgorithm::InitializePopulation(int populationSize, int n)
{
	std::vector<std::vector<double>> population;
	std::uniform_real_distribution<double> uniformDistribution(RANGE_MIN, RANGE_MAX);
	std::random_device rd;
	std::mt19937 randomEngine(rd());

	for (int i = 0;i < populationSize;i++) {
		std::vector<double> individual;
		for (int j = 0;j < n;j++) {
			individual.push_back(uniformDistribution(randomEngine));
		}
		population.push_back(individual);
	}

	return population;
}

std::vector<int> DifferentalEvolutionAlgorithm::SelectRandomIndividuals(int populationSize, int currentIndividual)
{
	std::vector<int> selected;
	std::uniform_int_distribution<int> uniformDistribution(0, populationSize - 1);
	std::random_device rd;
	std::mt19937 randomEngine(rd());

	int randomIndividual;

	for (int i = 0;i < 3;i++) {
		do {
			randomIndividual = uniformDistribution(randomEngine);
		} while (randomIndividual == currentIndividual || (selected.size() > 0 && std::find(selected.begin(), selected.end(), randomIndividual) != selected.end()));
		
		selected.push_back(randomIndividual);
	}

	return selected;
}

std::vector<double> DifferentalEvolutionAlgorithm::Mutate(const std::vector<double>& P_j, const std::vector<double>& P_k, const std::vector<double>& P_l)
{
	std::vector<double> M;
	for (int i = 0;i < P_j.size();i++) {
		M.push_back(P_j[i] + DIFFERENTAL_WEIGHT * (P_k[i] - P_l[i]));
	}

	return M;
}

std::vector<double> DifferentalEvolutionAlgorithm::Crossover(const std::vector<double>& P_i, const std::vector<double>& M)
{
	std::vector<double> O;
	std::uniform_real_distribution<double> uniformDistribution(0, 1);
	std::random_device rd;
	std::mt19937 randomEngine(rd());

	for (int i = 0;i < P_i.size();i++) {
		double randValue = uniformDistribution(randomEngine);
		if (randValue < CROSSOVER_PROBABILITY) {
			O.push_back(M[i]);
		}
		else {
			O.push_back(P_i[i]);
		}
	}

	return O;
}

