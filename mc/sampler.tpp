#include "sampler.hpp"

template <unsigned int dim_inp> MonteCarloSampler<dim_inp>::MonteCarloSampler(function f, std::string dist)
  : f(f), dist(dist) {
  // TODO: Assert dist is in "normal", "uniform"
  // TODO: Initialize distribution
  }

template <unsigned int dim_inp> MonteCarloSampler<dim_inp>::~MonteCarloSampler() {}

template <unsigned int dim_inp> double MonteCarloSampler<dim_inp>::moment(int k, std::string mode) {
    // TODO: Assert mode is in "raw", "central", "standardized"
    // TODO: Implement
    return 0.;
}

template <unsigned int dim_inp> double MonteCarloSampler<dim_inp>::mean() {
    return this->moment(1, "raw");
}

template <unsigned int dim_inp> double MonteCarloSampler<dim_inp>::var() {
    return this->moment(2, "central");
}

template <unsigned int dim_inp> double MonteCarloSampler<dim_inp>::skewness() {
    return this->moment(3, "standardized");
}
