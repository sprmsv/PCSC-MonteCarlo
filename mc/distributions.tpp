#include "distributions.hpp"
#include "mathutils.hpp"

#include <chrono>

#ifndef RAND_SEED
#define RAND_SEED 42
#endif

template<unsigned int dim>
Distribution<dim>::Distribution()
{
  srand(RAND_SEED);
}

template<unsigned int dim>
Distribution<dim>::~Distribution()
{
}

template<unsigned int dim>
std::vector<Vector<dim>>* Distribution<dim>::samples(const int n)
{
  // TODO - this is a memory leak
  std::vector<Vector<dim>>* samples = new std::vector<Vector<dim>>(n);
  for (int i = 0; i < n; i++)
  {
    Vector<dim>& sample = (*samples)[i];

    for (int d = 0; d < dim; d++)
    {
      sample[d] = sample_dim(d);
    }
  }
  return samples;
}

template<unsigned int dim>
void Distribution<dim>::set_time_seed()
{
  auto currentTime = std::chrono::high_resolution_clock::now();
  auto nano = currentTime.time_since_epoch();

  srand(static_cast<unsigned int>(nano.count()));
}

template<unsigned int dim>
Uniform<dim>::Uniform(std::vector<double>& lower, std::vector<double>& upper):
  Distribution<dim>(),
  m_lower(lower),
  m_upper(upper)
{
    // Check that the dimension of the bounds are valid
    assert((m_lower.size() == dim) && (m_upper.size() == dim));

    // Check that the lower bound is indeed lower than the upper bound for all dimensions
    for (int d = 0; d < dim; d++)
    {
      assert(m_lower[d] < m_upper[d]);
    }
}

template<unsigned int dim>
Uniform<dim>::Uniform(const double& lower, const double& upper):
  Distribution<dim>(),
  m_lower(dim, lower),
  m_upper(dim, upper)
{
    // Check that the lower bound is indeed lower than the upper bound
    assert(lower < upper);
}

template<unsigned int dim>
Uniform<dim>::~Uniform()
{
}

template<unsigned int dim>
double Uniform<dim>::sample_dim(const int d)
{
  // Check that the dimension matches
  assert((d >= 0) && (d < dim));
  return m_lower[d] + (m_upper[d] - m_lower[d]) * (double)rand() / RAND_MAX;
}

template<unsigned int dim>
Vector<dim> Uniform<dim>::mean()
{
  Vector<dim> mean;
  for (int d = 0; d < dim; d++)
  {
    mean[d] = (m_lower[d] + m_upper[d]) / 2.0;
  }
  return mean;
}

template<unsigned int dim>
Vector<dim> Uniform<dim>::var()
{
  Vector<dim> var;
  for (int d = 0; d < dim; d++)
  {
    var[d] = (m_upper[d] - m_lower[d]) * (m_upper[d] - m_lower[d]) / 12.0;
  }
  return var;
}

template<unsigned int dim>
Normal<dim>::Normal(std::vector<double>& mean, std::vector<std::vector<double>>& covariance):
  Distribution<dim>(),
  m_mean(mean),
  m_covariance(covariance)
{
  // Check that the dimension of the mean and covariance are valid
  assert((m_mean.size() == dim) && (m_covariance.size() == dim));

  // Check that the covariance matrix is symmetric
  for (int d1 = 0; d1 < dim; d1++)
  {
    for (int d2 = 0; d2 < dim; d2++)
    {
      assert(m_covariance[d1][d2] == m_covariance[d2][d1]);
    }
  }
}

template<unsigned int dim>
Normal<dim>::Normal(std::vector<double>& mean, std::vector<double>& variance):
  Distribution<dim>(),
  m_mean(mean),
  m_covariance(dim, std::vector<double>(dim, 0.0))
{
  // Check that the dimension of the mean and variance are valid
  assert((m_mean.size() == dim) && (m_covariance.size() == dim));

  // Check that the variance is positive
  for (int d = 0; d < dim; d++)
  {
    assert(variance[d] > 0.0);
  }

  // Set the covariance matrix to be diagonal with the variance on the diagonal
  for (int d = 0; d < dim; d++)
  {
    m_covariance[d][d] = variance[d];
  }
}

template<unsigned int dim>
Normal<dim>::Normal(const double& mean, const double& variance):
  Distribution<dim>(),
  m_mean(dim, mean),
  m_covariance(dim, std::vector<double>(dim, 0.0))
{
  // Check that the variance is positive
  assert(variance > 0.0);

  // Set the covariance matrix to be diagonal with the variance on the diagonal
  for (int d = 0; d < dim; d++)
  {
    m_covariance[d][d] = variance;
  }
}

template<unsigned int dim>
Normal<dim>::~Normal()
{
}

template<unsigned int dim>
Vector<dim> Normal<dim>::mean()
{
  Vector<dim> mean = m_mean;
  return mean;
}

template<unsigned int dim>
Vector<dim> Normal<dim>::var()
{
  Vector<dim> var;
  for (int d = 0; d < dim; d++)
  {
    var[d] = m_covariance[d][d];
  }
  return var;
}

template<unsigned int dim>
double Normal<dim>::sample_dim(const int d)
{
    // Check that the dimension matches
    assert((d >= 0) && (d < dim));

    double u = (double)rand() / RAND_MAX;
    double z = sqrt(2.) * erfinv(2. * u - 1.);
    return m_mean[d] + sqrt(m_covariance[d][d]) * z;
}

