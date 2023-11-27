#include "distributions.hpp"
#include "mathutils.hpp"

template <unsigned int dim> Normal<dim>::Normal(Eigen::Matrix<double, dim, 1>& mean, Eigen::Matrix<double, dim, dim>& covariance)
  : Distribution(dim), m_mean(mean), m_covariance(covariance) {
    // TODO: Assert that the dimensions of the inputs match
    // TODO: Reserve the matrix allocations
  }
template <unsigned int dim> Normal<dim>::Normal(const double mean, const double variance)
  : Distribution(1), m_mean(mean), m_covariance(variance) {
    // TODO: Assert dim == 1
    // TODO: Reserve the matrix allocations
  }

template <unsigned int dim> Normal<dim>::~Normal() {}

template <unsigned int dim> double Normal<dim>::sample_dim(const int d) {
  // NOTE: Covariances are ignored, only variances are taken into account
  double u = (double)rand() / (double)RAND_MAX;
  double z = erfinv(2 * u - 1);
  double x = sqrt(m_covariance(d, d)) * z + m_mean(d);
  return x;
}
