#include "functions.hpp"

#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>

template <unsigned int dim_inp, unsigned int dim_out>
Function<dim_inp, dim_out>::Function() {}

template <unsigned int dim_inp, unsigned int dim_out>
Vector<dim_out> Function<dim_inp, dim_out>::operator()(const Vector<dim_inp>& x) {
  return this->call(x);
}

template <unsigned int dim_inp, unsigned int dim_out>
std::vector<Vector<dim_out>>* Function<dim_inp, dim_out>::operator()(std::vector<Vector<dim_inp>>* xs) {
  // TODO: Keep track of the samples and destroy them!!
  std::vector<Vector<dim_out>>* outputs = new std::vector<Vector<dim_out>>(xs->size(), Vector<dim_out>());
  for (int i = 0; i < xs->size(); ++i) {
    outputs->at(i) = this->call(xs->at(i));
  }
  return outputs;
}

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
