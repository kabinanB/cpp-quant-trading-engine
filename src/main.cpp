#include <iostream>
#include <iomanip>
#include <fstream>
#include <filesystem>
#include <stdexcept>
#include "EuropeanCall.h"
#include "EuropeanPut.h"

using namespace std;
namespace fs = std::filesystem;

static constexpr double OPTION_MULTIPLIER = 100.0;

int main(int argc, char* argv[]) {

    // Reset command 
    if (argc >= 2 && (string(argv[1]) == "reset" || string(argv[1]) == "clear")) {
        for (const auto& entry : fs::directory_iterator(".")) {
            const string name = entry.path().filename().string();
            if (name.size() > 13 &&
               (name.substr(name.size() - 13) == "_position.txt" ||
                name.substr(name.size() - 13) == "_analytics.txt")) {
                fs::remove(entry.path());
            }
        }
        cout << "All position and analytics files cleared!" << endl;
        return 0;
    }

    // Usage guard 
    if (argc < 5) {
        cout << "Usage: " << argv[0] << " [call|put] [ticker] [price] [contracts]" << endl;
        cout << "       Optional: [strike=150.0] [expiry=0.5] [vol=0.25] [rate=0.05]" << endl;
        cout << "Example: " << argv[0] << " call AAPL 154.5 10 150.0 0.5 0.25 0.05" << endl;
        cout << "Reset:   " << argv[0] << " reset" << endl;
        return 1;
    }

    // Parse arguments safely 
    string callOrPut = argv[1];
    string ticker    = argv[2];
    double price     = 0.0;
    int    contracts = 0;

    // Default model parameters
    double K     = 150.0;  // Strike
    double T     = 0.5;    // 6 months
    double sigma = 0.25;   // 25% volatility
    double r     = 0.05;   // 5% risk-free rate

    try {
        price     = stod(argv[3]);
        contracts = stoi(argv[4]);
        if (argc >= 6) K     = stod(argv[5]);
        if (argc >= 7) T     = stod(argv[6]);
        if (argc >= 8) sigma = stod(argv[7]);
        if (argc >= 9) r     = stod(argv[8]);
    } catch (const invalid_argument& e) {
        cerr << "Error: numeric argument is invalid." << endl;
        return 1;
    } catch (const out_of_range& e) {
        cerr << "Error: numeric argument out of range." << endl;
        return 1;
    }

    if (price <= 0.0 || contracts <= 0) {
        cerr << "Error: price and contracts must be positive." << endl;
        return 1;
    }
    if (K <= 0.0 || T <= 0.0 || sigma <= 0.0) {
        cerr << "Error: strike, expiry, and volatility must be positive." << endl;
        return 1;
    }

    // Build option 
    EuropeanOption* e;
    EuropeanCall call(K, T);
    EuropeanPut  put(K, T);

    if (callOrPut == "call") {
        e = &call;
    } else if (callOrPut == "put") {
        e = &put;
    } else {
        cerr << "Error: first argument must be 'call' or 'put'." << endl;
        return 1;
    }

    // Price the option at current spot 
    double bsPrice = e->priceByAnalytical(price, sigma, r);

    // Warn if option is effectively worthless (deep OTM)
    if (bsPrice < 1e-6) {
        cerr << "Warning: option price is effectively zero. "
             << "Spot ($" << price << ") may be too far from strike ($" << K << ")." << endl;
    }

    // Load existing position 
    string positionFile  = ticker + "_position.txt";
    string analyticsFile = ticker + "_analytics.txt";

    double entryPrice   = 0.0;
    int    totalQty     = 0;
    double totalValue   = 0.0;
    int    totalVolume  = 0;
    bool   isNewPosition = true;

    ifstream infile(positionFile);
    if (infile.good()) {
        infile >> entryPrice >> totalQty;
        infile.close();
        isNewPosition = false;
    }

    ifstream analyticsIn(analyticsFile);
    if (analyticsIn.good()) {
        analyticsIn >> totalValue >> totalVolume;
        analyticsIn.close();
    }

    // Open or add to position
    if (isNewPosition) {
        entryPrice  = bsPrice;
        totalQty    = contracts;
        totalValue  = 0.0;   // discard any stale analytics data
        totalVolume = 0;
        cout << ">>> NEW POSITION OPENED <<<" << endl;
    } else {
        double prevCost  = entryPrice * totalQty;
        double newCost   = bsPrice    * contracts;
        totalQty        += contracts;
        entryPrice       = (totalQty > 0) ? (prevCost + newCost) / totalQty : bsPrice;
        cout << ">>> POSITION UPDATED <<<" << endl;
    }

    // Update VWAP accumulators (option price x contracts) 
    totalValue  += bsPrice * contracts;
    totalVolume += contracts;
    double vwap  = (totalVolume > 0) ? (totalValue / totalVolume) : 0.0;

    // P&L
    double pnl        = (bsPrice - entryPrice) * totalQty * OPTION_MULTIPLIER;
    double pnlPct     = (entryPrice > 0.0) ? (bsPrice - entryPrice) / entryPrice * 100.0 : 0.0;
    double positionVal = bsPrice * totalQty * OPTION_MULTIPLIER;

    // Display 
    cout << fixed << setprecision(4);
    cout << "===========================================================\n";
    cout << "Option Type : " << callOrPut << " | Strike: $" << K
         << " | Expiry: " << T << "y | Vol: " << sigma * 100 << "%" << endl;
    cout << "-----------------------------------------------------------\n";
    cout << "[" << ticker << "] Spot Price : $" << price
         << " | Contracts  : " << contracts << endl;
    cout << "BS Option Price : $" << bsPrice
         << " | VWAP        : $" << vwap << endl;
    cout << "-----------------------------------------------------------\n";
    cout << "Entry Price     : $" << entryPrice << endl;
    cout << "Total Contracts : "  << totalQty   << endl;
    cout << "Position Value  : $" << positionVal << endl;
    cout << "P&L             : $" << pnl
         << " (" << pnlPct << "%)" << endl;
    cout << "===========================================================\n";

    // Greeks 
    Greeks g = e->greeks(price, sigma, r);
    cout << "Greeks\n";
    cout << "  Delta : " << g.delta << "\n"
         << "  Gamma : " << g.gamma << "\n"
         << "  Vega  : " << g.vega  << "\n"
         << "  Theta : " << g.theta << "\n"
         << "  Rho   : " << g.rho   << "\n";
    cout << "===========================================================\n";

    // Persist position & analytics 
    ofstream outfile(positionFile);
    if (!outfile) { cerr << "Error: cannot write " << positionFile << endl; return 1; }
    outfile << entryPrice << " " << totalQty << endl;

    ofstream analyticsOut(analyticsFile);
    if (!analyticsOut) { cerr << "Error: cannot write " << analyticsFile << endl; return 1; }
    analyticsOut << totalValue << " " << totalVolume << endl;

    return 0;
}