#ifndef MC_MATHUTILS_HPP
#define MC_MATHUTILS_HPP

#include "exceptions.hpp"

#include <cmath>
#include <cfloat>
#include <map>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>


/**
 * @brief Returns true if two doubles are equal with a tolerance.
 * The tolerance is the resolution of the double type.
 * @param a First double.
 * @param b Second double.
 * @return true if the inputs are equal.
 * @return false if the inputs are not equal.
 */
bool isequal(double a, double b);

/**
 * @brief Reads a matrix from an input file stream.
 * The first rows of the file stream are read and processed line-by-line.
 * If the input stream is invalid, an InvalidInputException exception is thrown.
 * @param fstream The input file stream.
 * @param rows The number of the rows of the matrix.
 * @param cols The number of the columns of the matrix.
 * @return std::vector<std::vector<double>> The constructed matrix.
 */
std::vector<std::vector<double>> read_matrix(std::ifstream& fstream, int rows, int cols);

/// @brief The accuracy of the inverse error function output.
#define ERFINV_TOL 1e-05

/// @brief The maximum returned value by the inverse error function when approaching -1 or +1.
#define ERFINV_MAX 10.

/**
 * @brief Inverse error function.
 * This is a naive implementation of the inverse error function.
 * 1000 pairs of input/output values of the error function are cached.
 * The function loops over them to find the closest value to the input,
 * and then increments the cached value and calculates the error function
 * using the standard math library to finally reach the input value.
 *
 * The current tolerance (increment step) is set to 1e-05. Decreasing the tolerance makes the calls slower.
 * However, the speed can be maintained if the number of the cached pairs are increased correspondingly.
 *
 * More advanced implementations or available in the
 * [Boost library](https://www.boost.org/doc/libs/1_59_0/boost/math/special_functions/detail/erf_inv.hpp).
 *
 * @param v The input \f$ v \in (-1, +1) \f$.
 * @return double The output (\f$ z \in R \f$) of the inverse error function so that \f$ {erf}(z) = v \f$.
 */
double erfinv(double v);

#endif
