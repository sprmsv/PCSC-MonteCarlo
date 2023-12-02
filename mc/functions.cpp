#include "functions.hpp"

#include <cassert>
#include <fstream>
#include <iostream>

Scalar1DFunction::Scalar1DFunction() : Function<1, 1>() {}

Polynomial::Polynomial(std::string filepath) : Function<1, 1>() {
  std::ifstream file(filepath);
  assert(file.is_open());

  std::string line;
  while (file){
    std::getline(file, line);
    try{
      m_coeffs.push_back(std::stod(line));
    }
    catch (std::invalid_argument &e){
      if (line != ""){
        printf("Warning: Cannot parse \"%s\" as a coefficient.\n", line.c_str());
      }
    }
  }

  file.close();
}

Polynomial::Polynomial(std::vector<double> &coeffs)
  : Function<1, 1>(), m_coeffs(coeffs) {}
