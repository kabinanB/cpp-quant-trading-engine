#ifndef PORTFOLIO_H
#define PORTFOLIO_H

#include <string>
#include <map>

using namespace std;

struct Position {
    string ticker;
    int quantity;
    double entryOptionPrice;
};

class PortfolioManager {
public:
    void openPosition(const string& ticker, int qty, double currentBSPrice);
    double getUnrealizedPnL(const string& ticker, double currentBSPrice) const;
    bool hasPosition(const string& ticker) const;

private:
    map<string, Position> holdings;
};

#endif
