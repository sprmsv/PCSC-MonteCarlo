#ifndef MC_FUNCTIONS_HPP
#define MC_FUNCTIONS_HPP

#include <Eigen/Core>

#include <vector>
#include <string>


template <typename input, typename output>
class Function {
public:
  Function();
  output operator()(const input& x) {return this->call(x);};
  virtual output call(const input& x) = 0;
};

template <typename input, typename output>
class Polynomial : public Function<input, output> {
public:
  Polynomial(std::string filepath);
  Polynomial(std::vector<double> &coeffs);
  std::vector<double> m_coeffs;
  output call(const input& x) override;
};

#include "functions.tpp"

#endif
