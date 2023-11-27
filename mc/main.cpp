#include <iostream>
#include "distributions.hpp"

int main(){
  Uniform u;

  const int n = 7;
  Matrix* samples = u.sample(n);

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
