#include "functions.hpp"

#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>

template <typename input, typename output>
Function<input, output>::Function() {}

template<typename input, typename output>
Polynomial<input, output>::Polynomial(std::string filepath)
  : Function<input, output>()
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

template<typename input, typename output>
Polynomial<input, output>::Polynomial(std::vector<double> &coeffs)
  : Function<input, output>(), m_coeffs(coeffs) {}

template<typename input, typename output>
output Polynomial<input, output>::call(const input& x) {
  output y = 0;
  input x_powered = 1;
  for (int i = 0; i < m_coeffs.size(); ++i) {
    y += m_coeffs[i] * x_powered;
    x_powered *= x;
  }
  return y;
}
