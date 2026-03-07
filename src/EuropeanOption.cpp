#include "EuropeanOption.h"
#include <cmath>

double EuropeanOption::d1(double S, double sigma, double r) const
{
	double num = log(S / K) + (r + 0.5 * sigma * sigma) * T;
	double denom = sigma * sqrt(T);

	return num / denom;
}
