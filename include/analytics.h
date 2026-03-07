#ifndef ANALYTICS_HPP
#define ANALYTICS_HPP

#include <string>
#include <map>

using namespace std;

struct MarketTick {
    string stock;
    double price;
    int volume;
};

class MarketAnalytics {
public:
    void addTick(const MarketTick& t);
    double getVWAP(const string& ticker) const;

private:
    map<string, int> totalVolumes;
    map<string, double> totalValue;
};

#endif
