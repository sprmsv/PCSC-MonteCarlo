#ifndef MC_FUNCTIONS_HPP
#define MC_FUNCTIONS_HPP

#include "sampler.hpp"
#include "distributions.hpp"
#include "vector.hpp"

#include <Eigen/Core>

#include <string>
#include <vector>
#include <memory>

template <unsigned int dim_inp, unsigned int dim_out> class CombinedFunctionSum;
template <unsigned int dim_inp, unsigned int dim_out> class CombinedFunctionSub;
template <unsigned int dim_inp, unsigned int dim_out> class CombinedFunctionMul;
template <unsigned int dim_inp, unsigned int dim_out> class CombinedFunctionDiv;

template <unsigned int dim_inp, unsigned int dim_out>
class Function {
public:
  // Constructors and destructors
  Function();
  virtual ~Function();
  Function(const Function<dim_inp, dim_out>&);
  // Call operators
  Vector<dim_out> operator()(const Vector<dim_inp>& x);
  std::shared_ptr<std::vector<Vector<dim_out>>> operator()(std::shared_ptr<std::vector<Vector<dim_inp>>> x);
  // Arithmetic operators
  CombinedFunctionSum<dim_inp, dim_out> operator+(const Function<dim_inp, dim_out>&) const;
  CombinedFunctionSub<dim_inp, dim_out> operator-(const Function<dim_inp, dim_out>&) const;
  CombinedFunctionMul<dim_inp, dim_out> operator*(const Function<dim_inp, dim_out>&) const;
  CombinedFunctionDiv<dim_inp, dim_out> operator/(const Function<dim_inp, dim_out>&) const;

  // Member functions
  virtual Vector<dim_out> call(const Vector<dim_inp>& x) const = 0;
  std::unique_ptr<MonteCarloApproximator<dim_out>> mca(unsigned int n, Distribution<dim_inp>* dist);
  Vector<dim_out> mean(unsigned int n, Distribution<dim_inp>* dist);
  Vector<dim_out> var(unsigned int n, Distribution<dim_inp>* dist);
};

template <unsigned int dim_inp, unsigned int dim_out>
class CombinedFunction : public Function<dim_inp, dim_out> {
public:
  CombinedFunction(const Function<dim_inp, dim_out>& f1, const Function<dim_inp, dim_out>& f2);
  CombinedFunction(const CombinedFunction<dim_inp, dim_out>& f);
  const Function<dim_inp, dim_out>& m_f1;
  const Function<dim_inp, dim_out>& m_f2;
};

template <unsigned int dim_inp, unsigned int dim_out>
class CombinedFunctionSum : public CombinedFunction<dim_inp, dim_out> {
public:
  CombinedFunctionSum(const Function<dim_inp, dim_out>& f1, const Function<dim_inp, dim_out>& f2);
  CombinedFunctionSum(const CombinedFunctionSum<dim_inp, dim_out>& f);
  template <typename ...Args> CombinedFunctionSum(
    const Function<dim_inp, dim_out>& f1, const Function<dim_inp, dim_out>& f2, const Args&... args)
    : CombinedFunctionSum<dim_inp, dim_out>(f1, CombinedFunctionSum<dim_inp, dim_out>(f2, args...)) {};
  Vector<dim_out> call(const Vector<dim_inp>& x) const override;
};

template <unsigned int dim_inp, unsigned int dim_out>
class CombinedFunctionSub : public CombinedFunction<dim_inp, dim_out> {
public:
  CombinedFunctionSub(const Function<dim_inp, dim_out>& f1, const Function<dim_inp, dim_out>& f2);
  CombinedFunctionSub(const CombinedFunctionSub<dim_inp, dim_out>& f);
  template <typename ...Args> CombinedFunctionSub(
    const Function<dim_inp, dim_out>& f1, const Function<dim_inp, dim_out>& f2, const Args&... args)
    : CombinedFunctionSub<dim_inp, dim_out>(f1, CombinedFunctionSub<dim_inp, dim_out>(f2, args...)) {};
  Vector<dim_out> call(const Vector<dim_inp>& x) const override;
};

template <unsigned int dim_inp, unsigned int dim_out>
class CombinedFunctionMul : public CombinedFunction<dim_inp, dim_out> {
public:
  CombinedFunctionMul(const Function<dim_inp, dim_out>& f1, const Function<dim_inp, dim_out>& f2);
  CombinedFunctionMul(const CombinedFunctionMul<dim_inp, dim_out>& f);
  template <typename ...Args> CombinedFunctionMul(
    const Function<dim_inp, dim_out>& f1, const Function<dim_inp, dim_out>& f2, const Args&... args)
    : CombinedFunctionMul<dim_inp, dim_out>(f1, CombinedFunctionMul<dim_inp, dim_out>(f2, args...)) {};
  Vector<dim_out> call(const Vector<dim_inp>& x) const override;
};

template <unsigned int dim_inp, unsigned int dim_out>
class CombinedFunctionDiv : public CombinedFunction<dim_inp, dim_out> {
public:
  CombinedFunctionDiv(const Function<dim_inp, dim_out>& f1, const Function<dim_inp, dim_out>& f2);
  CombinedFunctionDiv(const CombinedFunctionDiv<dim_inp, dim_out>& f);
  template <typename ...Args> CombinedFunctionDiv(
    const Function<dim_inp, dim_out>& f1, const Function<dim_inp, dim_out>& f2, const Args&... args)
    : CombinedFunctionDiv<dim_inp, dim_out>(f1, CombinedFunctionDiv<dim_inp, dim_out>(f2, args...)) {};
  Vector<dim_out> call(const Vector<dim_inp>& x) const override;
};

template <unsigned int dim_inp, unsigned int dim_out>
class Polynomial : public Function<dim_inp, dim_out>
{
public:
  Polynomial(std::string filepath);
  Polynomial(std::vector<double> &coeffs);
  Polynomial(const Polynomial<dim_inp, dim_out>&);
  ~Polynomial() = default;
  std::vector<double> m_coeffs;

  Vector<dim_out> call(const Vector<dim_inp>& x) const override;
};

#include "functions.tpp"

#endif
