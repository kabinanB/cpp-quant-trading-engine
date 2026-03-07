#pragma once
#include "EuropeanOption.h"
class EuropeanCall: public EuropeanOption
{
public:
	EuropeanCall(double K, double T) : EuropeanOption(K, T) {}
	double priceByAnalytical(double S, double sigma, double r) const override;
	Greeks greeks(double S, double sigma, double r) const override;
};

