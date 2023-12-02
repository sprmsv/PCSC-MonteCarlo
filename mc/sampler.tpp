#include "sampler.hpp"

template <typename F> MonteCarloSampler<F>::MonteCarloSampler(typename F::ptr f, std::string dist)
  : f(f), dist(dist) {
  // TODO: Assert dist is in "normal", "uniform"
  // TODO: Initialize distribution
  }

template <typename F> MonteCarloSampler<F>::~MonteCarloSampler() {}

template <typename F> double MonteCarloSampler<F>::moment(int k, std::string mode) {
    // TODO: Assert mode is in "raw", "central", "standardized"
    // TODO: Implement
    return 0.;
}

template <typename F> double MonteCarloSampler<F>::mean() {
    return this->moment(1, "raw");
}

template <typename F> double MonteCarloSampler<F>::var() {
    return this->moment(2, "central");
}

template <typename F> double MonteCarloSampler<F>::skewness() {
    return this->moment(3, "standardized");
}
