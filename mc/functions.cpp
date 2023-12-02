#include "functions.hpp"

#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>


template<>
Polynomial<double, double>::Polynomial(std::string filepath)
  : Function<double, double>()
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

template<>
Polynomial<double, double>::Polynomial(std::vector<double> &coeffs)
  : Function<double, double>(), m_coeffs(coeffs) {}

template<>
double Polynomial<double, double>::call(double x) {
  double y = 0;
  for (int i = 0; i < m_coeffs.size(); ++i) {
    y += m_coeffs[i] * pow(x, i);
  }
  return y;
}
