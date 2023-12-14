#include "clt.hpp"

template<int dim_inp, int dim_out>
CLT<dim_inp, dim_out>::CLT() : N(10000), n(10), dist(new Normal<dim_inp>(0., 1.)), func(new Polynomial<dim_inp>("tests/data/poly.dat")) {
  try
  {
    assert(dim_inp == func->dim_inp);
    assert(dim_out == func->dim_out);
  }
  catch(const Exception& e)
  {
    throw DimensionNotSupported("The dimensions of the function and the distribution do not match.");
  }
}

template<int dim_inp, int dim_out>
CLT<dim_inp, dim_out>::CLT(Distribution<dim_inp>* dist, Function<dim_inp, dim_out>* func) : N(10000), n(10), dist(dist), func(func) {
  try
  {
    assert(dim_inp == func->dim_inp);
    assert(dim_out == func->dim_out);
  }
  catch(const Exception& e)
  {
    throw DimensionNotSupported("The dimensions of the function and the distribution do not match.");
  }
}

template<int dim_inp, int dim_out>
CLT<dim_inp, dim_out>::CLT(const int N, const int n, Distribution<dim_inp>* dist, Function<dim_inp, dim_out>* func) : N(N), n(n), dist(dist), func(func) {
  try
  {
    assert(dim_inp == func->dim_inp);
    assert(dim_out == func->dim_out);
  }
  catch(const Exception& e)
  {
    throw DimensionNotSupported("The dimensions of the function and the distribution do not match.");
  }
}

template<int dim_inp, int dim_out>
CLT<dim_inp, dim_out>::~CLT() {
  delete dist;
  delete func;
}


// replace clt() with run()
template<int dim_inp, int dim_out>
std::vector<Vector<dim_out>> CLT<dim_inp, dim_out>::run() {

  clt_return = std::vector<Vector<dim_out>>(2);
  // Formerly get_sample_means
  const int m = 1000;  // A sufficiently large number to get the right distribution
  std::vector<Vector<dim_out>> means(m);
  for(int i = 0; i < m; ++i){
    means[i] = func->mean(n, dist);
  }

  // Formerly is_clt_valid
  MonteCarloApproximator<dim_out> mca(std::make_shared<std::vector<Vector<dim_out>>>(means));

  Vector<dim_out> mean_the = func->mean(N, dist);
  // Handle the case where the theoretical mean is zero
  for (int i = 0; i < dim_out; ++i) {
    if (mean_the[i] < 1.e-10) {
      mean_the[i] = 1.e-10;
    }
  }
  clt_return[0] = (mean_the - mca.mean()).abs() / mean_the;  // theoretical mean vs. Mean of means
  
  Vector<dim_out> var_the = func->var(N, dist) / n;
  // Handle the case where the theoretical variance is zero
  for (int i = 0; i < dim_out; ++i) {
    if (var_the[i] < 1.e-10) {
      var_the[i] = 1.e-10;
    }
  }
  clt_return[1] = (var_the - mca.var()).abs() / var_the;  // theoretical variance vs. Variance of means

  return clt_return;

template<int dim_inp, int dim_out>
void CLT<dim_inp, dim_out>::output(std::ostream& os) {
  os << "Mean (Polynomial)    : " << clt_return[0].reshaped(1, dim_out) << std::endl;
  os << "Variance (Polynomial): " << clt_return[1].reshaped(1, dim_out) << std::endl;
}
