#include "analytics.h"

using namespace std;

void MarketAnalytics::addTick(const MarketTick& t) {
    totalVolumes[t.stock] += t.volume;
    totalValue[t.stock] += (t.price * t.volume);
}

double MarketAnalytics::getVWAP(const string& ticker) const {
    auto volIt = totalVolumes.find(ticker);
    if (volIt == totalVolumes.end() || volIt->second == 0) return 0.0;
    
    auto valIt = totalValue.find(ticker);
    if (valIt == totalValue.end()) return 0.0;
    
    return valIt->second / volIt->second;
}
