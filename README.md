Project: C++ Quant Trading Engine

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

`C = S * N(d1) - K * e^(-rT) * N(d2)`

**European Put Option Price (P):**

`P = K * e^(-rT) * N(-d2) - S * N(-d1)`

Where:

`d1 = [ln(S/K) + (r + (σ^2)/2) * T] / (σ * √T)`
`d2 = d1 - σ * √T`

And:
*   `S`: Current stock price
*   `K`: Option strike price
*   `T`: Time to expiration (in years)
*   `r`: Risk-free interest rate (annualized)
*   `σ`: Volatility of the stock's returns
*   `N(x)`: Cumulative standard normal distribution function
*   `e`: Euler's number (base of the natural logarithm)
*   `ln`: Natural logarithm

### Volume Weighted Average Price (VWAP) Formula

`VWAP = (Σ (Price * Volume)) / (Σ Volume)`

Where:
*   `Price`: Price of a trade
*   `Volume`: Volume of a trade
*   `Σ`: Summation

### Profit & Loss (P&L) Formula (Simple Example)

For a single stock trade:

`P&L = (Selling Price - Buying Price) * Number of Shares`

For an option position:

`P&L = (Current Option Price - Purchase Price) * Number of Contracts * Multiplier`

## How to Run the Program

To compile and run this C++ quantitative trading engine, follow these steps:

### Prerequisites

YouYou will need the following installed on your system:
*   **CMake:** Version 3.20 or higher. Used for managing the build process.
*   **A C++ Compiler:** Supporting C++17 standard (e.g., GCC, Clang).

### Building the Project

1.  **Clone the repository:**
    ```bash
    git clone <repository_url>
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

To price a European Call option for ticker `APPL` with a strike price of `100` and `11` contracts:

```bash
./QuantTradingEngine call APPL 100 11
```

To price a European Put option:

```bash
./QuantTradingEngine put MSFT 200 5
```

To reset any stored portfolio data (if applicable):

```bash
./QuantTradingEngine reset
```

**Note:** The exact arguments and their order might vary depending on the specific implementation within `main.cpp`. Refer to the program's usage message (if available by running `./QuantTradingEngine` without arguments) for precise instructions.