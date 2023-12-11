#include <iostream>
#include <string>
#include <algorithm>

#include "distributions.hpp"
#include "sampler.hpp"
#include "functions.hpp"
#include "vector.hpp"

#include <chrono>

// To make sure that everything works with both distributions
void test_approximations() {

  const int n = 10000;
  const int dim = 3;

  // Define uniform distribution
  std::vector<double> lower(dim);
  std::fill(lower.begin(), lower.end(), -1.);
  std::vector<double> upper(dim);
  std::fill(upper.begin(), upper.end(), +1.);
  Uniform<dim> uniform(lower, upper);

  // Define normal distribution
  std::vector<double> mean(dim);
  std::fill(mean.begin(), mean.end(), 0.);
  std::vector<double> variance(dim);
  std::fill(variance.begin(), variance.end(), 1.);
  Normal<dim> normal(mean, variance);

  // Get samples
  auto samples_uniform = uniform.samples(n);
  auto samples_normal = normal.samples(n);

  // Print sample approximations
  MonteCarloApproximator<dim> app_uniform(samples_uniform);
  std::cout << "Mean (Uniform)    : " << app_uniform.mean().reshaped(1, dim) << std::endl;
  std::cout << "Variance (Uniform): " << app_uniform.var().reshaped(1, dim) << std::endl;
  MonteCarloApproximator<dim> app_normal(samples_normal);
  std::cout << "Mean (Normal)     : " << app_normal.mean().reshaped(1, dim) << std::endl;
  std::cout << "Variance (Normal) : " << app_normal.var().reshaped(1, dim) << std::endl;

  // Pass samples through a function
  Polynomial<dim, dim> poly("tests/data/poly.dat");
  auto outputs_uniform = poly(samples_uniform);
  auto outputs_normal = poly(samples_normal);

  // Print sample approximations
  // TODO: Which distributions should be used?
  MonteCarloApproximator<dim> pol_uniform(outputs_uniform);
  std::cout << "Mean (Polynomial)    : " << pol_uniform.mean().reshaped(1, dim) << std::endl;
  std::cout << "Variance (Polynomial): " << pol_uniform.var().reshaped(1, dim) << std::endl;
  MonteCarloApproximator<dim> pol_normal(outputs_normal);
  std::cout << "Mean (Polynomial)    : " << pol_normal.mean().reshaped(1, dim) << std::endl;
  std::cout << "Variance (Polynomial): " << pol_normal.var().reshaped(1, dim) << std::endl;
}

// Just to show the workflow can be short
void workflow() {
  // Set parameters
  const int n = 10000;
  const int dim = 3;

  // Get samples from a distribution
  Normal<dim> dist(0., 1.);
  std::vector<Vector<dim>>* samples = dist.samples(n);
  // Pass samples through a function and define the approximator
  Polynomial<dim, dim> poly("tests/data/poly.dat");
  std::vector<Vector<dim>>* outputs = poly(samples);
  MonteCarloApproximator<dim> mca(outputs);

  // Print approximations
  std::cout << "Mean (Polynomial)    : " << mca.mean().reshaped(1, dim) << std::endl;
  std::cout << "Variance (Polynomial): " << mca.var().reshaped(1, dim) << std::endl;
}

int main(){
  test_approximations();
  workflow();
  return 0;
}
