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
#include "exceptions.hpp"

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
  const int dim_inp = 3;
  const int dim_out = 1;
  Polynomial<dim_inp> poly("tests/data/poly.dat");
  auto mca_poly_uniform = poly.mca(n, &uniform);
  auto mca_poly_normal = poly.mca(n, &normal);

  // Print sample approximations
  // TODO: Which distributions should be used?
  std::cout << "Mean (Polynomial)    : " << mca_poly_uniform->mean().reshaped(1, dim_out) << std::endl;
  std::cout << "Variance (Polynomial): " << mca_poly_uniform->var().reshaped(1, dim_out) << std::endl;
  std::cout << "Mean (Polynomial)    : " << mca_poly_normal->mean().reshaped(1, dim_out) << std::endl;
  std::cout << "Variance (Polynomial): " << mca_poly_normal->var().reshaped(1, dim_out) << std::endl;
}

// Just to show the workflow can be short
void workflow() {
  // Set parameters
  const int n = 1000;
  const int dim_inp = 3;
  const int dim_out = 1;

  // Get samples from a distribution
  Normal<dim_inp> dist(0., 1.);
  // Pass samples through a function and define the approximator
  Polynomial<dim_inp> poly("tests/data/poly.dat");
  auto mca = poly.mca(n, &dist);

  // Print approximations
  std::cout << "Mean (Polynomial)    : " << mca->mean().reshaped(1, dim_out) << std::endl;
  std::cout << "Variance (Polynomial): " << mca->var().reshaped(1, dim_out) << std::endl;
}

// TODO: Create a test from each error
// TODO: Create plots from the errors vs. n (?)
void ctl() {
  const int N = 10000;  // A large number for getting a close approximation
  const int n = 10;  // A smaller number
  const int dim_inp = 3;
  const int dim_out = 1;

  // Define the distribution and the function
  Normal<dim_inp> dist(0., 1.);
  Polynomial<dim_inp> poly("tests/data/poly.dat");

  // Formerly get_sample_means
  const int m = 1000;  // A sufficiently large number to get the right distribution
  std::vector<Vector<dim_out>> means(m);
  for(int i = 0; i < m; ++i){
    means[i] = poly.mean(n, &dist);
  }

  // Formerly is_clt_valid
  MonteCarloApproximator<dim_out> mca(std::make_shared<std::vector<Vector<dim_out>>>(means));
  Vector<dim_out> mean_the = poly.mean(N, &dist);
  // TODO: What if the theoretical mean is zero?
  Vector<dim_out> mean_err = (mean_the - mca.mean()).abs() / mean_the;  // theoretical mean vs. Mean of means
  Vector<dim_out> var_the = poly.var(N, &dist) / n;
  Vector<dim_out> var_err = (var_the - mca.var()).abs() / var_the;  // theoretical variance vs. Variance of means

  // Set a threshold
  // error_threshold = 1.96 * sqrt(dist_sample_mean_var.array() / m_means);

  std::cout << "Relative error (%) in the mean of approximated means    : " << mean_err * 100 << std::endl;
  std::cout << "Relative error (%) in the variance of approximated means: " << var_err * 100 << std::endl;
}

void test_combinedfunctions() {
  const int dim = 3;
  Polynomial<dim> f1("tests/data/poly.dat");
  SumExponential<dim> f2("tests/data/sumexp.dat");
  SumLogarithm<dim> f3("tests/data/sumlog.dat");

  Vector<dim> x = 1.;
  std::cout << "f1(x) = " << f1(x) << std::endl;
  std::cout << "f2(x) = " << f2(x) << std::endl;
  std::cout << "f3(x) = " << f3(x) << std::endl;

  std::cout << "Sum = " << (f1 + f2 + f3)(x) << std::endl;
  std::cout << "Sub = " << (f1 - f2 - f3)(x) << std::endl;
  std::cout << "Mul = " << (f1 * f2 * f3)(x) << std::endl;
  std::cout << "Div = " << (f1 / f2 / f3)(x) << std::endl;

  std::cout << "f1 + f2 * f3 = " << (f1 + f2 * f3)(x) << std::endl;
  std::cout << "f1 + (f2 * f3) = " << (f1 + (f2 * f3))(x) << std::endl;
  std::cout << "(f1 + f2) * f3 = " << ((f1 + f2) * f3)(x) << std::endl;
}

void test_linear() {
  Linear<3, 4> l1("tests/data/linear.dat");
  Vector<3> x(std::vector<double>({1., 0., 1.}));
  std::cout << "Linear(x) = " << l1(x) << std::endl;
}

int main() {
  test_approximations();
  workflow();
  // ctl();
  test_combinedfunctions();
  test_linear();

  return 0;
}

// MAIN

void print_usage(std::ostream& stream, char* name) {
  stream << "USAGE: "
  << name
  << " --function <input-function-file>"
  << " [-k <order>]"
  << " [--mode <moment-mode>]"
  << " [--dist <sample-distribution>]"
  << " [--n <n-samples>]"
  << " [--output <output-directory>]"
  << " [--plot <plot-samples>]"
  << " [--clt <show-clt-convergence>]"
  << std::endl;
}

void print_help(std::ostream& stream) {
  stream << "--function <input-function-file>" << std::endl;
  stream << "\t Path to the input file that defines the function" << std::endl;
  stream << "[-k <order>]" << std::endl;
  stream << "\t *Optional* Moment order" << std::endl;
  stream << "[--mode <moment-mode>]" << std::endl;
  stream << "\t *Optional* Moment type (Default: \"standardized\")" << std::endl;
  stream << "[--dist <sample-distribution>]" << std::endl;
  stream << "\t *Optional* Source sample distribution (Default: \"normal\")" << std::endl;
  stream << "[--n <n-samples>]" << std::endl;
  stream << "\t *Optional* Number of samples (Default: 1000)" << std::endl;
  stream << "[--output <output-directory>]" << std::endl;
  stream << "\t *Optional* Path to output directory" << std::endl;
  stream << "[--plot <plot-samples>]" << std::endl;
  stream << "\t *Optional* Whether to save plots of samples" << std::endl;
  stream << "[--clt <show-clt-convergence>]" << std::endl;
  stream << "\t *Optional* Whether to save CLT outputs" << std::endl;
}

void launch_workflow(const ArgParser& parser) {
  // TODO: Automize with boost/preprocessor.hpp
  if ((parser.dim_inp == 1) && (parser.dim_out == 1)) {
    Workflow<1, 1> workflow(parser);
    workflow.launch();
  }
  else if ((parser.dim_inp == 1) && (parser.dim_out == 2)) {
    Workflow<1, 2> workflow(parser);
    workflow.launch();
  }
  else if ((parser.dim_inp == 1) && (parser.dim_out == 3)) {
    Workflow<1, 3> workflow(parser);
    workflow.launch();
  }
  else if ((parser.dim_inp == 1) && (parser.dim_out == 4)) {
    Workflow<1, 4> workflow(parser);
    workflow.launch();
  }
  else if ((parser.dim_inp == 2) && (parser.dim_out == 1)) {
    Workflow<2, 1> workflow(parser);
    workflow.launch();
  }
  else if ((parser.dim_inp == 2) && (parser.dim_out == 2)) {
    Workflow<2, 2> workflow(parser);
    workflow.launch();
  }
  else if ((parser.dim_inp == 2) && (parser.dim_out == 3)) {
    Workflow<2, 3> workflow(parser);
    workflow.launch();
  }
  else if ((parser.dim_inp == 2) && (parser.dim_out == 4)) {
    Workflow<2, 4> workflow(parser);
    workflow.launch();
  }
  else if ((parser.dim_inp == 3) && (parser.dim_out == 1)) {
    Workflow<3, 1> workflow(parser);
    workflow.launch();
  }
  else if ((parser.dim_inp == 3) && (parser.dim_out == 2)) {
    Workflow<3, 2> workflow(parser);
    workflow.launch();
  }
  else if ((parser.dim_inp == 3) && (parser.dim_out == 3)) {
    Workflow<3, 3> workflow(parser);
    workflow.launch();
  }
  else if ((parser.dim_inp == 3) && (parser.dim_out == 4)) {
    Workflow<3, 4> workflow(parser);
    workflow.launch();
  }
  else if ((parser.dim_inp == 4) && (parser.dim_out == 1)) {
    Workflow<4, 1> workflow(parser);
    workflow.launch();
  }
  else if ((parser.dim_inp == 4) && (parser.dim_out == 2)) {
    Workflow<4, 2> workflow(parser);
    workflow.launch();
  }
  else if ((parser.dim_inp == 4) && (parser.dim_out == 3)) {
    Workflow<4, 3> workflow(parser);
    workflow.launch();
  }
  else if ((parser.dim_inp == 4) && (parser.dim_out == 4)) {
    Workflow<4, 4> workflow(parser);
    workflow.launch();
  }
  else {
    std::string msg = "Dimensions of the function are not supported: "
      + std::to_string(parser.dim_inp) + ", " + std::to_string(parser.dim_out);
    throw FunctionNotSupported(msg);
  }
}

int main_(int argc, char** argv){

  //TODO: Implement online version (user input directly)
  if (argc == 1) {
    std::cout << "Online mode is not implemented yet." << std::endl;
    print_usage(std::cout, argv[0]);
  }
  else if (argc == 2 && !strcmp(argv[1], "--help")) {
    print_usage(std::cout, argv[0]);
    std::cout << std::endl;
    print_help(std::cout);
  }
  // Set up arguments from the command line inputs
  else if (argc < 19) {
    try{
      ArgParser parser(argc, argv);
      launch_workflow(parser);
    }
    catch (const ArgumentParseException& e) {
      std::cout << e.what() << std::endl;
      print_usage(std::cerr, argv[0]);
      return 1;
    }
    catch (const Exception& e) {
      std::cout << e.what() << std::endl;
      return 1;
    }
  }
  // Print usage and return
  else {
    print_usage(std::cerr, argv[0]);
    return 1;
  }

  return 0;
}
