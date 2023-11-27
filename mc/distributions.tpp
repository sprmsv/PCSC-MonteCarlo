#ifndef MC_DISTRIBUTIONS_TPP
#define MC_DISTRIBUTIONS_TPP

#define RAND_SEED 42


template <int dim> Distribution<dim>::Distribution()
  : m_dim(dim) {
    srand(RAND_SEED);
  }

template <int dim> Distribution<dim>::~Distribution() {}

// TODO: Change to Eigen matrix
// TODO: Specialize for the 1D case
template <int dim> Matrix* Distribution<dim>::samples(const int n) {
  Matrix* samples = new Matrix(n, std::vector<double>(this->m_dim));
  for (int i = 0; i < n; i++){
    std::vector<double>& s = (*samples)[i];
    for (int j = 0; j < this->m_dim; j++){
      s[j] = this->sample_dim(j);
    }
  }
  return samples;
}

template <int dim> Normal<dim>::Normal()
  : Distribution<dim>() {}

template <int dim> Normal<dim>::~Normal() {}


template <int dim> Uniform<dim>::Uniform(const double* lower, const double* upper)
  : Distribution<dim>(), m_lower(lower), m_upper(upper) {
    // TODO: Assert the dimension of the domain bounds
    // TODO: Assert upper is larger than higher
  }

template <int dim> Uniform<dim>::~Uniform() {}

template <int dim> double Uniform<dim>::sample_dim(const int d) {
  double s = (double)rand() / (double)RAND_MAX;
  s *= m_upper[d] - m_lower[d];
  s += m_lower[d];
  return s;
}

#endif
