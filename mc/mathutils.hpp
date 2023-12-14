#ifndef MC_MATHUTILS_HPP
#define MC_MATHUTILS_HPP

#include <cmath>
#include <cfloat>
#include <map>
#include <fstream>
#include <string>
#include <sstream>


bool isequal(double a, double b);

std::vector<std::vector<double>> read_matrix(std::ifstream& fstream, int rows, int cols);

// CHECK: Use boost/math/special_functions/detail/erf_inv.hpp instead?
double erfinv(double v);

#endif
