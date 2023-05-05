#include "CEC17Wrapper.h"

double CEC17Wrapper::GetFunctionValue(std::vector<double> x, int functionNumber)
{
    double result;
    cec17_test_func(&x[0], &result, x.size(), 1, functionNumber);
    
    return result;
}
