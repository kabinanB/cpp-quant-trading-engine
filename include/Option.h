#pragma once

class TradeData
{
public:
	TradeData(double K, double T) : K(K), T(T) {}
protected:
	double K;
	double T;

};

class Option : public TradeData
{
public:
	Option(double K, double T) : TradeData(K, T) {}
};



