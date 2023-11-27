#include <iostream>

#include "distributions.hpp"

int uniform_1d() {
  Uniform u(5., 10.);
  // TODO: Check dimension

  const int n = 10;
  Matrix* samples = u.samples(n);
  for (int i = 0; i < n; i++){
    std::vector<double>& s = (*samples)[i];
    for (double& e : s){
      std::cout << e << " ";  // TODO: Check range instead
    }
    std::cout << std::endl;
  }
  delete samples;

  return 0;
}

int uniform_nd() {
  const int dim = 2;
  const double lower[dim] = {1., 10.};
  const double upper[dim] = {2., 20.};
  Uniform u(dim, lower, upper);

  const int n = 10;
  Matrix* samples = u.samples(n);
  for (int i = 0; i < n; i++){
    std::vector<double>& s = (*samples)[i];
    for (double& e : s){
      std::cout << e << " ";  // TODO: Check range instead
    }
    std::cout << std::endl;
  }
  delete samples;

  return 0;
}

int main(){

  return 0;
}
