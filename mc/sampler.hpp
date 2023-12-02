#ifndef MC_SAMPLER_HPP
#define MC_SAMPLER_HPP

#include <functional>
#include <string>

#include <Eigen/Core>

#include "distributions.hpp"
#include "functions.hpp"


// TODO: Specialize for scalar univariate functions
// TODO: If feasible, extend to vectorial multivariate functions
template <typename F>
class MonteCarloSampler {
public:

  MonteCarloSampler(typename F::ptr f, std::string mode = "normal");
  ~MonteCarloSampler();

  double moment(int k, std::string mode);
  double mean();
  double var();
  double skewness();

private:
  typename F::ptr f;
  std::string dist;
};

#include "sampler.tpp"

#endif
