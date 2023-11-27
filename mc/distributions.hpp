#include <cstdlib>
#include <vector>

#ifndef MC_DISTRIBUTIONS_HPP
#define MC_DISTRIBUTIONS_HPP

typedef std::vector<std::vector<double>> Matrix;

template<int dim> class Distribution
{
public:
  Distribution();
  ~Distribution();
  Matrix* samples(const int n = 1);

private:
  virtual double sample_dim(const int d) = 0;
  const int m_dim;
};

template<int dim = 1> class Normal:
  public Distribution<dim>
{
public:
  Normal();
  ~Normal();
  // virtual double pdf(double x[dim]) = 0;
  // virtual double cdf(double x[dim]) = 0;
  // double* icdf(double);
};

template<int dim = 1> class Uniform:
  public Distribution<dim>
{
public:
  Uniform(const double* lower, const double* upper);
  ~Uniform();
  const double* m_lower;
  const double* m_upper;

private:
  double sample_dim(const int d) override;
};

// Include separated implementations
#include "distributions.tpp"

#endif
