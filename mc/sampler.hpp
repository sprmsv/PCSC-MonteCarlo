#ifndef MC_SAMPLER_HPP
#define MC_SAMPLER_HPP

#include <functional>
#include <string>

#include <Eigen/Core>

#include "distributions.hpp"


// TODO: Specialize for scalar univariate functions
// TODO: If feasible, extend to vectorial multivariate functions
template <unsigned int dim_inp = 1>
class MonteCarloSampler {
public:
  typedef double output;
  typedef Eigen::Matrix<double, dim_inp, 1> input;
  typedef std::function<output(input)> function;

  MonteCarloSampler(function, std::string = "normal");
  ~MonteCarloSampler();

  double moment(int, std::string);
  double mean();
  double var();
  double skewness();

private:
  function f;
  std::string dist;
};

#include "sampler.tpp"

#endif
