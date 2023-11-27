#include <iostream>
#include "distributions.hpp"

int main(){

  const int dim = 2;
  const double lower[dim] = {1., 10.};
  const double upper[dim] = {2., 20.};
  Uniform<dim> u(lower, upper);

  const int n = 10;
  Matrix* samples = u.samples(n);
  for (int i = 0; i < n; i++){
    std::vector<double>& s = (*samples)[i];
    for (double& e : s){
      std::cout << e << " ";
    }
    std::cout << std::endl;
  }
  delete samples;

  return 0;
}
