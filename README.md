# C++ Quant Trading Engine

## Tech Stack

This project is a C++ quantitative trading engine designed to perform various financial calculations, particularly focusing on options pricing and portfolio analytics. It uses standard C++ features and CMake for build management.

### European Options

A European option is a type of option that can only be exercised at its expiration date. This project specifically implements models for European Call and Put options.

*   **European Call Option:** Gives the holder the right, but not the obligation, to buy an underlying asset at a specified strike price on the expiration date.
*   **European Put Option:** Gives the holder the right, but not the obligation, to sell an underlying asset at a specified strike price on the expiration date.

### Greeks

The "Greeks" are a set of measures that quantify the sensitivity of an option's price to changes in underlying factors. They are crucial for risk management in options trading.

*   **Delta (Δ):** Measures the rate of change of the option price with respect to a change in the underlying asset's price. A delta of 0.5 means the option price will move 50 cents for every $1 move in the underlying asset.
*   **Gamma (Γ):** Measures the rate of change of delta with respect to a change in the underlying asset's price. It indicates how much delta will change for a $1 move in the underlying.
*   **Vega (ν):** Measures the sensitivity of the option price to changes in the volatility of the underlying asset. A high vega means the option price is very sensitive to volatility changes.
*   **Theta (Θ):** Measures the sensitivity of the option price to the passage of time (time decay). It indicates how much the option's value will decrease each day, all else being equal.
*   **Rho (ρ):** Measures the sensitivity of the option price to a change in the risk-free interest rate.

### Volume Weighted Average Price (VWAP)

VWAP is a trading benchmark used by traders that gives the average price a security has traded at throughout the day, based on both volume and price. It is calculated by taking the total value of shares traded and dividing it by the total volume of shares traded over a specified period.

### Profit & Loss (P&L)

Profit and Loss (P&L) is a financial statement that summarizes the revenues, costs, and expenses incurred during a specific period. In trading, it refers to the gain or loss realized on a position or a series of trades.

## Program Overview

This program serves as a command-line utility for pricing European options and performing portfolio analytics. It takes inputs such as the option type (call/put), ticker symbol, strike price, and volume, and likely calculates option prices, Greeks, and potentially manages a portfolio of these options. The `main.cpp` file processes command-line arguments, utilizes classes like `EuropeanOption`, `EuropeanCall`, `EuropeanPut` to model the options, and `analytics` to perform calculations. The `portfolio` module likely handles managing multiple option positions.

From start to end, the program:
1.  Parses command-line arguments to determine the operation (e.g., pricing a call option, resetting a portfolio).
2.  Initializes option objects with provided parameters (ticker, strike, volume, etc.).
3.  Performs calculations such as option pricing (using Black-Scholes model) and Greek sensitivities.
4.  Outputs the results to the console.

## Mathematical Formulas

### Black-Scholes Model for European Options

The Black-Scholes model is a mathematical model for the dynamics of a financial market containing derivative investment instruments. The formulas for a non-dividend-paying stock are:

**European Call Option Price (C):**

$$C = S \cdot \Phi(d_1) - K \cdot e^{-rT} \cdot \Phi(d_2)$$

**European Put Option Price (P):**

$$P = K \cdot e^{-rT} \cdot \Phi(-d_2) - S \cdot \Phi(-d_1)$$

**Intermediate Variables**

$$d_1 = \frac{\ln\left(\dfrac{S}{K}\right) + \left(r + \dfrac{\sigma^2}{2}\right) T}{\sigma \sqrt{T}}$$

$$d_2 = d_1 - \sigma\sqrt{T}$$

### Put-Call Parity

For European options, the following relationship always holds (no-arbitrage):

$$C - P = S - K \cdot e^{-rT}$$

### Key Assumptions

1. The stock follows **geometric Brownian motion** with constant drift and volatility.
2. **No dividends** are paid during the option's life.
3. Markets are **frictionless** — no transaction costs or taxes.
4. The **risk-free rate** `r` and **volatility** `σ` are constant over the life of the option.
5. **No arbitrage** opportunities exist.
6. Options are **European-style** (exercisable only at expiration).

### Quick Reference — Signs & Bounds

- **Call price bounds:** `max(S − Ke^{−rT}, 0) ≤ C ≤ S`
- **Put price bounds:** `max(Ke^{−rT} − S, 0) ≤ P ≤ Ke^{−rT}`
- As `T → 0`: both prices converge to their intrinsic values.
- As `σ → 0`: the option is worth its discounted intrinsic value.

Where:
*   `S`: Current stock price
*   `K`: Option strike price
*   `T`: Time to expiration (in years)
*   `r`: Risk-free interest rate (annualized)
*   `σ`: Volatility of the stock's returns
*   `Φ(x)`: Cumulative standard normal distribution function
*   `e`: Euler's number (base of the natural logarithm)
*   `ln`: Natural logarithm

### Volume Weighted Average Price (VWAP) Formula

For options, VWAP is computed using the **option price** weighted by number of contracts:

$$VWAP = \frac{\sum (OptionPrice \times Contracts)}{\sum Contracts}$$

Where:
*   `OptionPrice`: Black-Scholes price of the option at time of trade
*   `Contracts`: Number of option contracts traded
*   `Σ`: Summation

### Profit & Loss (P&L) Formula

For a single stock trade:

`P&L = (SellingPrice - BuyingPrice) * NumberOfShares`

For an option position:

`P&L = (CurrentOptionPrice - EntryOptionPrice) * NumberOfContracts * Multiplier`

Where `Multiplier = 100` for standard equity options (each contract represents 100 shares).

**Position value:**

$$PositionValue = CurrentOptionPrice \times NumberOfContracts \times Multiplier$$

## How to Run the Program

To compile and run this C++ quantitative trading engine, follow these steps.

### Prerequisites

You will need the following installed on your system:
*   **CMake:** Version 3.20 or higher. Used for managing the build process.
*   **A C++ Compiler:** Supporting C++17 standard (e.g., GCC, Clang).

### Building the Project

1.  **Clone the repository:**
    ```bash
    git clone https://github.com/kabinanB/cpp-quant-trading-engine.git
    cd cpp-quant-trading-engine
    ```

2.  **Create a build directory and navigate into it:**
    ```bash
    mkdir build
    cd build
    ```

3.  **Configure CMake and build the project:**
    ```bash
    cmake ..
    make
    ```
    This will compile the source code and create the executable named `QuantTradingEngine` in the `build` directory.

### Running the Program

After building, you can run the executable directly from the `build` directory. The program expects specific command-line arguments.

**Example Usage:**

Minimum required arguments only (defaults apply for K, T, σ, r):
```bash
./QuantTradingEngine call AAPL 154.5 10
```

Specifying a custom strike near the spot:
```bash
./QuantTradingEngine call AAPL 154.5 10 150.0
```

Specifying strike, expiry and volatility:
```bash
./QuantTradingEngine call MME 100.5 500 100.0 0.5 0.28
```

Full control over all parameters:
```bash
./QuantTradingEngine put MSFT 200.0 5 200.0 0.25 0.30 0.04
```

Reset all stored position and analytics data:
```bash
./QuantTradingEngine reset
```
> **Note:** The fourth argument is the **spot price** of the underlying asset, the fifth is the **number of contracts** and the last argument is **interest rate**. Refer to the program's usage message (run `./QuantTradingEngine` without arguments) for precise instructions.
