#include <iostream>

#include <Eigen/Core>

#include "distributions.hpp"
#include "sampler.hpp"
#include "functions.hpp"


int main(){
  Polynomial<double, double> p("tmp.dat");
  std::cout << p.call(5.) << std::endl;

  return 0;
}
