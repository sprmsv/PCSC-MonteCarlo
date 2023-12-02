#include "functions.hpp"

template <unsigned int dim_inp, unsigned int dim_out>
Function<dim_inp, dim_out>::Function() {}

template <unsigned int dim_inp>
ScalarMDFunction<dim_inp>::ScalarMDFunction() : Function<dim_inp, 1>() {}
