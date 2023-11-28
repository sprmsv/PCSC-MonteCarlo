#include <iostream>

#include <Eigen/Core>

#include "distributions.hpp"
#include "sampler.hpp"


typedef Eigen::Matrix<double, 1, 1> M1;

double func(M1 x) {
  return 1.;
}

int main(){
  MonteCarloSampler<1> sampler(&func);

  return 0;
}
