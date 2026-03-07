#include "EuropeanCall.h"
#include "helper.h"



double EuropeanCall::priceByAnalytical(double S, double sigma, double r) const  
{
	double d1_ = d1(S, sigma, r);
	double d2 = d1_ - sigma * sqrt(T);

	double T1 = S * normalCDF(d1_);
	double T2 = K * exp(-r * T) * normalCDF(d2);

	return T1 - T2;


}

Greeks EuropeanCall::greeks(double S, double sigma, double r) const
{
	double d1_ = d1(S, sigma, r);
	double d2 = d1_ - sigma * sqrt(T);

	double S_sqrt_T = S * sqrt(T);
	double discount_factor = exp(-r * T);

	
	double pdf = exp(-0.5 * d1_ * d1_) / sqrt(2 * M_PI);
	double theta_T1 = sigma * S * pdf / (2 * sqrt(T));
	double theta_T2 = r * K * discount_factor * normalCDF(d2);

	Greeks g;
	g.delta = normalCDF(d1_);
	g.gamma = pdf / (sigma * S_sqrt_T);
	g.rho = K * T * discount_factor * normalCDF(d2);
	g.vega = S_sqrt_T * pdf;
	g.theta = -theta_T1 - theta_T2;

	return g;
}
