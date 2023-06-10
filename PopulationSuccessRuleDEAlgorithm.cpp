#include "PopulationSuccessRuleDEAlgorithm.h"
#include <algorithm>
#include <iostream>

double PopulationSuccessRuleDEAlgorithm::TuneMutationScope(double F, double& success, const std::vector<double>& population, std::vector<double>& prevPopulation)
{
    int populationSize = population.size();
    std::vector<std::pair<int, double>> fmix;

    for (int i = 0;i < populationSize;i++) {
        fmix.push_back(std::make_pair(0, population[i]));
        fmix.push_back(std::make_pair(1, prevPopulation[i]));
    }
    std::sort(fmix.begin(), fmix.end(), [](std::pair<int, double> p1, std::pair<int, double> p2) {return p1.second < p2.second;});

    std::vector<int> ranks;
    std::vector<int> prevRanks;

    for (int i = 0;i < populationSize * 2;i++) {

        if (fmix[i].first == 0) {
            ranks.push_back(i);
        }
        else {
            prevRanks.push_back(i);
        }
    }

    double ranksDiff = 0;
    for (int i = 0;i < populationSize;i++) {
        ranksDiff += prevRanks[i] - ranks[i];
    }

    double z = ranksDiff / (populationSize * populationSize) - TARGET_SUCCESS;

    success = (1.0 - RELAXATION_FACTOR) * success + RELAXATION_FACTOR * z;


    return F * exp(success / DAMPING_FACTOR);
}

std::string PopulationSuccessRuleDEAlgorithm::GetName()
{
	return "DE_rand_1_bin_PSR";
}