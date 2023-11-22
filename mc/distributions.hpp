template<int dim>
class Distribution
{
public:
  Distribution();
  ~Distribution();
  virtual double pdf(double x[dim]) = 0;
  virtual double cdf(double x[dim]) = 0;
  virtual double* icdf(double p) = 0;
  double** sample(int n = 1);

private:
  int m_dim;
};

template<int dim>
class Normal : public Distribution<dim>
{
public:
  Normal();
  ~Normal();
};

template<int dim>
class Uniform : public Distribution<dim>
{
  Uniform();
  ~Uniform();
};

// Include separated implementations
#include "distributions.tpp"
