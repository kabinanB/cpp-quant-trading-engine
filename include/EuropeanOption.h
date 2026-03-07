#pragma once
#include "Option.h"

struct Greeks
{
	double delta;
	double gamma;
	double theta;
	double vega;
	double rho;
};
class EuropeanOption: public Option
{
public:
	EuropeanOption(double K, double T) : Option(K, T) {}
	virtual double priceByAnalytical(double S, double sigma, double r) const = 0;
	virtual Greeks greeks(double S, double sigma, double r) const = 0;
protected:
	double d1(double S, double sigma, double r) const;

};

