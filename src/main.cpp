#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include "analytics.h"
#include "portfolio.h"
#include "EuropeanCall.h"
#include "EuropeanPut.h"

using namespace std;

int main(int argc, char* argv[]) {
    // Check for reset command
    if (argc >= 2 && (string(argv[1]) == "reset" || string(argv[1]) == "clear")) {
        system("rm -f *_position.txt *_analytics.txt");
        cout << "All position and analytics files cleared!" << endl;
        return 0;
    }
    
    // Default parameters
    double K = 150.0;      // Strike
    double T = 0.5;        // 6 months
    double r = 0.05;       // 5%
    double sigma = 0.25;   // 25% volatility
    
    // Check command line arguments
    if (argc < 5) {
        cout << "Usage: " << argv[0] << " [call|put] [ticker] [price] [volume]" << endl;
        cout << "Example: " << argv[0] << " call AAPL 154.5 1000" << endl;
        cout << "Reset: " << argv[0] << " reset" << endl;
        return 1;
    }
    
    string callOrPut = argv[1];
    string ticker = argv[2];
    double price = atof(argv[3]);
    int volume = atoi(argv[4]);
    
    // Create option
    EuropeanOption* e;
    EuropeanCall call(K, T);
    EuropeanPut put(K, T);
    
    if (callOrPut == "call") {
        e = &call;
    } else if (callOrPut == "put") {
        e = &put;
    } else {
        cout << "Error: Must specify 'call' or 'put'" << endl;
        return 1;
    }
    
    // Calculate option price at current spot
    double bsPrice = e->priceByAnalytical(price, sigma, r);
    
    // Load or initialize position from file
    string positionFile = ticker + "_position.txt";
    string analyticsFile = ticker + "_analytics.txt";
    double entryPrice = 0.0;
    int qty = 0;
    bool isNewPosition = true;
    double totalValue = 0.0;
    int totalVolume = 0;
    
    ifstream infile(positionFile);
    if (infile.good()) {
        infile >> entryPrice >> qty;
        infile.close();
        isNewPosition = false;
    }
    
    // Load analytics data (VWAP)
    ifstream analyticsIn(analyticsFile);
    if (analyticsIn.good()) {
        analyticsIn >> totalValue >> totalVolume;
        analyticsIn.close();
    }
    
    // Handle new position
    if (isNewPosition) {
        qty = 1;
        entryPrice = bsPrice;
        cout << ">>> NEW POSITION OPENED <<<" << endl;
    }
    
    // Update cumulative values for VWAP calculation
    totalValue += (price * volume);
    totalVolume += volume;
    double vwap = (totalVolume > 0) ? (totalValue / totalVolume) : 0.0;
    
    // Calculate P&L
    double pnl = (bsPrice - entryPrice) * qty;
    
    // Display results
    cout << fixed << setprecision(4);
    cout << "Option Type: " << callOrPut << " | Strike: " << K 
         << " | Vol: " << sigma << endl;
    cout << "-----------------------------------------------------------" << endl;
    cout << "[" << ticker << "] Spot Price: " << price 
         << " | Volume: " << volume << endl;
    cout << "VWAP: $" << vwap << " | Option Value: $" << bsPrice << endl;
    cout << "Entry Price: $" << entryPrice << endl;
    cout << "P&L: $" << pnl << " (" << (entryPrice > 0 ? (pnl / entryPrice * 100) : 0.0) << "%)" << endl;
    
    // Show Greeks
    Greeks g = e->greeks(price, sigma, r);
    cout << "-----------------------------------------------------------" << endl;
    cout << "Greeks - Delta: " << g.delta << " | Gamma: " << g.gamma 
         << " | Vega: " << g.vega << " | Theta: " << g.theta 
         << " | Rho: " << g.rho << endl;
    
    // Save updated position and analytics to files
    ofstream outfile(positionFile);
    outfile << entryPrice << " " << qty << endl;
    outfile.close();
    
    ofstream analyticsOut(analyticsFile);
    analyticsOut << totalValue << " " << totalVolume << endl;
    analyticsOut.close();
    
    return 0;
}
