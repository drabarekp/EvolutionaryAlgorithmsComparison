#include "ModifiedDEAlgorithm.h"
#include <algorithm>

std::vector<double> ModifiedDEAlgorithm::FindMinimum(std::function<double(std::vector<double>)> f, int n, const std::vector<double>& recordValues, std::vector<double>& recordsError, double bestValue)
{
	int populationSize = POPULATION_SIZE_COEFFICIENT * n;
	std::vector<std::vector<double>> population = InitializePopulation(populationSize, n);
	std::vector<double> result;
	double resultValue = std::numeric_limits<double>::infinity();

	std::vector<double> populationValues;

	for (int i = 0;i < populationSize;i++) {
		populationValues.push_back(f(population[i]));
	}

	double success = 0.0;
	double F = CROSSOVER_PROBABILITY;

	std::vector<double> prevPopulationValues = populationValues;

	int iterations = n * ITERATIONS_COEFFICIENT;
	int recordIndex = 0;

	int t = 0;
	while (t++ < iterations) {
		for (int i = 0;i < populationSize;i++) {
			std::vector<int> selectedIndividuals = SelectRandomIndividuals(populationSize, i);

			std::vector<double> P_i = population[i], P_j = population[selectedIndividuals[0]], P_k = population[selectedIndividuals[1]], P_l = population[selectedIndividuals[2]];

			std::vector<double> M = Mutate(P_j, P_k, P_l, F);

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

		if (t == recordValues[recordIndex] * iterations) {
			recordsError.push_back(CalculateError(resultValue, bestValue));

			if (recordsError[recordIndex] == 0) {
				for (int i = recordIndex + 1;i < recordValues.size();i++) {
					recordsError.push_back(0);
				}
				break;
			}
			recordIndex++;
		}

		F = TuneMutationScope(F, success, populationValues, prevPopulationValues);

		prevPopulationValues = populationValues;
	}

	return result;
}

std::vector<double> ModifiedDEAlgorithm::Mutate(const std::vector<double>& P_j, const std::vector<double>& P_k, const std::vector<double>& P_l, double F)
{
	std::vector<double> M;
	for (int i = 0;i < P_j.size();i++) {
		M.push_back(P_j[i] + F * (P_k[i] - P_l[i]));
	}

	return M;
}

