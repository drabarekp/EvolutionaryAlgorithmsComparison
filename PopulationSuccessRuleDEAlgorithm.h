#pragma once

#pragma once
#include "ModifiedDEAlgorithm.h"
#include <vector>

class PopulationSuccessRuleDEAlgorithm : public ModifiedDEAlgorithm {
protected:
	const double TARGET_SUCCESS = 0.35;

protected:
	double TuneMutationScope(double F, double& success, const std::vector<double>& population, std::vector<double>& prevPopulation) override;

};