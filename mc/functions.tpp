#include "functions.hpp"

#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>

template <unsigned int dim_inp, unsigned int dim_out>
Function<dim_inp, dim_out>::Function() {}

template <unsigned int dim_inp, unsigned int dim_out>
Function<dim_inp, dim_out>::Function(const Function<dim_inp, dim_out>& f) {}

template <unsigned int dim_inp, unsigned int dim_out>
Function<dim_inp, dim_out>::~Function() {}

template <unsigned int dim_inp, unsigned int dim_out>
Vector<dim_out> Function<dim_inp, dim_out>::operator()(const Vector<dim_inp>& x) {
  return this->call(x);
}

template <unsigned int dim_inp, unsigned int dim_out>
std::shared_ptr<std::vector<Vector<dim_out>>> Function<dim_inp, dim_out>::operator()(std::shared_ptr<std::vector<Vector<dim_inp>>> x) {
  std::shared_ptr<std::vector<Vector<dim_out>>> y(new std::vector<Vector<dim_out>>(x->size()));
  for (int i = 0; i < x->size(); ++i) {
    (*y)[i] = this->call((*x)[i]);
  }
  return y;
}

template <unsigned int dim_inp, unsigned int dim_out>
CombinedFunctionSum<dim_inp, dim_out> Function<dim_inp, dim_out>::operator+(const Function<dim_inp, dim_out>& f) const {
  CombinedFunctionSum<dim_inp, dim_out> out(*this, f);
  return out;
}

template <unsigned int dim_inp, unsigned int dim_out>
CombinedFunctionSub<dim_inp, dim_out> Function<dim_inp, dim_out>::operator-(const Function<dim_inp, dim_out>& f) const {
  CombinedFunctionSub<dim_inp, dim_out> out(*this, f);
  return out;
}

template <unsigned int dim_inp, unsigned int dim_out>
CombinedFunctionMul<dim_inp, dim_out> Function<dim_inp, dim_out>::operator*(const Function<dim_inp, dim_out>& f) const {
  CombinedFunctionMul<dim_inp, dim_out> out(*this, f);
  return out;
}

template <unsigned int dim_inp, unsigned int dim_out>
CombinedFunctionDiv<dim_inp, dim_out> Function<dim_inp, dim_out>::operator/(const Function<dim_inp, dim_out>& f) const {
  CombinedFunctionDiv<dim_inp, dim_out> out(*this, f);
  return out;
}

template <unsigned int dim_inp, unsigned int dim_out>
std::unique_ptr<MonteCarloApproximator<dim_out>> Function<dim_inp, dim_out>::mca(unsigned int n, Distribution<dim_inp>* dist) {
  auto samples = dist->samples(n);
  auto outputs = (*this)(samples);
  std::unique_ptr<MonteCarloApproximator<dim_out>> mca(new MonteCarloApproximator<dim_out>(outputs));
  return mca;
}

template <unsigned int dim_inp, unsigned int dim_out>
Vector<dim_out> Function<dim_inp, dim_out>::mean(unsigned int n, Distribution<dim_inp>* dist) {
  auto mca = this->mca(n, dist);
  return Vector<dim_out>(mca->mean());
}

template <unsigned int dim_inp, unsigned int dim_out>
Vector<dim_out> Function<dim_inp, dim_out>::var(unsigned int n, Distribution<dim_inp>* dist) {
  auto mca = this->mca(n, dist);
  return Vector<dim_out>(mca->var());
}

template<unsigned int dim_inp, unsigned int dim_out>
CombinedFunction<dim_inp, dim_out>::CombinedFunction(const Function<dim_inp, dim_out>& f1, const Function<dim_inp, dim_out>& f2)
  : Function<dim_inp, dim_out>(), m_f1(f1), m_f2(f2) {}

template<unsigned int dim_inp, unsigned int dim_out>
CombinedFunction<dim_inp, dim_out>::CombinedFunction(const CombinedFunction<dim_inp, dim_out>& f)
  : Function<dim_inp, dim_out>(), m_f1(f.m_f1), m_f2(f.m_f2) {}

template<unsigned int dim_inp, unsigned int dim_out>
CombinedFunctionSum<dim_inp, dim_out>::CombinedFunctionSum(const Function<dim_inp, dim_out>& f1, const Function<dim_inp, dim_out>& f2)
  : CombinedFunction<dim_inp, dim_out>(f1, f2) {}

template<unsigned int dim_inp, unsigned int dim_out>
CombinedFunctionSum<dim_inp, dim_out>::CombinedFunctionSum(const CombinedFunctionSum<dim_inp, dim_out>& f)
  : CombinedFunction<dim_inp, dim_out>(f.m_f1, f.m_f2) {}

template<unsigned int dim_inp, unsigned int dim_out>
Vector<dim_out> CombinedFunctionSum<dim_inp, dim_out>::call(const Vector<dim_inp>& x) const {
  Vector<dim_out> out = this->m_f1.call(x) + this->m_f2.call(x);
  return out;
}

template<unsigned int dim_inp, unsigned int dim_out>
CombinedFunctionSub<dim_inp, dim_out>::CombinedFunctionSub(const Function<dim_inp, dim_out>& f1, const Function<dim_inp, dim_out>& f2)
  : CombinedFunction<dim_inp, dim_out>(f1, f2) {}

template<unsigned int dim_inp, unsigned int dim_out>
CombinedFunctionSub<dim_inp, dim_out>::CombinedFunctionSub(const CombinedFunctionSub<dim_inp, dim_out>& f)
  : CombinedFunction<dim_inp, dim_out>(f.m_f1, f.m_f2) {}

template<unsigned int dim_inp, unsigned int dim_out>
Vector<dim_out> CombinedFunctionSub<dim_inp, dim_out>::call(const Vector<dim_inp>& x) const {
  Vector<dim_out> out = this->m_f1.call(x) - this->m_f2.call(x);
  return out;
}

template<unsigned int dim_inp, unsigned int dim_out>
CombinedFunctionMul<dim_inp, dim_out>::CombinedFunctionMul(const Function<dim_inp, dim_out>& f1, const Function<dim_inp, dim_out>& f2)
  : CombinedFunction<dim_inp, dim_out>(f1, f2) {}

template<unsigned int dim_inp, unsigned int dim_out>
CombinedFunctionMul<dim_inp, dim_out>::CombinedFunctionMul(const CombinedFunctionMul<dim_inp, dim_out>& f)
  : CombinedFunction<dim_inp, dim_out>(f.m_f1, f.m_f2) {}

template<unsigned int dim_inp, unsigned int dim_out>
Vector<dim_out> CombinedFunctionMul<dim_inp, dim_out>::call(const Vector<dim_inp>& x) const {
  Vector<dim_out> out = this->m_f1.call(x) * this->m_f2.call(x);
  return out;
}

template<unsigned int dim_inp, unsigned int dim_out>
CombinedFunctionDiv<dim_inp, dim_out>::CombinedFunctionDiv(const Function<dim_inp, dim_out>& f1, const Function<dim_inp, dim_out>& f2)
  : CombinedFunction<dim_inp, dim_out>(f1, f2) {}

template<unsigned int dim_inp, unsigned int dim_out>
CombinedFunctionDiv<dim_inp, dim_out>::CombinedFunctionDiv(const CombinedFunctionDiv<dim_inp, dim_out>& f)
  : CombinedFunction<dim_inp, dim_out>(f.m_f1, f.m_f2) {}

template<unsigned int dim_inp, unsigned int dim_out>
Vector<dim_out> CombinedFunctionDiv<dim_inp, dim_out>::call(const Vector<dim_inp>& x) const {
  Vector<dim_out> out = this->m_f1.call(x) / this->m_f2.call(x);
  return out;
}

template<unsigned int dim_inp, unsigned int dim_out>
Polynomial<dim_inp, dim_out>::Polynomial(std::string filepath)
  : Function<dim_inp, dim_out>() {
  std::ifstream file(filepath);
  assert(file.is_open());

  std::string line;

  // Pass the first two lines (function type and dimension)
  std::getline(file, line);
  std::getline(file, line);

  // Read the coefficients
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
Polynomial<dim_inp, dim_out>::Polynomial(std::vector<double> &coeffs)
  : Function<dim_inp, dim_out>(), m_coeffs(coeffs) {}

template<unsigned int dim_inp, unsigned int dim_out>
Polynomial<dim_inp, dim_out>::Polynomial(const Polynomial<dim_inp, dim_out>& p)
  : Function<dim_inp, dim_out>(), m_coeffs(p.m_coeffs) {}

template<unsigned int dim_inp, unsigned int dim_out>
Vector<dim_out> Polynomial<dim_inp, dim_out>::call(const Vector<dim_inp>& x) const {
  Vector<dim_out> y = 0;
  Vector<dim_inp> x_powered = 1;
  for (int i = 0; i < m_coeffs.size(); ++i) {
    y = y + x_powered * m_coeffs[i];
    x_powered = x_powered * x;
  }
  return y;
}
