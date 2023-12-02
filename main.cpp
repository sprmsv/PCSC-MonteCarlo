#include <iostream>

#include <Eigen/Core>

#include "distributions.hpp"
#include "sampler.hpp"
#include "functions.hpp"


int main(){

  const int d = 2;
  std::vector<double> u = {1., 2.};
  std::vector<double> v = {3., 2.};
  std::vector<double> w = {5., 10.};
  std::vector<double> a = {5., 10.};
  std::vector<double> b = {5., 10.};
  std::vector<std::vector<double>> s = {u, v, w, a, b};
  std::vector<std::vector<double>>* m_samples = &s;


  MonteCarloApproximater<2> app(m_samples);

  // std::vector<unsigned int> orders = {5, 5};
  auto out = app.hypertailedness();
  std::cout << out << std::endl;

  return 0;
}
