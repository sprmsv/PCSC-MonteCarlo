#include "mathutils.hpp"

#include <cmath>
#include <cfloat>
#include <map>

bool isequal(double a, double b) {
    if (abs(a - b) < DBL_EPSILON) {
      return true;
    }
    else{
      return false;
    }
}

// TODO: Once cached values are increased, reduce the step size to improve accuracy
#define ERFINV_TOL 1e-03

double erfinv(double v) {
  // TODO: Assert v \in (-1, +1)

  // TODO: Read from file in compilation
  std::map<double, double> ERFINV_CACHED{
    {-1., -2.}, {0., 0.}, {1., 2.}
  };

  // Set the closest smaller cached values
  double v_lower = -1.;
  double z_lower = -2.;
  for (std::pair<double, double> p : ERFINV_CACHED){
    double& v_cached = p.first;
    double& z_cached = p.second;
    if (isequal(v_cached, v)) {
      return z_cached;
    }
    if ((v_cached < v) && (v_cached > v_lower)) {
        v_lower = v_cached;
        z_lower = z_cached;
    }
  }

  // Increment the lower bound until reaching the input
  for (; z_lower < 2.; z_lower+=ERFINV_TOL){
    v_lower = erf(z_lower);
    if (v_lower > v) {
        break;
    }
  }

  return z_lower;
}
