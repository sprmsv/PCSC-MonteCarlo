#ifndef MC_IO_HPP
#define MC_IO_HPP

#include "functions.hpp"
#include "distributions.hpp"
#include "sampler.hpp"
#include "exceptions.hpp"

#include <string>
#include <vector>


class Reader {
protected:
  Reader();
  virtual void setup() = 0;
};

// Call from Command line
class ArgParser: public Reader {
public:
  ArgParser(int argc, char* argv[]);
  void parse();
  virtual void setup() override;
  // Path to function file
  std::string function;
  // Statistic
  std::string stat;
  // Moment order
  int k;
  // Moment type
  std::string mode;
  // Distribution name
  std::string dist;
  // Number of samples
  int n;
  // Path to output directory
  std::string output;
  // Whether to save plots
  bool plot;
  // Whether to save clt outputs
  bool clt;
  // Arguments
  std::vector<std::string> args;
};

template <unsigned int dim_inp, unsigned int dim_out>
class Workflow {
public:
  Workflow();
  ~Workflow();

  Workflow(std::string dir, std::string stat, std::string mode, int k, std::string dist, std::string ftype, std::string filepath);
  void run();
private:
  std::string mode;
  std::string stat;
  std::string dir;
  int k;
  Function<dim_inp, dim_out>* f;
  Distribution<dim_inp>* d;
  MonteCarloApproximator<dim_out>* mc;
};

#endif
