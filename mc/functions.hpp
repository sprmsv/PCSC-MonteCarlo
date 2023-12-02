#ifndef MC_FUNCTIONS_HPP
#define MC_FUNCTIONS_HPP

#include <Eigen/Core>

#include <vector>
#include <string>


// TODO: Make this an abstract class
template <unsigned int dim_inp = 1, unsigned int dim_out = 1>
class Function {
public:
  Function();
  typedef Eigen::Matrix<double, dim_inp, 1> input;
  typedef Eigen::Matrix<double, dim_out, 1> output;
  typedef std::function<output(input)> ptr;
};

// TODO: Make this an abstract class
template <unsigned int dim_inp = 1>
class ScalarMDFunction : public Function<dim_inp, 1> {
public:
  ScalarMDFunction();
  typedef typename Function<dim_inp, 1>::input input;
  typedef double output;
  typedef std::function<output(input)> ptr;
};

// TODO: Make this an abstract class
class Scalar1DFunction : public Function<1, 1> {
public:
  Scalar1DFunction();
  typedef double input;
  typedef double output;
  typedef std::function<output(input)> ptr;
};

// TODO: Make this an abstract class
class Polynomial : public Function<1, 1> {
public:
  Polynomial(std::string filepath);
  Polynomial(std::vector<double> &coeffs);
  typedef typename Function<1, 1>::input input;
  typedef typename Function<1, 1>::output output;
  typedef std::function<output(input)> ptr;

  std::vector<double> m_coeffs;
};

#include "functions.tpp"

#endif
