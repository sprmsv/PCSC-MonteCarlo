#ifndef MC_DISTRIBUTIONS_HPP
#define MC_DISTRIBUTIONS_HPP

#include <cstdlib>
#include <vector>
#include <Eigen/Core>

typedef std::vector<std::vector<double>> Matrix;

class Distribution
{
public:
  Distribution(const unsigned int dim);
  ~Distribution();
  Matrix* samples(const int n = 1);

private:
  virtual double sample_dim(const int d) = 0;
  const int m_dim;
};

class Uniform:
  public Distribution
{
public:
  // Constructors
  Uniform(const unsigned int dim, const double* lower, const double* upper);
  Uniform(const double& lower, const double& upper);
  // Destructor
  ~Uniform();
  const double* m_lower;
  const double* m_upper;

private:
  double sample_dim(const int d) override;
};

template <unsigned int dim = 1>
class Normal:
  public Distribution
{
public:
  Normal(Eigen::Matrix<double, dim, 1>& mean, Eigen::Matrix<double, dim, dim>& covariance);
  Normal(const double mean, const double variance);
  ~Normal();

  Eigen::Matrix<double, dim, 1> m_mean;
  Eigen::Matrix<double, dim, dim> m_covariance;

private:
  double sample_dim(const int d) override;
};

#include "distributions.tpp"

#endif
