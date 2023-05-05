#pragma once
#include <vector>

void cec17_test_func(double*, double*, int, int, int);

static class CEC17Wrapper {
public:
	static double GetFunctionValue(std::vector<double> x, int functionNumber);

};