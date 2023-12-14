#ifndef MC_CLT_HPP
#define MC_CLT_HPP

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>
#include <iterator>
#include <fstream>

#include "distributions.hpp"
#include "sampler.hpp"
#include "functions.hpp"
#include "vector.hpp"
#include "io.hpp"
#include "exceptions.hpp"

template<int dim_inp, int dim_out>
class CLT {
public:
    CLT();
    ~CLT();
    CLT(Distribution<dim_inp>* dist, Function<dim_inp, dim_out>* func);
    CLT(const int N, const int n, Distribution<dim_inp>* dist, Function<dim_inp, dim_out>* func);

    std::vector<Vector<dim_out> run();
    void output(std::ostream& os = std::cout);
}

#include "clt.tpp"

#endif // MC_CLT_HPP