#include <iostream>
#include <fstream>

#include "distributions.hpp"

int uniform_1d() {
  // Uniform u(5., 10.);
  // // TODO: Check dimension

  // const int n = 10;
  // std::vector<std::vector<double>>* samples = u.samples(n);
  // for (int i = 0; i < n; i++){
  //   std::vector<double>& s = (*samples)[i];
  //   for (double& e : s){
  //     std::cout << e << " ";  // TODO: Check range instead
  //   }
  //   std::cout << std::endl;
  // }
  // delete samples;

  return 0;
}

int uniform_nd() {
  // const int dim = 2;
  // const double lower[dim] = {1., 10.};
  // const double upper[dim] = {2., 20.};
  // Uniform u(dim, lower, upper);

  // const int n = 10;
  // std::vector<std::vector<double>>* samples = u.samples(n);
  // for (int i = 0; i < n; i++){
  //   std::vector<double>& s = (*samples)[i];
  //   for (double& e : s){
  //     std::cout << e << " ";  // TODO: Check range instead
  //   }
  //   std::cout << std::endl;
  // }
  // delete samples;

  return 0;
}

int normal_1d() {
  // Normal u(100., 25.);
  // const int n = 3000;
  // std::vector<std::vector<double>>* samples = u.samples(n);

  // // TODO: Check mean / std

  // std::ofstream f("normal_nD.out");
  // for (int i = 0; i < n; i++){
  //   std::vector<double>& s = (*samples)[i];
  //   for (double& e : s){
  //     f << e << " ";
  //   }
  //   f << std::endl;
  // }
  // delete samples;

  return 0;
}

int normal_nD() {
  // const unsigned int dim = 2;
  // Eigen::Vector2d mean;
  // mean << 0., 50.;
  // Eigen::Matrix2d cov;
  // cov << 1., 0., 0., 2.;
  // Normal<dim> u(mean, cov);
  // const int n = 3000;
  // Matrix* samples = u.samples(n);

  // // TODO: Check mean / std

  // std::ofstream f("normal_nD.out");
  // for (int i = 0; i < n; i++){
  //   std::vector<double>& s = (*samples)[i];
  //   for (double& e : s){
  //     f << e << " ";
  //   }
  //   f << std::endl;
  // }
  // delete samples;

  return 0;
}

int main(){

  return 0;
}
