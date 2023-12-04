#include "vector.hpp"

template<unsigned int dim>
Vector<dim>::Vector() {}

template<unsigned int dim>
Vector<dim>::~Vector() {}

template<unsigned int dim>
Vector<dim>::Vector(const double& s) {
  for (int idx = 0; idx < dim; ++idx){
    m_elements[idx] = s;
  }
}

template<unsigned int dim>
Vector<dim>::Vector(const Vector<dim>& v) {
  for (int idx = 0; idx < dim; ++idx){
    m_elements[idx] = v[idx];
  }
}

template<unsigned int dim>
double& Vector<dim>::operator[](unsigned int idx){
  return m_elements[idx];
}

template<unsigned int dim>
const double& Vector<dim>::operator[](unsigned int idx) const{
  return m_elements[idx];
}

template<unsigned int dim>
Vector<dim>& Vector<dim>::operator=(const double& s){
  for (int idx = 0; idx < dim; ++idx){
    m_elements[idx] = s;
  }
  return *this;
}

template<unsigned int dim>
Vector<dim>& Vector<dim>::operator=(const Vector<dim>& v){
  for (int idx = 0; idx < dim; ++idx){
    m_elements[idx] = v[idx];
  }
  return *this;
}

template<unsigned int dim>
Vector<dim> Vector<dim>::operator-() const {
  Vector<dim> u(*this);
  for (int idx = 0; idx < dim; ++idx){
    u[idx] *= -1;
  }
  return u;
}

template<unsigned int dim>
Vector<dim> Vector<dim>::operator+(const double& s) const {
  Vector<dim> u(*this);
  for (int idx = 0; idx < dim; ++idx){
    u[idx] += s;
  }
  return u;
}

template<unsigned int dim>
Vector<dim> Vector<dim>::operator-(const double& s) const {
  Vector<dim> u(*this);
  for (int idx = 0; idx < dim; ++idx){
    u[idx] -= s;
  }
  return u;
}

template<unsigned int dim>
Vector<dim> Vector<dim>::operator*(const double& s) const {
  Vector<dim> u(*this);
  for (int idx = 0; idx < dim; ++idx){
    u[idx] *= s;
  }
  return u;
}

template<unsigned int dim>
Vector<dim> Vector<dim>::operator/(const double& s) const {
  Vector<dim> u(*this);
  for (int idx = 0; idx < dim; ++idx){
    u[idx] /= s;
  }
  return u;
}

template<unsigned int dim>
Vector<dim> Vector<dim>::operator+(const Vector<dim>& v) const {
  Vector<dim> u(*this);
  for (int idx = 0; idx < dim; ++idx){
    u[idx] += v[idx];
  }
  return u;
}

template<unsigned int dim>
Vector<dim> Vector<dim>::operator-(const Vector<dim>& v) const {
  Vector<dim> u(*this);
  for (int idx = 0; idx < dim; ++idx){
    u[idx] -= v[idx];
  }
  return u;
}

template<unsigned int dim>
Vector<dim> Vector<dim>::operator*(const Vector<dim>& v) const {
  Vector<dim> u(*this);
  for (int idx = 0; idx < dim; ++idx){
    u[idx] *= v[idx];
  }
  return u;
}

template<unsigned int dim>
Vector<dim> Vector<dim>::operator/(const Vector<dim>& v) const {
  Vector<dim> u(*this);
  for (int idx = 0; idx < dim; ++idx){
    u[idx] /= v[idx];
  }
  return u;
}

template<unsigned int dim>
std::ostream& operator<<(std::ostream& stream, const Vector<dim>& v) {
  for (int idx = 0; idx < dim; ++idx){
    stream << v[idx];
    if (idx < dim - 1){
      stream << " ";
    }
  }

  return stream;
}
