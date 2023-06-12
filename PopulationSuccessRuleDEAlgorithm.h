#pragma once

#pragma once
#include "ModifiedDEAlgorithm.h"
#include <vector>

class PopulationSuccessRuleDEAlgorithm : public ModifiedDEAlgorithm {
protected:
	const double TARGET_SUCCESS = 0.2;

public: 
	PopulationSuccessRuleDEAlgorithm(int seed): ModifiedDEAlgorithm(seed) {}
	std::string GetName() override;
protected:
	double TuneMutationScope(double F, double& success, const std::vector<double>& population, std::vector<double>& prevPopulation) override;

};