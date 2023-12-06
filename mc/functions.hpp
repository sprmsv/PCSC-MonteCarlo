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
  Vector<dim_out> operator()(const Vector<dim_inp>& x);
  std::vector<Vector<dim_out>>* operator()(std::vector<Vector<dim_inp>>* x);
  virtual Vector<dim_out> call(const Vector<dim_inp>& x) = 0;
};

template <unsigned int dim_inp, unsigned int dim_out>
class Polynomial : public Function<dim_inp, dim_out> 
{
public:
  Polynomial(std::string filepath);
  Polynomial(std::vector<double> &coeffs);
  std::vector<double> m_coeffs;

  Vector<dim_out> call(const Vector<dim_inp>& x) override;
};

#include "functions.tpp"

#endif
