#include "functions.hpp"

#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>

template <unsigned int dim_inp, unsigned int dim_out>
Function<dim_inp, dim_out>::Function() {}

// template <unsigned int dim_inp, unsigned int dim_out>
// Function<dim_inp, dim_out>::Function(Distribution& dist, unsigned int n)
//   : m_dist(&dist) {
//     // Get samples and pass them through the function
//     // TODO: Move to a member function
//     std::vector<Vector<dim_out>> samples = m_dist.samples(n);
//     std::vector<Vector<dim_out>> outputs(n);
//     for (int i = 0; i < n; ++i) {
//       // outputs[i].resize(1);  // TODO: Reserve size
//       outputs[i] = poly(samples->at(i));
//     }
//     m_mca(outputs);

//   }

template<unsigned int dim_inp, unsigned int dim_out>
Polynomial<dim_inp, dim_out>::Polynomial(std::string filepath)
  // : Function<dim_inp, dim_out>(dist, n)
{
  std::ifstream file(filepath);
  assert(file.is_open());

  std::string line;
  while (!file.eof()){
    std::getline(file, line);
    try{
      m_coeffs.push_back(std::stod(line));
    }
    catch (std::invalid_argument &e){
      if (line == ""){
        m_coeffs.push_back(0.);
      }
      else {
        printf("Warning: Cannot parse \"%s\" as a coefficient.\n", line.c_str());
      }
    }
  }

  file.close();
}

// template<unsigned int dim_inp, unsigned int dim_out>
// Polynomial<dim_inp, dim_out>::Polynomial(std::vector<double> &coeffs, Distribution& dist, unsigned int n)
//   : Function<dim_inp, dim_out>(dist, n), m_coeffs(coeffs) {}

template<unsigned int dim_inp, unsigned int dim_out>
Vector<dim_out> Polynomial<dim_inp, dim_out>::call(const Vector<dim_inp>& x) {
  Vector<dim_out> y(0);
  Vector<dim_inp> x_powered = 1;
  for (int i = 0; i < m_coeffs.size(); ++i) {
    y = y + x_powered * m_coeffs[i];
    x_powered = x_powered * x;
  }
  return y;
}
