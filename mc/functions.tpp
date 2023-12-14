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

template<unsigned int dim_inp>
Polynomial<dim_inp>::Polynomial(std::string filepath)
  : Function<dim_inp, 1>() {

  std::ifstream file(filepath);
  assert(file.is_open());

  std::string line;

  // Check the function type
  std::getline(file, line);
  assert (line == "polynomial");
  // Check the dimensions
  std::getline(file, line);
  unsigned int d_inp, d_out;
  std::istringstream(line) >> d_inp >> d_out;
  assert (d_inp == dim_inp);
  assert (d_out == 1);
  // Check the third line (empty)
  std::getline(file, line);
  assert (line == "");

  // TODO: Avoid code repetition
  // Read the coefficients row by row
  while (!file.eof()){
    std::getline(file, line);
    std::istringstream linestream(line);
    try{
      std::vector<double> row = {std::istream_iterator<double>(linestream), std::istream_iterator<double>()};
      if (row.size() > 0) {
        assert (row.size() == dim_inp);
        m_coeffs.push_back(row);
      }
    }
    catch (std::invalid_argument &e){
      printf("Warning: Cannot parse \"%s\" as a row of coefficients.\n", line.c_str());
    }
  }

  file.close();
}

template<unsigned int dim_inp>
Polynomial<dim_inp>::Polynomial(std::vector<std::vector<double>> &coeffs)
  : Function<dim_inp, 1>(), m_coeffs(coeffs) {}

template<unsigned int dim_inp>
Polynomial<dim_inp>::Polynomial(const Polynomial<dim_inp>& p)
  : Function<dim_inp, 1>(), m_coeffs(p.m_coeffs) {}

template<unsigned int dim_inp>
Vector<1> Polynomial<dim_inp>::call(const Vector<dim_inp>& x) const {
  Vector<1> y = 0;
  Vector<dim_inp> x_powered = 1;
  for (int i = 0; i < m_coeffs.size(); ++i) {
    y = y + x_powered.dot(m_coeffs[i]);
    x_powered *= x;
  }
  return y;
}

template<unsigned int dim_inp>
SumExponential<dim_inp>::SumExponential(std::string filepath)
  : Function<dim_inp, 1>() {

  std::ifstream file(filepath);
  assert(file.is_open());

  std::string line;

  // Check the function type
  std::getline(file, line);
  assert (line == "sumexponential");
  // Check the dimensions
  std::getline(file, line);
  unsigned int d_inp, d_out;
  std::istringstream(line) >> d_inp >> d_out;
  assert (d_inp == dim_inp);
  assert (d_out == 1);
  // Check the third line (empty)
  std::getline(file, line);
  assert (line == "");

  // TODO: Avoid code repetition
  // Read the coefficients row by row
  while (!file.eof()){
    std::getline(file, line);
    std::istringstream linestream(line);
    try{
      std::vector<double> row = {std::istream_iterator<double>(linestream), std::istream_iterator<double>()};
      if (row.size() > 0) {
        assert (row.size() == dim_inp);
        m_coeffs.push_back(row);
      }
    }
    catch (std::invalid_argument &e){
      printf("Warning: Cannot parse \"%s\" as a row of coefficients.\n", line.c_str());
    }
  }

  file.close();
}

template<unsigned int dim_inp>
SumExponential<dim_inp>::SumExponential(std::vector<std::vector<double>> &coeffs)
  : Function<dim_inp, 1>(), m_coeffs(coeffs) {}

template<unsigned int dim_inp>
SumExponential<dim_inp>::SumExponential(const SumExponential<dim_inp>& f)
  : Function<dim_inp, 1>(), m_coeffs(f.m_coeffs) {}

template<unsigned int dim_inp>
Vector<1> SumExponential<dim_inp>::call(const Vector<dim_inp>& x) const {
  Vector<1> y = 0;
  for (int i = 0; i < m_coeffs.size(); ++i) {
    y += (i * x).exp().dot(m_coeffs[i]);
  }
  return y;
}

template<unsigned int dim_inp>
SumLogarithm<dim_inp>::SumLogarithm(std::string filepath)
  : Function<dim_inp, 1>() {

  std::ifstream file(filepath);
  assert(file.is_open());

  std::string line;

  // Check the function type
  std::getline(file, line);
  assert (line == "sumlogarithm");
  // Check the dimensions
  std::getline(file, line);
  unsigned int d_inp, d_out;
  std::istringstream(line) >> d_inp >> d_out;
  assert (d_inp == dim_inp);
  assert (d_out == 1);
  // Check the third line (empty)
  std::getline(file, line);
  assert (line == "");

  // TODO: Avoid code repetition
  // Read the coefficients row by row
  while (!file.eof()){
    std::getline(file, line);
    std::istringstream linestream(line);
    try{
      std::vector<double> row = {std::istream_iterator<double>(linestream), std::istream_iterator<double>()};
      if (row.size() > 0) {
        assert (row.size() == dim_inp);
        m_coeffs.push_back(row);
      }
    }
    catch (std::invalid_argument &e){
      printf("Warning: Cannot parse \"%s\" as a row of coefficients.\n", line.c_str());
    }
  }

  file.close();
}

template<unsigned int dim_inp>
SumLogarithm<dim_inp>::SumLogarithm(std::vector<std::vector<double>> &coeffs)
  : Function<dim_inp, 1>(), m_coeffs(coeffs) {}

template<unsigned int dim_inp>
SumLogarithm<dim_inp>::SumLogarithm(const SumLogarithm<dim_inp>& f)
  : Function<dim_inp, 1>(), m_coeffs(f.m_coeffs) {}

template<unsigned int dim_inp>
Vector<1> SumLogarithm<dim_inp>::call(const Vector<dim_inp>& x) const {
  Vector<1> y = 0;
  for (int i = 0; i < m_coeffs.size(); ++i) {
    y += ((i+1) * x).log().dot(m_coeffs[i]);
  }
  return y;
}

template<unsigned int dim_inp, unsigned int dim_out>
Linear<dim_inp, dim_out>::Linear(std::string filepath)
  : Function<dim_inp, dim_out>(){

  std::ifstream file(filepath);
  assert(file.is_open());

  std::string line;

  // Check the function type
  std::getline(file, line);
  assert (line == "linear");
  // Check the dimensions
  std::getline(file, line);
  unsigned int d_inp, d_out;
  std::istringstream(line) >> d_inp >> d_out;
  assert (d_inp == dim_inp);
  assert (d_out == dim_out);
  // Check the third line (empty)
  std::getline(file, line);
  assert (line == "");

  // Store the biases
  std::getline(file, line);
  std::istringstream linestream(line);
  std::vector<double> row = {std::istream_iterator<double>(linestream), std::istream_iterator<double>()};
  assert (row.size() == dim_out);
  m_biases = row;
  // Check the fifth line (empty)
  std::getline(file, line);
  assert (line == "");

  // TODO: Avoid code repetition
  // Read the coefficients row by row
  while (!file.eof()){
    std::getline(file, line);
    std::istringstream linestream(line);
    try{
      std::vector<double> row = {std::istream_iterator<double>(linestream), std::istream_iterator<double>()};
      if (row.size() > 0) {
        assert (row.size() == dim_inp);
        m_weights.push_back(row);
      }
    }
    catch (std::invalid_argument &e){
      printf("Warning: Cannot parse \"%s\" as a row of coefficients.\n", line.c_str());
    }
  }

  file.close();
}

template<unsigned int dim_inp, unsigned int dim_out>
Linear<dim_inp, dim_out>::Linear(std::vector<std::vector<double>> &weights, std::vector<double> &biases)
  : Function<dim_inp, dim_out>(), m_weights(weights), m_biases(biases) {}

template<unsigned int dim_inp, unsigned int dim_out>
Linear<dim_inp, dim_out>::Linear(const Linear<dim_inp, dim_out>& f)
  : Function<dim_inp, dim_out>(), m_weights(f.weights), m_biases(f.biases) {}

template<unsigned int dim_inp, unsigned int dim_out>
Vector<dim_out> Linear<dim_inp, dim_out>::call(const Vector<dim_inp>& x) const {
  Vector<dim_out> y = m_biases;
  for (std::vector<double> weight : m_weights) {
    y += x.dot(weight);
  }
  return y;
}
