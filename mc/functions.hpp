#ifndef MC_FUNCTIONS_HPP
#define MC_FUNCTIONS_HPP

#include "sampler.hpp"
#include "distributions.hpp"
#include "vector.hpp"

#include <Eigen/Core>

#include <vector>
#include <string>

template <unsigned int dim_inp, unsigned int dim_out>
class Function {
public:
  Function();
  // Function(Distribution& dist, unsigned int n = 1000);
  Vector<dim_out> operator()(const Vector<dim_inp>& x) {return this->call(x);};
  virtual Vector<dim_out> call(const Vector<dim_inp>& x) = 0;
private:
  // Distribution* m_dist;
  // MonteCarloApproximater<dim_out> m_mca;
};

template <unsigned int dim_inp, unsigned int dim_out>
class Polynomial : public Function<dim_inp, dim_out> {
public:
  Polynomial(std::string filepath);
  // Polynomial(std::string filepath, Distribution& dist, unsigned int n = 1000);
  // Polynomial(std::vector<double> &coeffs, Distribution& dist, unsigned int n = 1000);
  std::vector<double> m_coeffs;
  Vector<dim_out> call(const Vector<dim_inp>& x) override;
};

#include "functions.tpp"

#endif
