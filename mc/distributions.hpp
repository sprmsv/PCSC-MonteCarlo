#ifndef MC_DISTRIBUTIONS_HPP
#define MC_DISTRIBUTIONS_HPP

#include "mathutils.hpp"
#include "exceptions.hpp"
#include "vector.hpp"

#include <cstdlib>
#include <vector>
#include <memory>
#include <ctime>


// TODO: Can be a user-input
// We can simply change it to time(0) if we do not want reproducibility

#ifndef RAND_SEED
/// @brief Seed for random number generation.
#define RAND_SEED 42
#endif


/**
 * @brief Abstract class for a distribution.
 * This class wraps the common members of a distribution.
 * @tparam dim The dimension of the samples of the distribution.
 */
template<unsigned int dim>
class Distribution
{
public:
  /// @brief Constructs a distribution object.
  Distribution();

  /// @brief Destroys the distribution object.
  virtual ~Distribution();

  /**
   * @brief Generates n samples from the distribution.
   * The samples are drawn from each dimension one by one randomly.
   * @param n The number of the samples.
   * @return std::shared_ptr<std::vector<Vector<dim>>> A pointer to the generated samples.
   */
  std::shared_ptr<std::vector<Vector<dim>>> samples(const int n = 1);

  /// @brief Returns the mean of the distribution.
  virtual Vector<dim> mean() = 0;
  /// @brief Returns the variance of the distribution.
  virtual Vector<dim> var() = 0;

private:
  /**
   * @brief Draws a random sample in the specified dimension.
   * The parameters in each dimension might be different.
   * This function draws a random sample by reading the parameters
   * of the corresponding dimension.
   * @param d The desired dimension of the sample.
   * @return double An element of a random sample.
   */
  virtual double sample_dim(const int d) = 0;
};

/**
 * @brief Multidimensional uniform distribution.
 * @tparam dim Dimension of the distribution.
 */
template<unsigned int dim>
class Uniform:
  public Distribution<dim>
{
public:
  /**
   * @brief Construct a new Uniform object.
   * @param lower The lower bound on each dimension.
   * @param upper The upper bound on each dimension.
   */
  Uniform(std::vector<double>& lower, std::vector<double>& upper);

  /**
   * @brief Construct a new Uniform object with the same bounds across dimensions.
   * @param lower The lower bound of all dimensions.
   * @param upper The upper bound of all dimensions.
   */
  Uniform(const double& lower, const double& upper);

  /// @brief Destroy the Uniform object.
  ~Uniform();

  /// @brief Returns the mean value of the Uniform distribution.
  virtual Vector<dim> mean() override;
  /// @brief Returns the variance of the Uniform distribution.
  virtual Vector<dim> var() override;

private:
  /// @brief Returns an element of a random sample from the uniform distribution.
  double sample_dim(const int d) override;

  /// @brief The lower bounds.
  std::vector<double> m_lower;
  /// @brief The upper bounds.
  std::vector<double> m_upper;
};

/**
 * @brief Multidimensional normal distribution.
 * @tparam dim Dimension of the distribution.
 */
template<unsigned int dim>
class Normal:
  public Distribution<dim>
{
public:
  /**
   * @brief Construct a new Normal object.
   * @param mean The mean value on each dimension.
   * @param covariance The covariance matrix of the normal distribution.
   */
  Normal(std::vector<double>& mean, std::vector<std::vector<double>>& covariance);

  /**
   * @brief Construct a new Normal object without covariances.
   * This constructor assumes that the covariance matrix is diagonal.
   * @param mean The mean value on each dimension.
   * @param variance The diagonal of the covariance matrix.
   */
  Normal(std::vector<double>& mean, std::vector<double>& variance);

  /**
   * @brief Construct a new Normal object with constant mean and variances.
   * This constructor assumes that the covariance matrix is diagonal.
   * This constructor assumes that the variance is constant across dimensions.
   * This constructor assumes that mean value is constant across dimensions.
   * @param mean The constant mean value across all dimensions.
   * @param variance The constant variance across all dimensions.
   */
  Normal(const double& mean, const double& variance);

  /// @brief Destroys the Normal object.
  ~Normal();

  /// @brief Returns the mean value of the distribution.
  virtual Vector<dim> mean() override;
  /// @return Returns the variance of the distribution.
  virtual Vector<dim> var() override;

private:
  /**
   * @brief Returns an element of a random sample from the uniform distribution.
   * This is done by applying the inverse transform sampling method.
   * Assuming that \f$ z \sim N(0, 1) \f$ is a random sample from the standard normal distribution,
   * a sample \f$ u \sim U([0, 1]) \f$ is randomly drawn from the unfiform distribution.
   * \f$ z \f$ is then calculated by \f$ \sqrt{2} {erfinv}(2u-1) \f$, where \f$ {erfinv} \f$
   * is the inverse error function. The return value is obtained by mapping \f$ z \f$ to the current
   * normal distribution using the mean and the standard deviation of the desired dimension.
   * @param d The dimension of the sample element.
   * @return double the sample element.
   */
  double sample_dim(const int d) override;

  /// @brief The mean value of each dimension.
  std::vector<double> m_mean;

  /// @brief The covariane matrix.
  std::vector<std::vector<double>> m_covariance;
};

#include "distributions.tpp"

#endif
