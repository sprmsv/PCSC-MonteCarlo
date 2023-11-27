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
  // virtual double pdf(double x[dim]) = 0;
  // virtual double cdf(double x[dim]) = 0;
  // double* icdf(double);
  virtual Matrix* sample(const int n = 1) = 0;

// private:
  const int m_dim;
};

template<int dim = 1> class Normal:
  public Distribution<dim>
{
public:
  Normal();
  ~Normal();
};

template<int dim = 1> class Uniform:
  public Distribution<dim>
{
public:
  Uniform();
  ~Uniform();
  virtual Matrix* sample(const int n = 1) override;
};

// Include separated implementations
#include "distributions.tpp"

#endif
