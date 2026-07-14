# Path-Dependent Option Pricing in the Cox–Ross–Rubinstein Binomial Model

## Overview

This project implements the pricing of **path-dependent derivatives** within the **Cox–Ross–Rubinstein (CRR) Binomial Model**. Unlike standard European options, whose payoff depends only on the terminal stock price, path-dependent options require the entire stock price trajectory to be evaluated.

Two pricing techniques are implemented:

1. **Exact Path Enumeration** (Risk-Neutral Valuation)
2. **Monte Carlo Simulation**

The project prices the following derivatives:

* Arithmetic Asian Call Option
* Floating Strike Lookback Option

Additionally, the program measures the computational performance of both pricing approaches and compares their scalability as the number of time steps increases.

---

# Project Structure

```text
PathDependentOptions/
│
├── main.cpp                     # Driver program
├── BinModel.h/.cpp              # CRR binomial model
├── PathDependentOption.h/.cpp   # Base class and pricing algorithms
├── assessment2.cbp              # Code::Blocks project
└── NM_Assessment2_Schwarzer.pdf # Assignment report
```

---

# Mathematical Background

The implementation assumes the standard **CRR Binomial Model**.

For every time step,

[
S_{t+1}=
\begin{cases}
uS_t,&\text{Up move}\
dS_t,&\text{Down move}
\end{cases}
]

where

* (S_0) = initial stock price
* (u) = up factor
* (d) = down factor
* (R) = one-period risk-free growth factor

To exclude arbitrage opportunities, the model requires

[
d<R<u
]

The corresponding risk-neutral probability is

[
p=\frac{R-d}{u-d}.
]

---

# Pricing by Complete Path Enumeration

For a path-dependent option, every possible stock price path must be evaluated.

Since each time step has two possible outcomes,

[
\Omega={U,D}^N,
]

the total number of possible paths equals

[
2^N.
]

For every path

1. construct the stock price sequence,
2. compute its payoff,
3. multiply by its risk-neutral probability,
4. discount the expectation.

The implemented pricing formula is

[
V_0
===

R^{-N}
\sum_{\omega\in\Omega}
P^*(\omega)
,f(\omega),
]

where

* (f(\omega)) denotes the payoff,
* (P^*(\omega)) is the risk-neutral probability of the path.

For a path containing (k) upward moves,

[
P^*(\omega)
===========

p^k(1-p)^{N-k}.
]

This corresponds directly to

```cpp
PathProb = pow(p, up_moves)
         * pow(1-p, N-up_moves);
```

inside `PriceByPathEvaluation()`.

---

# Binary Path Enumeration Using Bit Masks

Instead of recursively generating all possible stock paths, the project uses **bit manipulation**.

Each integer

[
i=0,\ldots,2^N-1
]

is interpreted as the binary representation of one complete stock path.

For example, when

[
N=4,
]

the integer

```text
13 = 1101₂
```

represents

```text
Step 1 : Up
Step 2 : Down
Step 3 : Up
Step 4 : Up
```

The implementation checks each bit using

```cpp
if (i & (1 << step))
```

### Explanation

The expression

```cpp
1 << step
```

creates a bit mask.

Example:

```text
step = 0

0001
```

```text
step = 1

0010
```

```text
step = 2

0100
```

```text
step = 3

1000
```

The left-shift operator

```cpp
1 << step
```

moves the binary digit one position to the left for every time step.

The expression

```cpp
i & (1 << step)
```

performs a bitwise AND.

If the result is non-zero,

* the bit equals 1,
* an **up move** is taken.

Otherwise,

* the bit equals 0,
* a **down move** is taken.

This allows every possible path to be generated without recursion or storing the entire tree.

---

# Arithmetic Asian Call

The payoff depends on the arithmetic average of all observed stock prices.

The average stock price is

[
\bar S
======

\frac1{N+1}
\sum_{i=0}^{N}
S_i.
]

The option payoff is

[
\max(\bar S-K,0).
]

Implemented as

```cpp
MeanPrice = PriceSum / size;
return max(MeanPrice - K, 0.0);
```

---

# Floating Strike Lookback Option

The lookback option uses the minimum stock price observed during the life of the option.

The payoff equals

[
S_T-\min_{0\le i\le N}S_i.
]

The implementation scans the entire path once to locate the minimum price before computing the payoff.

---

# Monte Carlo Pricing

The project also prices both derivatives using Monte Carlo simulation.

Instead of evaluating every possible path, each time step samples

[
U
\quad\text{with probability}\quad p
]

or

[
D
\quad\text{with probability}\quad 1-p.
]

After generating

[
M
]

sample paths,

the estimator becomes

[
\hat V
======

R^{-N}
\frac1M
\sum_{i=1}^{M}
f(\omega_i).
]

The implementation uses

```cpp
rand() / RAND_MAX
```

to generate uniform random variables on

[
[0,1].
]

---

# Monte Carlo Standard Error

The sample variance is computed as

[
\hat\sigma^2
============

\frac1{M-1}
\sum_{i=1}^{M}
(f_i-\bar f)^2.
]

The standard error of the estimator equals

[
SE
==

R^{-N}
\frac{\hat\sigma}{\sqrt M}.
]

Both the option price and standard error are returned as

```cpp
pair<double,double>
```

where

* first = estimated price
* second = Monte Carlo standard error

---

# Computational Complexity

## Path Enumeration

Number of paths

[
2^N.
]

Each path requires

[
O(N)
]

operations.

Overall complexity

[
O(N2^N).
]

Memory usage

[
O(N)
]

since only one path is stored at any time.

---

## Monte Carlo

For

* (M) simulations
* (N) time steps

the complexity is

[
O(MN).
]

Memory usage

[
O(N+M),
]

where

* one array stores the current path,
* another stores simulated payoffs for variance estimation.

---

# Object-Oriented Design

The project follows a polymorphic design.

```
PathDependentOption
        |
        +----------------------+
        |                      |
ArithmeticAsianCall     LookbackOption
```

The abstract base class defines

* path evaluation
* Monte Carlo pricing

while derived classes override

```cpp
Payoff(...)
```

to implement derivative-specific payoff functions.

This design allows additional path-dependent derivatives to be implemented by defining only a new payoff function.

---

# Input

The user specifies

* Initial stock price (S_0)
* Up factor (u)
* Down factor (d)
* Risk-free growth factor (R)

The program then executes three assessment tasks:

**Exercise 2.1**

* Exact path evaluation

**Exercise 2.2**

* CPU timing analysis

**Exercise 2.3**

* Monte Carlo pricing and standard error estimation

---

# Compilation

Using Code::Blocks

Open

```
assessment2.cbp
```

and build the project.

Using g++

```bash
g++ *.cpp -o PathDependentOptions
```

Run

```bash
./PathDependentOptions
```

or on Windows

```bash
PathDependentOptions.exe
```

---

# Key Concepts Demonstrated

* Cox–Ross–Rubinstein Binomial Model
* Risk-neutral valuation
* Path-dependent derivatives
* Arithmetic Asian options
* Floating strike lookback options
* Complete path enumeration
* Binary path generation using bit masks
* Left-shift (`<<`) and bitwise AND (`&`)
* Monte Carlo simulation
* Standard error estimation
* Dynamic memory allocation
* Polymorphism and inheritance
* Computational complexity analysis
