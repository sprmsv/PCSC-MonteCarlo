#ifndef MC_SAMPLER_HPP
#define MC_SAMPLER_HPP

#include "distributions.hpp"
#include "vector.hpp"

#include <Eigen/Core>

#include <functional>
#include <string>


/**
 * @brief Class for calculating Monte Carlo Approximations.
 * This class estimates the statistical moments from a set of samples
 * of a distribution.
 *
 * The k-th raw moment of a scalar random variable is approximated as:
 * \f[
 *      E_{x \sim X}(x^k) \simeq \frac{1}{N} \sum_{i=1}^{N}x_i^k.
 * \f]
 *
 * The k-th central moment of a scalar random variable is approximated as:
 * \f[
 *      E_{x \sim X}((x-\mu)^k) \simeq \frac{1}{N} \sum_{i=1}^{N}(x_i-\mu)^k,
 * \f]
 * where \f$ \mu \f$ is the mean of the samples.
 *
 * The k-th standardized moment of a scalar random variable is approximated as:
 * \f[
 *      E_{x \sim X}((\frac{x-\mu}{\sigma})^k) \simeq \frac{1}{N} \sum_{i=1}^{N}((\frac{x_i-\mu}{\sigma})^k,
 * \f]
 * where \f$ \mu \f$ and \f$ \sigma^2 \f$ are the mean and variance of the samples, respectively.
 *
 * The moments of vectorial distributions are calculated similarly in each dimension.
 *
 * @tparam dim The dimension of the samples.
 */
template <unsigned int dim = 1>
class MonteCarloApproximator
{
public:
  /// @brief Construct a MonteCarloApproximator object.
  MonteCarloApproximator() = default;

  /// @brief Construct a MonteCarloApproximator object from a set of samples.
  MonteCarloApproximator(std::shared_ptr<std::vector<Vector<dim>>> samples);

  /// @brief Destroy the object.
  ~MonteCarloApproximator();

  /// @brief Return the underlying data.
  std::vector<Vector<dim>>& data();

  /**
   * @brief Calculate an approximated moment of the samples.
   * @param orders The moment order in each dimension.
   * @param mode The mode of the moment among "raw", "central", and "standardized".
   * @return Eigen::VectorXd The vector of moments along each dimension.
   */
  Eigen::VectorXd moment(std::vector<unsigned int> &orders, std::string mode);

  /**
   * @brief Calculate an approximated moment of the samples.
   * @param order The moment order in all dimensions.
   * @param mode The mode of the moment among "raw", "central", and "standardized".
   * @return Eigen::VectorXd The vector of moments along each dimension.
   */
  Eigen::VectorXd moment(unsigned int order, std::string mode);

  /// @brief Calculate the first raw moment (mean) of the samples.
  Eigen::VectorXd mean();
  /// @brief Calculate the second central moment (variance) of the samples.
  Eigen::VectorXd var();
  /// @brief Calculate the standard deviation of the samples.
  Eigen::VectorXd std();
  /// @brief Calculate the third standardized moment (skewness) of the samples.
  Eigen::VectorXd skewness();
  /// @brief Calculate the fourth standardized moment (kurtosis) of the samples.
  Eigen::VectorXd kurtosis();
  /// @brief Calculate the fifth standardized moment (hyperskewness) of the samples.
  Eigen::VectorXd hyperskewness();
  /// @brief Calculate the sixth standardized moment (hypertailedness) of the samples.
  Eigen::VectorXd hypertailedness();

private:
  /// @brief Calculate the moment in one dimension.
  double moment_dim(unsigned int order, std::string mode, const Eigen::VectorXd& samples_dim);

  /// @brief The samples.
  std::shared_ptr<std::vector<Vector<dim>>> m_samples;
};

#include "sampler.tpp"

#endif
