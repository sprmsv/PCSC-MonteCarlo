#include "distributions.hpp"
#include "mathutils.hpp"

#ifndef RAND_SEED
// TODO: Set seed based on time
#define RAND_SEED 42
#endif

Distribution::Distribution(const unsigned int dim)
  : m_dim(dim) {
    srand(RAND_SEED);
  }

Distribution::~Distribution() {}

std::vector<std::vector<double>>* Distribution::samples(const int n) {
  std::vector<std::vector<double>>* samples = new std::vector<std::vector<double>>(n, std::vector<double>(this->m_dim));
  for (int i = 0; i < n; i++){
    std::vector<double>& s = (*samples)[i];
    for (int j = 0; j < this->m_dim; j++){
      s[j] = this->sample_dim(j);
    }
  }
  return samples;
}

Uniform::Uniform(const unsigned int dim, std::vector<double>& lower, std::vector<double>& upper)
  : Distribution(dim), m_lower(lower), m_upper(upper) {
    // TODO: Assert the dimension of the domain bounds
    // TODO: Assert upper is larger than higher
  }

Uniform::Uniform(const double& lower, const double& upper)
  : Distribution(1) {
    // TODO: Assert upper is larger than higher

    // TODO: Improve instantiation
    m_lower.resize(1);
    m_lower[0] = lower;
    m_upper.resize(1);
    m_upper[0] = lower;
  }

Uniform::~Uniform() {}

double Uniform::sample_dim(const int d) {
  double z = (double)rand() / (double)RAND_MAX;
  double x = (m_upper[d] - m_lower[d]) * z + m_lower[d];
  return x;
}

Normal::Normal(const unsigned int dim, std::vector<double>& mean, std::vector<std::vector<double>>& covariance)
  : Distribution(dim), m_mean(mean), m_covariance(covariance) {
    // TODO: Assert that the dimensions of the inputs match
}

Normal::Normal(const unsigned int dim, std::vector<double>& mean, std::vector<double>& covariance)
  : Distribution(dim), m_mean(mean) {
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

Normal::Normal(const double& mean, const double& variance)
  : Distribution(1) {
    // Instantiate the mean vector
    m_mean.resize(1);
    m_mean[0] = mean;
    // Instantiate the covariance matrix
    m_covariance.resize(1);
    m_covariance[0].resize(1);
    m_covariance[0][0] = variance;
}

Normal::~Normal() {}

double Normal::sample_dim(const int d) {
  // NOTE: Covariances are ignored, only variances are taken into account
  // NOTE: The math behind the erfinv becomes complicated
  double u = (double)rand() / (double)RAND_MAX;
  double z = erfinv(2 * u - 1);
  double x = sqrt(m_covariance[d][d]) * z + m_mean[d];
  return x;
}
