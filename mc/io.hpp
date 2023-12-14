#ifndef MC_IO_HPP
#define MC_IO_HPP

#include "functions.hpp"
#include "distributions.hpp"
#include "sampler.hpp"
#include "exceptions.hpp"
#include "output.cpp"

#include <string>
#include <vector>
#include <set>
#include <map>
#include <memory>
#include <sys/types.h>
#include <sys/stat.h>


// Call from Command line
class ArgParser {
public:
  // Constructor
  ArgParser(int argc, char* argv[]);
  // Path to function file
  std::string function;
  // Function type
  std::string functype;
  // Input dimension of the function
  unsigned int dim_inp;
  // Output dimension of the function
  unsigned int dim_out;
  // Moment order
  int order;
  // Moment type
  std::string mode;
  // Distribution name
  std::string dist;
  // Number of samples
  int n_samples;
  // Path to output directory
  std::string output;
  // Whether to save plots
  bool plot;
  // Whether to save clt outputs
  bool clt;
private:
  // Parse arguments and initialize members
  void parse();
  // Arguments
  std::vector<std::string> args;
};

template <unsigned int dim_inp, unsigned int dim_out>
class Workflow {
public:
  Workflow(const ArgParser& parser);
  ~Workflow();
  void launch();
  void clt(int n = 10);
private:
  const ArgParser& m_parser;
  Function<dim_inp, dim_out>* m_function;
  Distribution<dim_inp>* m_distribution;
  std::unique_ptr<MonteCarloApproximator<dim_out>> m_mca;
};

#include "io.tpp"

#endif
