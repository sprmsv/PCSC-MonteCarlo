# MCA: Monte Carlo Approximation of Statistical Moments in C++

## Project Description

From a user defined function and a distribution, this library approximates the statistical moments using Monte Carlo approximation. The library is written in C++ and uses the Eigen library for linear algebra and the Google Test library for unit testing. The library is tested on Linux and macOS.

Given a probablity space $(\Omega, \mathcal{F}, P)$, a function $f \colon \mathbb{R}^n \to \mathbb{R}^m$ and a random variable $X \colon \Omega \to \mathbb{R}^n$, this library approximates the statistical moments using Monte Carlo approximation. 

A set of samples $\{X_i\}_{i=1}^N$ is drawn from the distribution of $X$ and the statistical moments are approximated as follows:

\[ \mathbb{E}[f(X)^k] \approx \frac{1}{N} \sum_{i=1}^N f(X_i)^k \]

for $k \in \mathbb{N}$. Other statistical properties are provided if necessary by the program : variance, standard deviation, skewness, kurtosis, hyper-skewness, hyper-kurtosis.

The functions currently supported by the library are the following:

- Multivariate polynomial

 The function \f$ p(u): R^m -> R^n \f$ is evaluated on a vector as
 \f[
    p(u) = b + \sum_{k=1}^{K} A_k^{m, n} pow(u, k),
 \f]
 where \f$ K \f$ is the order of the polynomial,
 \f$ A_k \in R^{m, n} \f$ are coefficients of the function,
 \f$ b \in R^n \f$ is the biase vector,
 and \f$ pow \f$ is the element-wise power function.

- Exponential sum
 The function \f$ f(u): R^m -> R \f$ is evaluated on a vector as
 \f[
    f(u) = \sum_{k=0}^{K} c_k . log((k+1)u),
 \f]

 - Logarithmic sum
 The function \f$ f(u): R^m -> R \f$ is evaluated on a vector as
 \f[
     f(u) = \sum_{k=0}^{K} c_k . exp(ku),
  \f]
  where \f$ K \f$ is the order of the summation,
  \f$ c_k \in R^m \f$ are coefficients of the function,
  and \f$ exp \f$ is the element-wise exponential function.
 
 - Polynomials
 The function \f$ p(u): R^m -> R \f$ is evaluated on a vector as
 \f[
   p(u) = \sum_{k=0}^{K} c_k . pow(u, k),
 \f]
 where \f$ K \f$ is the order of the polynomial,
 \f$ c_k \in R^m \f$ are coefficients of the polynomial,
 and \f$ pow \f$ is the element-wise power function.

 - Any combination of the above functions. The operators between functions are the following:
   - Addition
   - Subtraction
   - Multiplication
   - Division

The distribution of the random variable $X$ is defined by the user. The following distributions are currently supported:

- Uniform distribution
- Normal distribution


## Code Compilation and Documentation

This library deals with the statistical study of non-linear operators by approximating expectations and statistical moments using Monte Carlo methods.

All the following instructions presume that the current working directory is the project's root directory.

First, make sure that [Doxygen](https://www.doxygen.nl/manual/install.html) and [Graphviz](https://graphviz.org/download/) are installed:
```bash
doxygen --version
dot --version
```
If not, please install them.

Initialize the submodules:
```bash
git submodule update --init eigen
git submodule update --init gtest
```

To build the project:
```bash
cmake -S . -B ./build
cmake --build ./build
```

To open the documentation:
```bash
open build/documentation/html/index.html
```

## Main features

Typical usage:
```bash
mkdir out
build/main --function tests/data/linear.dat --output ./out
```

## Tests

To run the tests:
```bash
build/tests
```

Implemented tests:

| TestName    | TestFile.cpp |
| -------- | ------- |
| VectorInitStd  | vector_test.cpp    |
| VectorSize | vector_test.cpp    |
| VectorPlus  | vector_test.cpp    |
| VectorMinus  | vector_test.cpp    |
| VectorTimes  | vector_test.cpp    |
| VectorDivide  | vector_test.cpp    |
| VectorDot  | vector_test.cpp    |
| Polynomial eval  | function_test.cpp    |
| MultivariatePolynomialEval  | function_test.cpp    |
| LinearEval  | function_test.cpp    |
| SumExponentialEval  | function_test.cpp    |
| SumLogarithmEval  | function_test.cpp    |
| CombinedSum  | function_test.cpp    |
| CombinedDiff  | function_test.cpp    |
| CombinedProd  | function_test.cpp    |
| CombineDiv  | function_test.cpp    |
| ComplexCombination  | function_test.cpp    |

The tests are implemented using the Google Test library. The tests are located in the `tests` directory. Each test is built assuming previous correct tests (VectorSum assumes VectorSize works properly).

## Command-line interface

<!-- TODO: A table with the input arguments + descriptions -->

To see the input arguments:
```bash
build/main --help
```

To run the code:
```bash
build/main ...
```

## Limitations

<!-- TODO: Limitations, TODOs, perspectives, etc. -->

## Contributions

This project is part of the Programming Concepts in Scientific Computing (MATH-458) course at École Polytechnique Fédérale de Lausanne (EPFL), given in Fall 2023.

### Authors

- Sepehr Mousavi ([sepehr.mousavi@epfl.ch](mailto:sepehr.mousavi@epfl.ch))
- Paul Devianne ([paul.devianne@epfl.ch](mailto:paul.devianne@epfl.ch))

### Instructors

- Guillaume Anciaux ([guillaume.anciaux@epfl.ch](mailto:guillaume.anciaux@epfl.ch))
- Haoze He ([haoze.he@epfl.ch](mailto:haoze.he@epfl.ch))
