#include "vector.hpp"

// Constructors and destructor
template <unsigned int dim>
Vector<dim>::Vector() {}

template <unsigned int dim>
Vector<dim>::~Vector() {}

template <unsigned int dim>
Vector<dim>::Vector(const double& s) {
  for(unsigned int i=0; i<dim; ++i) {
    m_elements[i] = s;
  }
}

template <unsigned int dim>
Vector<dim>::Vector(const std::vector<double>& v) {
  assert(v.size() == dim);
  for(unsigned int i=0; i<dim; ++i) {
    m_elements[i] = v[i];
  }
}

template <unsigned int dim>
Vector<dim>::Vector(const Vector<dim>& v) {
  for(unsigned int i=0; i<dim; ++i) {
    m_elements[i] = v[i];
  }
}

template <unsigned int dim>
Vector<dim>::Vector(const Eigen::VectorXd& v) {
  assert(v.size() == dim);
  for(unsigned int i=0; i<dim; ++i) {
    m_elements[i] = v[i];
  }
}

//// Internal operators
// Assignment operators

template <unsigned int dim>
Vector<dim>& Vector<dim>::operator=(const Vector<dim>& v) {
  for(unsigned int i=0; i<dim; ++i) {
    m_elements[i] = v[i];
  }
  return *this;
}

template <unsigned int dim>
Vector<dim>& Vector<dim>::operator=(const double& s) {
  for(unsigned int i=0; i<dim; ++i) {
    m_elements[i] = s;
  }
  return *this;
}

template <unsigned int dim>
Vector<dim>& Vector<dim>::operator=(const std::vector<double>& v) {
  assert(v.size() == dim);
  for(unsigned int i=0; i<dim; ++i) {
    m_elements[i] = v[i];
  }
  return *this;
}

// Access operators

template <unsigned int dim>
double& Vector<dim>::operator[](unsigned int idx) {
  return m_elements[idx];
}

template <unsigned int dim>
const double& Vector<dim>::operator[](unsigned int idx) const {
  return m_elements[idx];
}

// Opposite operator
template <unsigned int dim>
Vector<dim> Vector<dim>::operator-() const{
  Vector<dim> u(*this);
  for (int idx = 0; idx < dim; ++idx){
    u[idx] *= -1;
  }
  return u;
}

// Absolute function
template <unsigned int dim>
Vector<dim> Vector<dim>::abs() const{
  Vector<dim> u(*this);
  for (int idx = 0; idx < dim; ++idx){
    u[idx] = std::abs(u[idx]);
  }
  return u;
}

// Arithmetic vector operators
template <unsigned int dim>
Vector<dim> Vector<dim>::operator+(const Vector<dim>& v) const{
  Vector<dim> u(*this);
  for (int idx = 0; idx < dim; ++idx){
    u[idx] += v[idx];
  }
  return u;
}

template <unsigned int dim>
Vector<dim> Vector<dim>::operator-(const Vector<dim>& v) const{
  Vector<dim> u(*this);
  for (int idx = 0; idx < dim; ++idx){
    u[idx] -= v[idx];
  }
  return u;
}

template <unsigned int dim>
Vector<dim> Vector<dim>::operator*(const Vector<dim>& v) const{
  Vector<dim> u(*this);
  for (int idx = 0; idx < dim; ++idx){
    u[idx] *= v[idx];
  }
  return u;
}

template <unsigned int dim>
Vector<dim> Vector<dim>::operator/(const Vector<dim>& v) const{
  Vector<dim> u(*this);
  for (int idx = 0; idx < dim; ++idx){
    u[idx] /= v[idx];
  }
  return u;
}

// Arithmetic reassignment operators
template <unsigned int dim>
Vector<dim>& Vector<dim>::operator+=(const Vector<dim>& v) {
  for(unsigned int i=0; i<dim; ++i) {
    m_elements[i] += v[i];
  }
  return *this;
}

template <unsigned int dim>
Vector<dim>& Vector<dim>::operator-=(const Vector<dim>& v) {
  for(unsigned int i=0; i<dim; ++i) {
    m_elements[i] -= v[i];
  }
  return *this;
}

template <unsigned int dim>
Vector<dim>& Vector<dim>::operator*=(const Vector<dim>& v) {
  for(unsigned int i=0; i<dim; ++i) {
    m_elements[i] *= v[i];
  }
  return *this;
}

template <unsigned int dim>
Vector<dim>& Vector<dim>::operator/=(const Vector<dim>& v) {
  for(unsigned int i=0; i<dim; ++i) {
    m_elements[i] /= v[i];
  }
  return *this;
}


// Arithmetic scalar operators
template <unsigned int dim>
Vector<dim> Vector<dim>::operator+(const double& s) {
  Vector<dim> u(*this);
  for (int idx = 0; idx < dim; ++idx){
    u[idx] += s;
  }
  return u;
}

template <unsigned int dim>
Vector<dim> Vector<dim>::operator-(const double& s) {
  Vector<dim> u(*this);
  for (int idx = 0; idx < dim; ++idx){
    u[idx] -= s;
  }
  return u;
}

template <unsigned int dim>
Vector<dim> Vector<dim>::operator*(const double& s) {
  Vector<dim> u(*this);
  for (int idx = 0; idx < dim; ++idx){
    u[idx] *= s;
  }
  return u;
}

template <unsigned int dim>
Vector<dim> Vector<dim>::operator/(const double& s) {
  Vector<dim> u(*this);
  for (int idx = 0; idx < dim; ++idx){
    u[idx] /= s;
  }
  return u;
}

template <unsigned int dim>
Vector<dim> Vector<dim>::operator^(const double& s) {
  Vector<dim> u(*this);
  for(unsigned int i=0; i<dim; ++i) {
    u[i] = pow(u[i], s);
  }
  return u;
}

// Arithmetic reassignment operators with doubles
template <unsigned int dim>
Vector<dim>& Vector<dim>::operator+=(const double& s) {
  for(unsigned int i=0; i<dim; ++i) {
    m_elements[i] += s;
  }
  return *this;
}

template <unsigned int dim>
Vector<dim>& Vector<dim>::operator-=(const double& s) {
  for(unsigned int i=0; i<dim; ++i) {
    m_elements[i] -= s;
  }
  return *this;
}

template <unsigned int dim>
Vector<dim>& Vector<dim>::operator*=(const double& s) {
  for(unsigned int i=0; i<dim; ++i) {
    m_elements[i] *= s;
  }
  return *this;
}

template <unsigned int dim>
Vector<dim>& Vector<dim>::operator/=(const double& s) {
  for(unsigned int i=0; i<dim; ++i) {
    m_elements[i] /= s;
  }
  return *this;
}

// Display operator
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

//// External operators
// Arithmetic scalar operators
template <unsigned int dim>
Vector<dim> operator+(const double& s, const Vector<dim>& u) {
  Vector<dim> v(u);
  for(unsigned int i=0; i<dim; ++i) {
    v[i] += s;
  }
  return v;
}

template <unsigned int dim>
Vector<dim> operator-(const double& s, const Vector<dim>& u) {
  Vector<dim> v(u);
  for(unsigned int i=0; i<dim; ++i) {
    v[i] -= s;
  }
  return v;
}

template <unsigned int dim>
Vector<dim> operator*(const double& s, const Vector<dim>& u) {
  Vector<dim> v(u);
  for(unsigned int i=0; i<dim; ++i) {
    v[i] *= s;
  }
  return v;
}

template <unsigned int dim>
Vector<dim> operator/(const double& s, const Vector<dim>& u) {
  Vector<dim> v(u);
  for(unsigned int i=0; i<dim; ++i) {
    v[i] /= s;
  }
  return v;
}

template <unsigned int dim>
std::vector<double> Vector<dim>::to_std_vector() const {
  assert(dim > 0);
  std::vector<double> v(dim);
  for(unsigned int i=0; i<dim; ++i) {
    v[i] = m_elements[i];
  }
  return v;
}
