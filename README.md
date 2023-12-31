# Monte Carlo Approximation of Statistical Moments in C++

## Project Description

From a user defined function and a distribution, this library approximates the statistical moments using Monte Carlo approximation. The library is written in C++ and uses the Eigen library for linear algebra and the Google Test library for unit testing. The library is tested on Linux and macOS.

Given a probablity space $(\Omega, \mathcal{F}, P)$, a function $f \colon \mathbb{R}^n \to \mathbb{R}^m$ and a random variable $X \colon \Omega \to \mathbb{R}^n$, this library approximates the statistical moments using Monte Carlo approximation.

A set of samples $\{X\}_{i=1}^N$ is drawn from the distribution of $X$ and the statistical moments are approximated as follows:

$$
    \mathbb{E}[f(X)^k] \approx \frac{1}{N} \sum_{i=1}^N f(X_i)^k
$$

for $k \in \mathbb{N}$. Other statistical properties are provided if necessary by the program : variance, standard deviation, skewness, kurtosis, hyper-skewness, hyper-kurtosis.

The functions currently supported by the library are the following:

- Multivariate polynomial

The function $p(u) \colon \mathbb{R}^m \to \mathbb{R}^n$ is evaluated on a vector as

$$ p(u) = b + \sum_{k=1}^{K} A_k^{m, n} pow(u, k), $$

where $K$ is the order of the polynomial, $A_k \in \mathbb{R}^{m,n}$ are coefficients of the function, and $b \in \mathbb{R}^m$ is the biase vector, and $pow$ is the element-wise power function.

- Linear function

The function $f(u) \colon \mathbb{R}^m \to \mathbb{R}^n$ is evaluated on a vector as

$$ f(u) = Au + b $$

where $A \in \mathbb{R}^{n, m}$ is the linear operator, and $b\in \mathbb{R}^n$ is the biase vector.

- Logarithmic sum

The function $ f(u)\colon \mathbb{R}^m \to \mathbb{R} $ is evaluated on a vector as

$$
f(u) = \sum_{k=0}^{K} c_k \cdot \log((k+1)u),
$$

where $K$ is the order of the summation,
$c_k \in \mathbb{R}^m$ are coefficients of the function, and $\log$ is the element-wise logarithm function.

- Exponential sum

The function $f(u) \colon \mathbb{R}^m \to \mathbb{R}$ is evaluated on a vector as

$$
f(u) = \sum_{k=0}^{K} c_k \cdot \exp(ku),
$$

where $K$ is the order of the summation,
$c_k \in \mathbb{R}^m$ are coefficients of the function, and $\exp$ is the element-wise exponential function.

- Polynomials

The function $p(u) \colon \mathbb{R}^m \to \mathbb{R}$ is evaluated on a vector as

$$
p(u) = \sum_{k=0}^{K} c_k \cdot pow(u, k),
$$

where $K$ is the order of the polynomial, $c_k \in \mathbb{R}^m$ are coefficients of the polynomial, and $pow$ is the element-wise power function.

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

All the following instructions presume that the repository is cloned and the current working directory is the project's root directory.

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

To build the project, run the following commands:
```bash
cmake -S . -B ./build
cmake --build ./build
```

The documentation is also automatically built, provided that Doxygen is installed. To open the documentation, you can use the following command:
```bash
open build/documentation/html/index.html
```

## Main features

Typical usage of the program is:
```bash
mkdir out
build/main --function tests/data/linear.dat --output ./out
```

Running this command will print approximations of statistical moments of the provided finction and also stores the report and the samples of the function to an output directory. However, generating the output files is optional. The methods used in the approximations (e.g., number of samples, source distribution, additional moment, etc.) can be configured using additional input arguments. A full list is available in the following sections.

Another functionality is testing the Central Limit Theorem for the provided function. This can be achieved by passin `--clt 1`. Doing this, in addition to the statistical moments, the Central Limit Theorem is also performed and relative errors (empirical vs. approximated theoretical mean and variance) will be printed out for 10, 50, and 90 samples.

## Tests

You can run all the tests using the following command:
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
| PolynomialEval  | function_test.cpp    | Check the evaluation of a polynomial function|
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

To see the full list of input arguments you can use the following command:
```bash
build/main --help
```

To run the code:
```bash
build/main --function <path-to-input-function> [options]
```

## Limitations and prospects

### Future work

- The user input is currently limited to a file with pre-defined structure. An interactive mode can be implemented to define the function via the command line.

- The configurations of the source distributions (mean and variance for the Normal distribution, lower and upper bounds for the Uniform distribution) are currently limited to pre-defined -standard- values. These can be defined by the user.

- Other distributions and function types can be implemented.

- The plots are not implemented currently. The option is open for development. A plot of the distribution of the function samples could be informative. For vectorial functions, this can be more challenging since dimension reduction might be necessary.

- Study of the central limit theorem with the relation between the error and the number of samples is not implemented currently. The option is open for development.

### Code optimization

- Currently, the input and output dimensions of the functions are limited to 4. This can easily be extended to any number before the compilation of `main`. However, when used as a library, functions from any arbitrary dimension can be built statically before compilation. Extending the `Function` class to allocate dimensions dynamically is open for development.

- The `Vector` class can be easily extended to be defined on other data types. Currently, it is limited to `double`.

- Replacing standard vectors (`std::vector`) with standard arrays (`std::array`) can make the memory management more efficient, since we are dealing with fixed-size vectors most of the times.

- The `Vector` class can be extended and also used in the `MonteCarloApproximator` instead of Eigen matrices.

- The code could be parallelized using OpenMP or MPI. As a starting point, the generation of random samples and passing them through the function is a perfect candidate for parallelization.

### Boost library

- Distributions from the Boost library can be used.

- The inverse error function is naively implemented. More sophisticated implementations are available in the Boost library, which will make the random sampling of the Normal distribution much faster.

### Other

- Initialization of the git submodules can be handled by `CMakeLists.txt`.

- Building the documentation can be an option.


## Contributions

This project is part of the Programming Concepts in Scientific Computing (MATH-458) course at École Polytechnique Fédérale de Lausanne (EPFL), given in Fall 2023.

### Authors

- Sepehr Mousavi ([sepehr.mousavi@epfl.ch](mailto:sepehr.mousavi@epfl.ch))
- Paul Devianne ([paul.devianne@epfl.ch](mailto:paul.devianne@epfl.ch))

### Instructors

- Guillaume Anciaux ([guillaume.anciaux@epfl.ch](mailto:guillaume.anciaux@epfl.ch))
- Haoze He ([haoze.he@epfl.ch](mailto:haoze.he@epfl.ch))
