#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>

#include "distributions.hpp"
#include "sampler.hpp"
#include "functions.hpp"
#include "io.hpp"

int main(int argc, char* argv[]){
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

// int main(){

//   const int n = 10000;
//   const int dim = 1;

//   // Define uniform distribution
//   std::vector<double> lower(dim);
//   std::fill(lower.begin(), lower.end(), -1.);
//   std::vector<double> upper(dim);
//   std::fill(upper.begin(), upper.end(), +1.);
//   Uniform<dim> uniform(lower, upper);

//   // Define normal distribution
//   std::vector<double> mean(dim);
//   std::fill(mean.begin(), mean.end(), 0.);
//   std::vector<double> variance(dim);
//   std::fill(variance.begin(), variance.end(), 1.);
//   Normal<dim> normal(mean, variance);

//   // Get samples
//   auto samples_uniform = uniform.samples(n);
//   auto samples_normal = normal.samples(n);

//   // Print sample approximations
//   MonteCarloApproximater<dim> app_uniform(samples_uniform);
//   std::cout << "Mean (Uniform)    : " << app_uniform.mean().reshaped(1, dim) << std::endl;
//   std::cout << "Variance (Uniform): " << app_uniform.var().reshaped(1, dim) << std::endl;
//   MonteCarloApproximater<dim> app_normal(samples_normal);
//   std::cout << "Mean (Normal)     : " << app_normal.mean().reshaped(1, dim) << std::endl;
//   std::cout << "Variance (Normal) : " << app_normal.var().reshaped(1, dim) << std::endl;

//   // Pass samples through a function
//   // TODO: Implement classes for input/output with = * / + [] operators as in Paul's UMLs
//   Polynomial<dim, dim> poly("../tests/data/poly.dat");
//   std::vector<Vector<dim>> outputs_uniform(n);
//   for (int i=0; i<n; ++i) {
//     outputs_uniform[i] = poly(samples_uniform->at(i));
//   }
//   std::vector<Vector<dim>> outputs_normal(n);
//   for (int i=0; i<n; ++i) {
//     outputs_normal[i] = poly(samples_normal->at(i));
//   }

//   // Print sample approximations
//   // TODO: Which distributions should be used?
//   MonteCarloApproximater<dim> pol_uniform(&outputs_uniform);
//   std::cout << "Mean (Polynomial)    : " << pol_uniform.mean().reshaped(1, dim) << std::endl;
//   std::cout << "Variance (Polynomial): " << pol_uniform.var().reshaped(1, dim) << std::endl;
//   MonteCarloApproximater<dim> pol_normal(&outputs_normal);
//   std::cout << "Mean (Polynomial)    : " << pol_normal.mean().reshaped(1, dim) << std::endl;
//   std::cout << "Variance (Polynomial): " << pol_normal.var().reshaped(1, dim) << std::endl;

//   // TODO: Show central limit theorem

//   return 0;
// }
