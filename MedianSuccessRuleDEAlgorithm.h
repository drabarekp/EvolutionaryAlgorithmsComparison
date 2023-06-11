#pragma once
#include "ModifiedDEAlgorithm.h"
#include <vector>

class MedianSuccessRuleDEAlgorithm : public ModifiedDEAlgorithm {

protected:
	const double INDIVIDUAL_QUANTILE = 0.4;

public:
	MedianSuccessRuleDEAlgorithm(int seed):ModifiedDEAlgorithm(seed) {}
	std::string GetName() override;

protected:
	double TuneMutationScope(double F, double& success, const std::vector<double>& population, std::vector<double>& prevPopulation) override;


};
