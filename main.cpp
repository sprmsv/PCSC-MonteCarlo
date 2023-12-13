#include <iostream>
#include <string>
#include <algorithm>
#include <memory>
#include <iterator>

#include "distributions.hpp"
#include "sampler.hpp"
#include "functions.hpp"
#include "vector.hpp"
#include "io.hpp"

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
  MonteCarloApproximator<dim> mca_uniform(samples_uniform);
  std::cout << "Mean (Uniform)    : " << mca_uniform.mean().reshaped(1, dim) << std::endl;
  std::cout << "Variance (Uniform): " << mca_uniform.var().reshaped(1, dim) << std::endl;
  MonteCarloApproximator<dim> mca_normal(samples_normal);
  std::cout << "Mean (Normal)     : " << mca_normal.mean().reshaped(1, dim) << std::endl;
  std::cout << "Variance (Normal) : " << mca_normal.var().reshaped(1, dim) << std::endl;

  // Pass samples through a function
  Polynomial<dim, dim> poly("tests/data/poly.dat");
  auto mca_poly_uniform = poly.mca(n, &uniform);
  auto mca_poly_normal = poly.mca(n, &normal);

  // Print sample approximations
  // TODO: Which distributions should be used?
  std::cout << "Mean (Polynomial)    : " << mca_poly_uniform->mean().reshaped(1, dim) << std::endl;
  std::cout << "Variance (Polynomial): " << mca_poly_uniform->var().reshaped(1, dim) << std::endl;
  std::cout << "Mean (Polynomial)    : " << mca_poly_normal->mean().reshaped(1, dim) << std::endl;
  std::cout << "Variance (Polynomial): " << mca_poly_normal->var().reshaped(1, dim) << std::endl;
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
  auto mca = poly.mca(n, &dist);

  // Print approximations
  std::cout << "Mean (Polynomial)    : " << mca->mean().reshaped(1, dim) << std::endl;
  std::cout << "Variance (Polynomial): " << mca->var().reshaped(1, dim) << std::endl;
}

// TODO: Create a test from each error
// TODO: Create plots from the errors vs. n (?)
void ctl() {
  const int N = 10000;  // A large number for getting a close approximation
  const int n = 10;  // A smaller number
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
  MonteCarloApproximator<dim> mca(std::make_shared<std::vector<Vector<dim>>>(means));
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

void test_combinedfunctions() {
  const int dim = 2;
  Polynomial<dim, dim> p1("tests/data/poly.dat");
  Polynomial<dim, dim> p2(p1);
  Polynomial<dim, dim> p3(p1);

  Vector<dim> x = 5.;

  std::cout << p1(x) << std::endl;

  std::cout << (p1 + p2 + p3)(x) << std::endl;

  CombinedFunctionSum<dim, dim> s2(p1, p1, p1);
  // TODO: Resolve this issue
  // Segmentation fault when trying to reach m_f2->call(x) because m_f2 is a "const Function*"
  // Need to store m_f2 as a "const CombinedFunction*" or "const CombinedFunctionSum*"
  std::cout << s2(x) << std::endl;

}

int main() {
  // test_approximations();
  // workflow();
  // ctl();

  test_combinedfunctions();

  return 0;
}

int main_args(int argc, char* argv[]){
  std::string input_type;
  // Check if the required number of arguments are provided
    if ((argc < 14) || (argc > 6)) {
        input_type = "CL";
        ReaderCL ReaderCL(argc, argv);
        ReaderCL.setup();
    }
    else if (argc == 1)
    {
        input_type = "online";
        //TODO: Implement online version (user input directly)
    }
    else{
      std::cerr << "Usage: " 
                  << argv[0] 
                  << " --dir \"value\" --stat \"value\"-k \"value\" --mode \"value\"--dist \"value\" --function \"value\"\n";
        return 1;
    }

  //
  return 0;
}
