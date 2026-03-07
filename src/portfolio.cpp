#include "portfolio.h"
#include <string>

using namespace std;

void PortfolioManager::openPosition(const string& ticker, int qty, double currentBSPrice) {
    if (holdings.find(ticker) == holdings.end()) {
        holdings[ticker] = {ticker, qty, currentBSPrice};
    }
}

double PortfolioManager::getUnrealizedPnL(const string& ticker, double currentBSPrice) const {
    auto it = holdings.find(ticker);
    if (it == holdings.end()) return 0.0;
    
    const Position& pos = it->second;
    double priceChange = currentBSPrice - pos.entryOptionPrice;
    return priceChange * pos.quantity;
}

bool PortfolioManager::hasPosition(const string& ticker) const {
    return holdings.find(ticker) != holdings.end();
}
