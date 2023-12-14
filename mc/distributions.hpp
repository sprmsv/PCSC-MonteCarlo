#ifndef MC_DISTRIBUTIONS_HPP
#define MC_DISTRIBUTIONS_HPP

#include "mathutils.hpp"
#include "exceptions.hpp"
#include "vector.hpp"

#include <cstdlib>
#include <vector>
#include <memory>
#include <ctime>


template<unsigned int dim>
class Distribution
{
public:
  Distribution();
  virtual ~Distribution();
  std::shared_ptr<std::vector<Vector<dim>>> samples(const int n = 1);

  virtual Vector<dim> mean() = 0;
  virtual Vector<dim> var() = 0;
private:
  virtual double sample_dim(const int d) = 0;
};

template<unsigned int dim>
class Uniform:
  public Distribution<dim>
{
public:
  // Constructors
  Uniform(std::vector<double>& lower, std::vector<double>& upper);
  Uniform(const double& lower, const double& upper);
  // Destructor
  ~Uniform();

  std::vector<double> m_lower;
  std::vector<double> m_upper;

  virtual Vector<dim> mean() override;
  virtual Vector<dim> var() override;
private:
  double sample_dim(const int d) override;
};

template<unsigned int dim>
class Normal:
  public Distribution<dim>
{
public:
  Normal(std::vector<double>& mean, std::vector<std::vector<double>>& covariance);
  Normal(std::vector<double>& mean, std::vector<double>& variance);
  Normal(const double& mean, const double& variance);
  ~Normal();
  
  std::vector<double> m_mean;
  std::vector<std::vector<double>> m_covariance;

  virtual Vector<dim> mean() override;
  virtual Vector<dim> var() override;
private:
  double sample_dim(const int d) override;
};

#include "distributions.tpp"

#endif
