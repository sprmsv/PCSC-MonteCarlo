#include "distributions.hpp"
#include "mathutils.hpp"

#ifndef RAND_SEED
// TODO: Set seed based on time
#define RAND_SEED 42
#endif


template<unsigned int dim>
Distribution<dim>::Distribution() {
    srand(RAND_SEED);
  }

template<unsigned int dim>
Distribution<dim>::~Distribution() {}

template<unsigned int dim>
std::vector<Vector<dim>>* Distribution<dim>::samples(const int n) {
  // TODO: Keep track of the samples and destroy them!!
  std::vector<Vector<dim>>* samples = new std::vector<Vector<dim>>(n, Vector<dim>());
  for (int i = 0; i < n; i++){
    Vector<dim>& s = (*samples)[i];
    for (int j = 0; j < dim; j++){
      s[j] = this->sample_dim(j);
    }
  }
  return samples;
}

template<unsigned int dim>
Uniform<dim>::Uniform(std::vector<double>& lower, std::vector<double>& upper)
  : Distribution<dim>(), m_lower(lower), m_upper(upper) {
    // TODO: Assert the dimension of the domain bounds
    // TODO: Assert upper is larger than higher
  }

template<unsigned int dim>
Uniform<dim>::Uniform(const double& lower, const double& upper)
  : Distribution<dim>() {
    // TODO: Assert upper is larger than higher

    // TODO: Improve instantiation
    m_lower.resize(dim);
    std::fill(m_lower.begin(), m_lower.end(), lower);
    m_upper.resize(dim);
    std::fill(m_upper.begin(), m_upper.end(), upper);
  }

template<unsigned int dim>
Uniform<dim>::~Uniform() {}

template<unsigned int dim>
double Uniform<dim>::sample_dim(const int d) {
  double z = (double)rand() / (double)RAND_MAX;
  double x = (m_upper[d] - m_lower[d]) * z + m_lower[d];
  return x;
}

template<unsigned int dim>
Normal<dim>::Normal(std::vector<double>& mean, std::vector<std::vector<double>>& covariance)
  : Distribution<dim>(), m_mean(mean), m_covariance(covariance) {
    // TODO: Assert that the dimensions of the inputs match
}

template<unsigned int dim>
Normal<dim>::Normal(std::vector<double>& mean, std::vector<double>& covariance)
  : Distribution<dim>(), m_mean(mean) {
    // TODO: Assert that the dimensions of the inputs match

    // Instantiate the covariance matrix
    m_covariance.resize(dim);
    for (auto& vec : m_covariance) {
      vec.resize(dim);
      std::fill(vec.begin(), vec.end(), 0.);
    }
    for (int i=0; i<dim; ++i) {
      m_covariance[i][i] = covariance[i];
    }
}

template<unsigned int dim>
Normal<dim>::Normal(const double& mean, const double& variance)
  : Distribution<dim>() {
    // Instantiate the mean vector
    m_mean.resize(dim);
    std::fill(m_mean.begin(), m_mean.end(), mean);
    // Instantiate the covariance matrix
    m_covariance.resize(dim);
    for (auto& vec : m_covariance) {
      vec.resize(dim);
      std::fill(vec.begin(), vec.end(), variance);
    }
}

template<unsigned int dim>
Normal<dim>::~Normal() {}

template<unsigned int dim>
double Normal<dim>::sample_dim(const int d) {
  // NOTE: Covariances are ignored, only variances are taken into account
  // NOTE: The math behind the erfinv becomes complicated
  double u = (double)rand() / (double)RAND_MAX;
  double z = sqrt(2.) * erfinv(2. * u - 1.);
  double x = sqrt(m_covariance[d][d]) * z + m_mean[d];
  return x;
}
