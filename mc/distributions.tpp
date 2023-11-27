#ifndef MC_DISTRIBUTIONS_TPP
#define MC_DISTRIBUTIONS_TPP

#define RAND_SEED 42


template <int dim> Distribution<dim>::Distribution()
  : m_dim(dim) {
    srand(RAND_SEED);
  }

template <int dim> Distribution<dim>::~Distribution() {}

// template <int dim> double* Distribution<dim>::icdf(double p) {
// }


template <int dim> Normal<dim>::Normal()
  : Distribution<dim>() {}

template <int dim> Normal<dim>::~Normal() {}


template <int dim> Uniform<dim>::Uniform()
  : Distribution<dim>() {}

template <int dim> Uniform<dim>::~Uniform() {}


// TODO: Change to Eigen matrix
// TODO: Specialize for the 1D case
template <int dim> Matrix* Uniform<dim>::sample(const int n) {
  Matrix* samples = new Matrix(n, std::vector<double>(this->m_dim));
  for (int i = 0; i < n; i++){
    std::vector<double>& s = (*samples)[i];
    for (double& e : s){
      e = (double)rand() / (double)RAND_MAX;
    }
  }
  return samples;
}

#endif
