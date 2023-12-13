#ifndef MC_IO_HPP
#define MC_IO_HPP

#include "functions.hpp"
#include "distributions.hpp"
#include "sampler.hpp"
#include <string>
#include <vector>

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

// TODO: Make this an abstract class
class Reader {
protected:
  Reader();
  virtual void setup() = 0;
};

// Call from Command line
class ReaderCL: public Reader{
public:
  ReaderCL(int argc, char* argv[]);
  ~ReaderCL();
  void parser();
  virtual void setup() override;
private:
  std::string dir;
  std::string stat;
  std::string mode;
  int k;
  std::string dist;
  std::string function;
  std::vector<std::string> commandLine;
};

#endif
