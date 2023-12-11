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

  const int n = 1000;
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
  MonteCarloApproximator<dim>* mca_uniform = poly.mca(n, &uniform);
  MonteCarloApproximator<dim>* mca_normal = poly.mca(n, &normal);

  // Print sample approximations
  // TODO: Which distributions should be used?
  std::cout << "Mean (Polynomial)    : " << mca_uniform->mean().reshaped(1, dim) << std::endl;
  std::cout << "Variance (Polynomial): " << mca_uniform->var().reshaped(1, dim) << std::endl;
  std::cout << "Mean (Polynomial)    : " << mca_normal->mean().reshaped(1, dim) << std::endl;
  std::cout << "Variance (Polynomial): " << mca_normal->var().reshaped(1, dim) << std::endl;
}

// Just to show the workflow can be short
void workflow() {
  // Set parameters
  const int n = 1000;
  const int dim = 3;

  // Get samples from a distribution
  Normal<dim> dist(0., 1.);
  // Pass samples through a function and define the approximator
  Polynomial<dim, dim> poly("tests/data/poly.dat");
  MonteCarloApproximator<dim>* mca = poly.mca(n, &dist);

  // Print approximations
  std::cout << "Mean (Polynomial)    : " << mca->mean().reshaped(1, dim) << std::endl;
  std::cout << "Variance (Polynomial): " << mca->var().reshaped(1, dim) << std::endl;
}

// TODO: Create a test from each error
// TODO: Create plots from the errors vs. n (?)
void ctl() {
  const int N = 10000;  // A large number for getting a close approximation
  const int n = 100;  // A smaller number
  const int dim = 1;

  // Define the distribution and the function
  Normal<dim> dist(0., 1.);
  Polynomial<dim, dim> poly("tests/data/poly.dat");

  // Formerly get_sample_means
  const int m = 1000;  // A sufficiently large number to get the right distribution
  std::vector<Vector<dim>> means(m);
  for(int i = 0; i < m; ++i){
    means[i] = poly.mean(n, &dist);
  }

  // Formerly is_clt_valid
  MonteCarloApproximator<dim> mca(&means);
  Vector<dim> mean_the = poly.mean(N, &dist);
  // TODO: What if the theoretical mean is zero?
  Vector<dim> mean_err = (mean_the - mca.mean()).abs() / mean_the;  // theoretical mean vs. Mean of means
  Vector<dim> var_the = poly.var(N, &dist) / n;
  Vector<dim> var_err = (var_the - mca.var()).abs() / var_the;  // theoretical variance vs. Variance of means

  // Set a threshold
  // error_threshold = 1.96 * sqrt(dist_sample_mean_var.array() / m_means);

  std::cout << "Relative error (%) in the mean of approximated means    : " << mean_err * 100 << std::endl;
  std::cout << "Relative error (%) in the variance of approximated means: " << var_err * 100 << std::endl;
}

int main(){
  // test_approximations();
  // workflow();
  ctl();
  return 0;
}
