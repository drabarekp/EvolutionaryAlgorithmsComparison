#include "MedianSuccessRuleDEAlgorithm.h"
#include <algorithm>

double MedianSuccessRuleDEAlgorithm::TuneMutationScope(double F, double& success, const std::vector<double>& population, std::vector<double>& prevPopulation)
{
	int populationSize = population.size();
	std::vector<double> sortedPrevPopulation = prevPopulation;
	std::sort(sortedPrevPopulation.begin(), sortedPrevPopulation.end());
	int choosedIndividual = INDIVIDUAL_QUANTILE * populationSize;

	double choosedIndividualValue = sortedPrevPopulation[choosedIndividual];

	int Ksuccess = 0;
	for (int i = 0;i < population.size();i++) {
		if (population[i] <= choosedIndividualValue)
			Ksuccess++;
	}

	double z = 2. * (Ksuccess - (populationSize + 1) / 2.) / populationSize;

	success = (1.0 - RELAXATION_FACTOR) * success + RELAXATION_FACTOR * z;
	
	return F * exp(success / DAMPING_FACTOR);
}
