#ifndef MC_FUNCTIONS_HPP
#define MC_FUNCTIONS_HPP

#include "sampler.hpp"
#include "distributions.hpp"
#include "vector.hpp"
#include "exceptions.hpp"

#include <Eigen/Core>

#include <string>
#include <vector>
#include <memory>
#include <cmath>
#include <fstream>
#include <iostream>

template <unsigned int dim_inp, unsigned int dim_out> class CombinedFunctionSum;
template <unsigned int dim_inp, unsigned int dim_out> class CombinedFunctionSub;
template <unsigned int dim_inp, unsigned int dim_out> class CombinedFunctionMul;
template <unsigned int dim_inp, unsigned int dim_out> class CombinedFunctionDiv;

/**
 * @brief A functor class for wrapping a mathematical vectorial multivariate function.
 * Parametric mathematical functions can be constructed using the daughters of this base class.
 *
 * The function provides additional features such as calculating Monte Carlo approximations of the
 * statistical moments of the function distribution:
 * \f[
 * E_{x \sim X}(f(x)^k) \simeq \frac{1}{N} \sum_{i=1}^{N}f(x_i)^k,
 * \f]
 * where \f$ x_i \sim X \f$ are samples from a random distribution.
 *
 * @tparam dim_inp The input dimension of the function.
 * @tparam dim_out The output dimension of the function.
 */
template <unsigned int dim_inp, unsigned int dim_out>
class Function
{
public:
  /// @brief Construct a new Function object.
  Function();

  /// @brief Copy a Function object.
  Function(const Function<dim_inp, dim_out>&);

  /// @brief Destroy the Function object.
  virtual ~Function();

  /// @brief Compute the output of the function on an input.
  /// @param x The input vector or scalar.
  /// @return The output of the function.
  Vector<dim_out> operator()(const Vector<dim_inp>& x);

  /// @brief Compute the output of the function on several inputs.
  /// @param x A pointer to the inputs.
  /// @return A pointer to the outputs.
  std::shared_ptr<std::vector<Vector<dim_out>>> operator()(std::shared_ptr<std::vector<Vector<dim_inp>>> x);

  /// @brief Construct a combined function from the present function an another one by summing their outputs.
  CombinedFunctionSum<dim_inp, dim_out> operator+(const Function<dim_inp, dim_out>&) const;
  /// @brief Construct a combined function from the present function an another one by subtracting their outputs.
  CombinedFunctionSub<dim_inp, dim_out> operator-(const Function<dim_inp, dim_out>&) const;
  /// @brief Construct a combined function from the present function an another one by multiplying their outputs.
  CombinedFunctionMul<dim_inp, dim_out> operator*(const Function<dim_inp, dim_out>&) const;
  /// @brief Construct a combined function from the present function an another one by dividing their outputs.
  CombinedFunctionDiv<dim_inp, dim_out> operator/(const Function<dim_inp, dim_out>&) const;

  /// @brief Call the function on an input and return its output.
  virtual Vector<dim_out> call(const Vector<dim_inp>& x) const = 0;

  /**
   * @brief Construct a Monte Carlo Approximator object by sampling the function.
   * Random samples ar drawn from the given distribution.
   * Then these samples are passed to the function to get a distribution of the outputs
   * of the function.
   * These samples are then used to build a Monte Carlo Approximator object which can be used to
   * calculate approximations about the distribution of the function samples.
   *
   * @param n The number of the function samples to generate.
   * @param dist The source distribution.
   * @return std::unique_ptr<MonteCarloApproximator<dim_out>> The Monte Carlo approximator.
   */
  std::unique_ptr<MonteCarloApproximator<dim_out>> mca(unsigned int n, Distribution<dim_inp>* dist);

  /// @brief Return the approximated mean value of the function using n samples from a given distribution.
  Vector<dim_out> mean(unsigned int n, Distribution<dim_inp>* dist);
  /// @brief Return the approximated variance of the function using n samples from a given distribution.
  Vector<dim_out> var(unsigned int n, Distribution<dim_inp>* dist);
};

/// @brief Base class for combining two functions by aggregating their outputs.
template <unsigned int dim_inp, unsigned int dim_out>
class CombinedFunction : public Function<dim_inp, dim_out>
{
public:
  /// @brief Construct a CombinedFunction object from two functions.
  CombinedFunction(const Function<dim_inp, dim_out>& f1, const Function<dim_inp, dim_out>& f2);

  /// @brief Copy a CombinedFunction object.
  CombinedFunction(const CombinedFunction<dim_inp, dim_out>& f);

  /// @brief The first (left) source function.
  const Function<dim_inp, dim_out>& m_f1;
  /// @brief The second (right) source function.
  const Function<dim_inp, dim_out>& m_f2;
};

/// @brief Combined function by summing the outputs of two or more functions.
template <unsigned int dim_inp, unsigned int dim_out>
class CombinedFunctionSum : public CombinedFunction<dim_inp, dim_out>
{
public:
  /// @brief Construct a CombinedFunctionSum object from two functions.
  CombinedFunctionSum(const Function<dim_inp, dim_out>& f1, const Function<dim_inp, dim_out>& f2);

  /// @brief Copy a CombinedFunctionSum object.
  CombinedFunctionSum(const CombinedFunctionSum<dim_inp, dim_out>& f);

  /// @brief Construct a CombinedFunctionSum object from more than two functions recursively.
  template <typename ...Args> CombinedFunctionSum(
    const Function<dim_inp, dim_out>& f1, const Function<dim_inp, dim_out>& f2, const Args&... args)
    : CombinedFunctionSum<dim_inp, dim_out>(f1, CombinedFunctionSum<dim_inp, dim_out>(f2, args...)) {};

  /// @brief Call the combined function by calling the source functions.
  Vector<dim_out> call(const Vector<dim_inp>& x) const override;
};

template <unsigned int dim_inp, unsigned int dim_out>
class CombinedFunctionSub : public CombinedFunction<dim_inp, dim_out> {
public:
  /// @brief Construct a CombinedFunctionSub object from two functions.
  CombinedFunctionSub(const Function<dim_inp, dim_out>& f1, const Function<dim_inp, dim_out>& f2);

  /// @brief Copy a CombinedFunctionSub object.
  CombinedFunctionSub(const CombinedFunctionSub<dim_inp, dim_out>& f);

  /// @brief Construct a CombinedFunctionSub object from more than two functions recursively.
  template <typename ...Args> CombinedFunctionSub(
    const Function<dim_inp, dim_out>& f1, const Function<dim_inp, dim_out>& f2, const Args&... args)
    : CombinedFunctionSub<dim_inp, dim_out>(f1, CombinedFunctionSub<dim_inp, dim_out>(f2, args...)) {};

  /// @brief Call the combined function by calling the source functions.
  Vector<dim_out> call(const Vector<dim_inp>& x) const override;
};

template <unsigned int dim_inp, unsigned int dim_out>
class CombinedFunctionMul : public CombinedFunction<dim_inp, dim_out> {
public:
  /// @brief Construct a CombinedFunctionMul object from two functions.
  CombinedFunctionMul(const Function<dim_inp, dim_out>& f1, const Function<dim_inp, dim_out>& f2);

  /// @brief Copy a CombinedFunctionMul object.
  CombinedFunctionMul(const CombinedFunctionMul<dim_inp, dim_out>& f);

  /// @brief Construct a CombinedFunctionMul object from more than two functions recursively.
  template <typename ...Args> CombinedFunctionMul(
    const Function<dim_inp, dim_out>& f1, const Function<dim_inp, dim_out>& f2, const Args&... args)
    : CombinedFunctionMul<dim_inp, dim_out>(f1, CombinedFunctionMul<dim_inp, dim_out>(f2, args...)) {};

  /// @brief Call the combined function by calling the source functions.
  Vector<dim_out> call(const Vector<dim_inp>& x) const override;
};

template <unsigned int dim_inp, unsigned int dim_out>
class CombinedFunctionDiv : public CombinedFunction<dim_inp, dim_out> {
public:
  /// @brief Construct a CombinedFunctionDiv object from two functions.
  CombinedFunctionDiv(const Function<dim_inp, dim_out>& f1, const Function<dim_inp, dim_out>& f2);

  /// @brief Copy a CombinedFunctionDiv object.
  CombinedFunctionDiv(const CombinedFunctionDiv<dim_inp, dim_out>& f);

  /// @brief Construct a CombinedFunctionDiv object from more than two functions recursively.
  template <typename ...Args> CombinedFunctionDiv(
    const Function<dim_inp, dim_out>& f1, const Function<dim_inp, dim_out>& f2, const Args&... args)
    : CombinedFunctionDiv<dim_inp, dim_out>(f1, CombinedFunctionDiv<dim_inp, dim_out>(f2, args...)) {};

  /// @brief Call the combined function by calling the source functions.
  Vector<dim_out> call(const Vector<dim_inp>& x) const override;
};

/**
 * @brief Functor class for a parameterized scalar multivariate polynomial.
 * The output dimension is always 1.
 * The function \f$ p(u): R^m -> R \f$ is evaluated on a vector as
 * \f[
 *    p(u) = \sum_{k=0}^{K} c_k . pow(u, k),
 * \f]
 * where \f$ K \f$ is the order of the polynomial,
 * \f$ c_k \in R^m \f$ are coefficients of the polynomial,
 * and \f$ pow \f$ is the element-wise power function.
 *
 * @tparam dim_inp The input dimension of the polynomoal.
 */
template <unsigned int dim_inp>
class Polynomial : public Function<dim_inp, 1>
{
public:
  /**
   * @brief Construct a new Polynomial object from an input file.
   * The structure of the file should be the same as the example provided in `tests/data/poly.dat`.
   *
   * - The first line must be "polynomoal".
   * - The second line determines the input dimension, output dimension (1), and the order of the polynomial `K`, correspondingly.
   * - The third line must be empty.
   * - The following `K+1` lines define the coefficients \f$ c_k \f$.
   * @param filepath The path of the file containing the paramters of the function.
   */
  Polynomial(std::string filepath);

  /// @brief Construct a Polynomial object from a matrix of coefficients.
  Polynomial(std::vector<std::vector<double>> &coeffs);

  /// @brief Copy a Polynomial object.
  Polynomial(const Polynomial<dim_inp>&);

  /// @brief Destroy a Polynomial object.
  ~Polynomial() = default;

  /// @brief coefficients of the function.
  std::vector<std::vector<double>> m_coeffs;

  /// @brief call the function.
  Vector<1> call(const Vector<dim_inp>& x) const override;
};

/**
 * @brief Functor class for a parameterized summation over element-wise exponential functions.
 * The output dimension is always 1.
 * The function \f$ f(u): R^m -> R \f$ is evaluated on a vector as
 * \f[
 *    f(u) = \sum_{k=0}^{K} c_k . exp(ku),
 * \f]
 * where \f$ K \f$ is the order of the summation,
 * \f$ c_k \in R^m \f$ are coefficients of the function,
 * and \f$ exp \f$ is the element-wise exponential function.
 *
 * @tparam dim_inp The input dimension of the function.
 */
template <unsigned int dim_inp>
class SumExponential : public Function<dim_inp, 1>
{
public:
  /**
   * @brief Construct a new SumExponential object from an input file.
   * The structure of the file should be the same as the example provided in `tests/data/sumexp.dat`.
   *
   * - The first line must be "sumexponential".
   * - The second line determines the input dimension, output dimension (1), and the order of the summation `K`, correspondingly.
   * - The third line must be empty.
   * - The following `K+1` lines define the coefficients \f$ c_k \f$.
   * @param filepath The path of the file containing the paramters of the function.
   */
  SumExponential(std::string filepath);

  /// @brief Copy a SumExponential object.
  SumExponential(std::vector<std::vector<double>> &coeffs);

  /// @brief Construct a SumExponential object from a matrix of coefficients.
  SumExponential(const SumExponential<dim_inp>&);

  /// @brief Destroy the object.
  ~SumExponential() = default;

  /// @brief The coefficients of the function.
  std::vector<std::vector<double>> m_coeffs;

  /// @brief Call the function.
  Vector<1> call(const Vector<dim_inp>& x) const override;
};

/**
 * @brief Functor class for a parameterized summation over element-wise logarithm functions.
 * The output dimension is always 1.
 * The function \f$ f(u): R^m -> R \f$ is evaluated on a vector as
 * \f[
 *    f(u) = \sum_{k=0}^{K} c_k . log((k+1)u),
 * \f]
 * where \f$ K \f$ is the order of the summation,
 * \f$ c_k \in R^m \f$ are coefficients of the function,
 * and \f$ exp \f$ is the element-wise logarithm function.
 *
 * @tparam dim_inp The input dimension of the function.
 */
template <unsigned int dim_inp>
class SumLogarithm : public Function<dim_inp, 1>
{
public:
  /**
   * @brief Construct a new SumLogarithm object from an input file.
   * The structure of the file should be the same as the example provided in `tests/data/sumlog.dat`.
   *
   * - The first line must be "sumlogarithm".
   * - The second line determines the input dimension, output dimension (1), and the order of the summation `K`, correspondingly.
   * - The third line must be empty.
   * - The following `K+1` lines define the coefficients \f$ c_k \f$.
   * @param filepath The path of the file containing the paramters of the function.
   */
  SumLogarithm(std::string filepath);

  /// @brief Construct a SumLogarithm object from a matrix of coefficients.
  SumLogarithm(std::vector<std::vector<double>> &coeffs);

  /// @brief Copy a SumLogarithm object.
  SumLogarithm(const SumLogarithm<dim_inp>&);

  /// @brief Destroy the object.
  ~SumLogarithm() = default;

  /// @brief The coefficients of the function.
  std::vector<std::vector<double>> m_coeffs;

  /// @brief Call the function.
  Vector<1> call(const Vector<dim_inp>& x) const override;
};

/**
 * @brief Functor class for a parameterized vectorial multivariate polynomial.
 * The function \f$ p(u): R^m -> R^n \f$ is evaluated on a vector as
 * \f[
 *    p(u) = b + \sum_{k=1}^{K} A_k^{m, n} pow(u, k),
 * \f]
 * where \f$ K \f$ is the order of the polynomial,
 * \f$ A_k \in R^{m, n} \f$ are coefficients of the function,
 * \f$ b \in R^n \f$ is the biase vector,
 * and \f$ pow \f$ is the element-wise power function.
 *
 * @tparam dim_inp The input dimension of the function.
 * @tparam dim_out The input dimension of the function.
 * @tparam order The order of the polynomial.
 */
template <unsigned int dim_inp, unsigned int dim_out, unsigned int order>
class MultivariatePolynomial : public Function<dim_inp, dim_out>
{
public:
  /**
   * @brief Construct a new MultivariatePolynomial object from an input file.
   * The structure of the file should be the same as the example provided in `tests/data/multipoly.dat`.
   *
   * - The first line must be "multipolynomial".
   * - The second line determines the input dimension, output dimension, and the order of the polynomial `K`, correspondingly.
   * - The third line must be empty.
   * - The fourth line defines the bias vector.
   * - The fifth line must be empty.
   * - The following `K` series of `dim_out` lines define the `K` coefficient matrices.
   * @param filepath The path of the file containing the paramters of the function.
   */
  MultivariatePolynomial(std::string filepath);

  /// @brief Construct a MultivariatePolynomial object from a matrix of coefficients.
  MultivariatePolynomial(std::vector<std::vector<std::vector<double>>> &weights, std::vector<double> &biases);

  /// @brief Copy a MultivariatePolynomial object.
  MultivariatePolynomial(const MultivariatePolynomial<dim_inp, dim_out, order>&);

  /// @brief Destroy the object.
  ~MultivariatePolynomial() = default;

  /// @brief The weight matrices of the function.
  std::vector<std::vector<std::vector<double>>> m_weights;

  /// @brief The bias vector of the function.
  std::vector<double> m_biases;

  /// @brief Call the function.
  virtual Vector<dim_out> call(const Vector<dim_inp>& x) const override;
};


/**
 * @brief Functor class for a parameterized vectorial multivariate linear transformation.
 * The function \f$ L(u): R^m -> R^n \f$ is evaluated on a vector as
 * \f[
 *    L(u) = b + A^{m, n} u,
 * \f]
 * where \f$ A \in R^{m, n} \f$ is the weight matrix and \f$ b \in R^n \f$ is the biase vector.
 *
 * @tparam dim_inp The input dimension of the function.
 * @tparam dim_out The input dimension of the function.
 */
template <unsigned int dim_inp, unsigned int dim_out>
class Linear : public MultivariatePolynomial<dim_inp, dim_out, 1>
{
public:
  /**
   * @brief Construct a new Linear object from an input file.
   * The structure of the file should be the same as the example provided in `tests/data/linear.dat`.
   *
   * - The first line must be "linear".
   * - The second line determines the input dimension, output dimension, and the order of the polynomial (1), correspondingly.
   * - The third line must be empty.
   * - The fourth line defines the bias vector.
   * - The fifth line must be empty.
   * - The following `dim_out` lines define the weight matrice.
   * @param filepath The path of the file containing the paramters of the function.
   */
  Linear(std::string filepath);

  /// @brief Construct a Polynomial object from a matrix of coefficients.
  Linear(std::vector<std::vector<double>> &weights, std::vector<double> &biases);

  /// @brief Copy a Polynomial object.
  Linear(const Linear<dim_inp, dim_out>&);

  /// @brief Destroy the object.
  ~Linear() = default;
};

#include "functions.tpp"

#endif
