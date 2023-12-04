#ifndef MC_VECTOR_HPP
#define MC_VECTOR_HPP

#include <iostream>


template<unsigned int dim>
class Vector {
public:
  Vector();
  Vector(const double& s);
  Vector(const Vector<dim>& v);
  ~Vector();

  double& operator[](unsigned int idx);
  const double& operator[](unsigned int idx) const;
  Vector<dim>& operator=(const double& s);
  Vector<dim>& operator=(const Vector<dim>& v);

  Vector<dim> operator-() const;
  Vector<dim> operator+(const double& s) const;
  Vector<dim> operator-(const double& s) const;
  Vector<dim> operator*(const double& s) const;
  Vector<dim> operator/(const double& s) const;
  Vector<dim> operator+(const Vector<dim>& v) const;
  Vector<dim> operator-(const Vector<dim>& v) const;

  unsigned int size() {return m_dim;};
private:
  unsigned int m_dim;
  double m_elements[dim];
};

#include "vector.tpp"

#endif
