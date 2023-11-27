#include "distributions.hpp"

#ifndef RAND_SEED
// TODO: Set seed based on time
#define RAND_SEED 42
#endif

Distribution::Distribution(const unsigned int dim)
  : m_dim(dim) {
    srand(RAND_SEED);
  }

Distribution::~Distribution() {}

// TODO: Change to Eigen matrix
// TODO: Specialize for the 1D case
Matrix* Distribution::samples(const int n) {
  Matrix* samples = new Matrix(n, std::vector<double>(this->m_dim));
  for (int i = 0; i < n; i++){
    std::vector<double>& s = (*samples)[i];
    for (int j = 0; j < this->m_dim; j++){
      s[j] = this->sample_dim(j);
    }
  }
  return samples;
}

Normal::Normal(const unsigned int dim)
  : Distribution(dim) {}

Normal::~Normal() {}


Uniform::Uniform(const unsigned int dim, const double* lower, const double* upper)
  : Distribution(dim), m_lower(lower), m_upper(upper) {
    // TODO: Assert the dimension of the domain bounds
    // TODO: Assert upper is larger than higher
  }

Uniform::Uniform(const double& lower, const double& upper)
  : Distribution(1), m_lower(&lower), m_upper(&upper) {
    // TODO: Assert upper is larger than higher
  }

Uniform::~Uniform() {}

double Uniform::sample_dim(const int d) {
  double s = (double)rand() / (double)RAND_MAX;
  s *= m_upper[d] - m_lower[d];
  s += m_lower[d];
  return s;
}
