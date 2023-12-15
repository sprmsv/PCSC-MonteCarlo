#include "distributions.hpp"


template<unsigned int dim>
Distribution<dim>::Distribution()
{
  srand(RAND_SEED);
}

template<unsigned int dim>
Distribution<dim>::~Distribution() {}

template<unsigned int dim>
std::shared_ptr<std::vector<Vector<dim>>> Distribution<dim>::samples(const int n)
{
  std::shared_ptr<std::vector<Vector<dim>>> samples (new std::vector<Vector<dim>>(n));
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
Uniform<dim>::Uniform(std::vector<double>& lower, std::vector<double>& upper):
  Distribution<dim>(),
  m_lower(lower),
  m_upper(upper)
{
    // Check that the dimension of the bounds are valid
    if ((m_lower.size() != dim) || (m_upper.size() != dim)) {
      std::string msg = "The provided bounds must have dimension " + std::to_string(dim) + " .";
      throw InvalidInputException(msg);
    }

    // Check that the lower bound is indeed lower than the upper bound for all dimensions
    for (int d = 0; d < dim; d++) {
      if(m_lower[d] >= m_upper[d]) {
        throw InvalidInputException("The lower bound must be smaller than the upper bound.");
      }
    }
}

template<unsigned int dim>
Uniform<dim>::Uniform(const double& lower, const double& upper):
  Distribution<dim>(),
  m_lower(dim, lower),
  m_upper(dim, upper)
{
  // Check that the lower bound is indeed lower than the upper bound
  if (lower >= upper) {
    throw InvalidInputException("The lower bound must be smaller than the upper bound.");
  }
}

template<unsigned int dim>
Uniform<dim>::~Uniform() {}

template<unsigned int dim>
double Uniform<dim>::sample_dim(const int d)
{
  if (d < 0 || d >= dim) {
    std::string msg = "Dimension " + std::to_string(d) +
    " is invakid for Distribution<" + std::to_string(dim) + ">.";
    throw InvalidInputException(msg);
  }
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
  if ((m_mean.size() != dim) || (m_covariance.size() != dim)) {
    throw InvalidArgumentException("Mean and covariance must have the same dimension of the distribution.");
  }

  // Check that the covariance matrix is symmetric
  for (int d1 = 0; d1 < dim; d1++)
  {
    for (int d2 = 0; d2 < dim; d2++)
    {
      if (m_covariance[d1][d2] != m_covariance[d2][d1]) {
        throw InvalidArgumentException("The covariance matrix must be symmetric.");
      }
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
  if ((m_mean.size() != dim) || (m_covariance.size() != dim)) {
    throw InvalidInputException("Mean and covariance vectors must have the same dimension as the distribution.");
  }

  // Check that the variance is positive
  for (int d = 0; d < dim; d++) {
    if (variance[d] <= 0.0) {
      throw InvalidInputException("Variance must be positive.");
    }
  }

  // Set the covariance matrix to be diagonal with the variance on the diagonal
  for (int d = 0; d < dim; d++) {
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
  if (variance <= 0.0) {
    throw InvalidInputException("Variance must be positive.");
  }

  // Set the covariance matrix to be diagonal with the variance on the diagonal
  for (int d = 0; d < dim; d++)
  {
    m_covariance[d][d] = variance;
  }
}

template<unsigned int dim>
Normal<dim>::~Normal() {}

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
  if (d < 0 || d >= dim) {
    std::string msg = "Dimension " + std::to_string(d) +
    " is invakid for Distribution<" + std::to_string(dim) + ">.";
    throw InvalidInputException(msg);
  }

  double u = (double)rand() / RAND_MAX;
  double z = sqrt(2.) * erfinv(2. * u - 1.);
  return m_mean[d] + sqrt(m_covariance[d][d]) * z;
}
