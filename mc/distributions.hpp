#ifndef MC_DISTRIBUTIONS_HPP
#define MC_DISTRIBUTIONS_HPP

#include <cstdlib>
#include <vector>


class Distribution
{
public:
  Distribution(const unsigned int dim);
  ~Distribution();
  std::vector<std::vector<double>>* samples(const int n = 1);

private:
  virtual double sample_dim(const int d) = 0;
  const int m_dim;
};

class Uniform:
  public Distribution
{
public:
  // Constructors
  Uniform(const unsigned int dim, std::vector<double>& lower, std::vector<double>& upper);
  Uniform(const double& lower, const double& upper);
  // Destructor
  ~Uniform();

  std::vector<double> m_lower;
  std::vector<double> m_upper;

private:
  double sample_dim(const int d) override;
};

class Normal:
  public Distribution
{
public:
  Normal(const unsigned int dim, std::vector<double>& mean, std::vector<std::vector<double>>& covariance);
  Normal(const double mean, const double variance);
  ~Normal();

  std::vector<double> m_mean;
  std::vector<std::vector<double>> m_covariance;

private:
  double sample_dim(const int d) override;
};

#endif
