#pragma once
#include "DifferentialEvolutionAlgorithm.h"
#include <vector>

class ModifiedDEAlgorithm : public DifferentalEvolutionAlgorithm {
protected:
	const double RELAXATION_FACTOR = 0.3;
	const double DAMPING_FACTOR = 1.0;

public:
	std::vector<double> FindMinimum(std::function<double(std::vector<double>)> f, int n) override;

protected:
	std::vector<double> Mutate(const std::vector<double>& P_j, const std::vector<double>& P_k, const std::vector<double>& P_l, double F);
	virtual double TuneMutationScope(double F, double& success, const std::vector<double>& population, std::vector<double>& prevPopulation) = 0;

};