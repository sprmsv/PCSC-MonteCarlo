# MCA: Monte Carlo Approximation of Statistical Moments in C++

## Project Description

From a user defined function and a distribution, this library approximates the statistical moments using Monte Carlo approximation. The library is written in C++ and uses the Eigen library for linear algebra and the Google Test library for unit testing. The library is tested on Linux and macOS.

Given a probablity space $(\Omega, \mathcal{F}, P)$, a function $f \colon \mathbb{R}^n \to \mathbb{R}^m$ and a random variable $X \colon \Omega \to \mathbb{R}^n$, this library approximates the statistical moments using Monte Carlo approximation. 

A set of samples $\{X_i\}_{i=1}^N$ is drawn from the distribution of $X$ and the statistical moments are approximated as follows:

$$
    \mathbb{E}[f(X)^k] \approx \frac{1}{N} \sum_{i=1}^N f(X_i)^k
$$

for $k \in \mathbb{N}$. Other statistical properties are provided if necessary by the program : variance, standard deviation, skewness, kurtosis, hyper-skewness, hyper-kurtosis.

The functions currently supported by the library are the following:

- Multivariate polynomial

The function $p(u) \colon \mathbb{R}^m \to \mathbb{R}^n$ is evaluated on a vector as 

$$ p(u) = b + \sum_{k=1}^{K} A_k^{m, n} pow(u, k), $$

where $ K $ is the order of the polynomial, $ A_k \in \mathbb{R}^{m, n} $ are coefficients of the function, $ b \in \mathbb{R}^n $ is the biase vector, and $ pow $ is the element-wise power function.

- Linear function
The function $f(u)\colon \mathbb{R}^m \to \mathbb{R}^n $ is evaluated on a vector as

$$ f(u) = Au + b, $$

where $ A \in \mathbb{R}^{n, m} $ is the linear operator, and $ b \in \mathbb{R}^n $ is the biase vector.

- Logarithmic sum
The function $ f(u)\colon \mathbb{R}^m \to \mathbb{R} $ is evaluated on a vector as 
$$ f(u) = \sum_{k=0}^{K} c_k \cdot \log((k+1)u),$$
where $ K $ is the order of the summation, $ c_k \in \mathbb{R}^m $ are coefficients of the function, and $ \log $ is the element-wise logarithm function.

- Exponential sum
The function $f(u)\colon \mathbb{R}^m \to \mathbb{R} $ is evaluated on a vector as
$$ f(u) = \sum_{k=0}^{K} c_k \cdot \exp(ku),$$
where $ K $ is the order of the summation, $ c_k \in \mathbb{R}^m $ are coefficients of the function, and $ \exp $ is the element-wise exponential function.

- Polynomials

The function $p(u): \mathbb{R}^m \to \mathbb{R} $ is evaluated on a vector as
$$ p(u) = \sum_{k=0}^{K} c_k \cdot pow(u, k),$$
where $ K $ is the order of the polynomial, $ c_k \in \mathbb{R}^m $ are coefficients of the polynomial, and $ pow $ is the element-wise power function.

- Any combination of the above functions. The operators between functions are the following:
   - Addition
   - Subtraction
   - Multiplication
   - Division

The distribution of the random variable $X$ is defined by the user. The following distributions are currently supported:

- Uniform distribution $U(a, b)$
- Normal distribution $\mathcal{N}(\mu, \sigma^2)$


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

| TestName    | TestFile.cpp | Description |
| -------- | ------- | ----------- |
| VectorInitStd  | vector_test.cpp    | Initialize a vector with a C++ vector standard library |
| VectorSize | vector_test.cpp    | Check the size is well defined|
| VectorPlus  | vector_test.cpp    | Check the addition of two vectors |
| VectorMinus  | vector_test.cpp    | Check the subtraction of two vectors |
| VectorTimes  | vector_test.cpp    | Check the multiplication of two vectors elementwise |
| VectorDivide  | vector_test.cpp    | Check the division of two vectors elementwise |
| VectorDot  | vector_test.cpp    | Check the dot product of two vectors |
| Polynomial eval  | function_test.cpp    | Check the evaluation of a polynomial function|
| MultivariatePolynomialEval  | function_test.cpp    | Check the evaluation of a multivariate polynomial function|
| LinearEval  | function_test.cpp    |  Check the evaluation of a linear function|
| SumExponentialEval  | function_test.cpp    | Check the evaluation of a sum of exponential function|
| SumLogarithmEval  | function_test.cpp    | Check the evaluation of a sum of logarithm function|
| CombinedSum  | function_test.cpp    | Check the evaluation of a sum of functions|
| CombinedDiff  | function_test.cpp    | Check the evaluation of a difference of functions|
| CombinedProd  | function_test.cpp    | Check the evaluation of a product of functions|
| CombineDiv  | function_test.cpp    | Check the evaluation of a division of functions|
| ComplexCombination  | function_test.cpp    | Check the evaluation of a complex combination of functions|

The tests are implemented using the Google Test library. The tests are located in the `tests` directory. Each test is built assuming previous correct tests (VectorSum assumes VectorSize works properly).

## Command-line interface

| Argument    | Description | Required |
| -------- | ----------- | -------- |
| --function | Path to the file containing the function to approximate | Yes |
| -k | Order of the statistical moment to approximate | No (default: 1) |
| --mode | Type of moment | No (default: standardized) |
| --dist | Distribution of the random variable | No (default: normal) |
| --n | Number of samples | No (default: 1000) |
| --output | Path to the output file | No (default: stdout) |
| --plot | Whether to save plots of samples | No (default: none) |
| --clt | Whether to print the central limit theorem output| No (default: 0) |

To see the input arguments:
```bash
build/main --help
```

To run the code:
```bash
build/main ...
```

## Limitations

- The plots are not implemented currently. The option is open for development.
- Study of the central limit theorem with the relation between the error and the number of samples is not implemented currently. The option is open for development.
- Other distributions can be implemented.
- Other functions can be implemented.
- Boost library could be used for the distribution and set as an option for the user.
- The code could be parallelized using OpenMP or MPI.
- Other types of sampler than Monte Carlo could be implemented.

## Contributions

This project is part of the Programming Concepts in Scientific Computing (MATH-458) course at École Polytechnique Fédérale de Lausanne (EPFL), given in Fall 2023.

### Authors

- Sepehr Mousavi ([sepehr.mousavi@epfl.ch](mailto:sepehr.mousavi@epfl.ch))
- Paul Devianne ([paul.devianne@epfl.ch](mailto:paul.devianne@epfl.ch))

### Instructors

- Guillaume Anciaux ([guillaume.anciaux@epfl.ch](mailto:guillaume.anciaux@epfl.ch))
- Haoze He ([haoze.he@epfl.ch](mailto:haoze.he@epfl.ch))
