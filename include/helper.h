#pragma once
#include <cmath>

/**
* Resource: 
* https://stackoverflow.com/questions/2328258/cumulative-normal-distribution-function-in-c-c
**/
inline double normalCDF(double value)
{
	return 0.5 * erfc(-value / sqrt(2.0));
}

#ifndef M_PI
const double M_PI = 3.141592653589;
#endif
