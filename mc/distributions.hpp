#include <cstdlib>
#include <vector>

#ifndef MC_DISTRIBUTIONS_HPP
#define MC_DISTRIBUTIONS_HPP

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

class Normal:
  public Distribution
{
public:
  Normal(const unsigned int dim);
  ~Normal();
  // virtual double pdf(double x[dim]) = 0;
  // virtual double cdf(double x[dim]) = 0;
  // double* icdf(double);
};

class Uniform:
  public Distribution
{
public:
  Uniform(const unsigned int dim, const double* lower, const double* upper);
  Uniform(const unsigned int dim, double lower, double upper);
  ~Uniform();
  const double* m_lower;
  const double* m_upper;

private:
  double sample_dim(const int d) override;
};

// Include separated implementations
#include "distributions.tpp"

#endif
