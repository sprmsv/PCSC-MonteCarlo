#include "vector.hpp"

// Constructors and destructor
template <unsigned int dim>
Vector<dim>::Vector() {}

template <unsigned int dim>
Vector<dim>::~Vector() {}

template <unsigned int dim>
Vector<dim>::Vector(const double& v) {
  for(unsigned int i=0; i<dim; ++i) {
    m_elements[i] = v;
  }
}

//// Internal operators
// Assignment operators
template <unsigned int dim>
Vector<dim>& Vector<dim>::operator=(const Vector<dim>& other) {
  for(unsigned int i=0; i<dim; ++i) {
    m_elements[i] = other[i];
  }
  return *this;
}

template <unsigned int dim>
Vector<dim>& Vector<dim>::operator=(const double& v) {
  for(unsigned int i=0; i<dim; ++i) {
    m_elements[i] = v;
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
Vector<dim>& Vector<dim>::operator-() const{
  Vector<dim> result;
  for(unsigned int i=0; i<dim; ++i) {
    result[i] = -m_elements[i];
  }
  return result;
}

// Arithmetic vector operators
template <unsigned int dim>
Vector<dim>& Vector<dim>::operator+(const Vector<dim>& other) const{
  Vector<dim> result;
  for(unsigned int i=0; i<dim; ++i) {
    result[i] = m_elements[i] + other[i];
  }
  return result;
}

template <unsigned int dim>
Vector<dim>& Vector<dim>::operator-(const Vector<dim>& other) const{
  Vector<dim> result;
  for(unsigned int i=0; i<dim; ++i) {
    result[i] = m_elements[i] - other[i];
  }
  return result;
}

template <unsigned int dim>
Vector<dim>& Vector<dim>::operator*(const Vector<dim>& other) const{
  Vector<dim> result;
  for(unsigned int i=0; i<dim; ++i) {
    result[i] = m_elements[i] * other[i];
  }
  return result;
}

// Arithmetic reassignment operators
template <unsigned int dim>
void Vector<dim>::operator+=(const Vector<dim>& other) {
  for(unsigned int i=0; i<dim; ++i) {
    m_elements[i] += other[i];
  }
}

template <unsigned int dim>
void Vector<dim>::operator-=(const Vector<dim>& other) {
  for(unsigned int i=0; i<dim; ++i) {
    m_elements[i] -= other[i];
  }
}

template <unsigned int dim>
void Vector<dim>::operator*=(const Vector<dim>& other) {
  for(unsigned int i=0; i<dim; ++i) {
    m_elements[i] *= other[i];
  }
}

template <unsigned int dim>
void Vector<dim>::operator/=(const Vector<dim>& other) {
  for(unsigned int i=0; i<dim; ++i) {
    m_elements[i] /= other[i];
  }
}


// Arithmetic scalar operators
template <unsigned int dim>
Vector<dim>& Vector<dim>::operator+(const double& v) {
  Vector<dim> result;
  for(unsigned int i=0; i<dim; ++i) {
    result[i] = m_elements[i] + v;
  }
  return result;
}

template <unsigned int dim>
Vector<dim>& Vector<dim>::operator-(const double& v) {
  Vector<dim> result;
  for(unsigned int i=0; i<dim; ++i) {
    result[i] = m_elements[i] - v;
  }
  return result;
}

template <unsigned int dim>
Vector<dim>& Vector<dim>::operator*(const double& v) {
  Vector<dim> result;
  for(unsigned int i=0; i<dim; ++i) {
    result[i] = m_elements[i] * v;
  }
  return result;
}

template <unsigned int dim>
Vector<dim>& Vector<dim>::operator/(const double& v) {
  Vector<dim> result;
  for(unsigned int i=0; i<dim; ++i) {
    result[i] = m_elements[i] / v;
  }
  return result;
}

template <unsigned int dim>
Vector<dim>& Vector<dim>::operator^(unsigned int& d) {
  Vector<dim> result;
  for(unsigned int i=0; i<dim; ++i) {
    result[i] = pow(m_elements[i], d);
  }
  return result;
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
Vector<dim> operator+(const double& v, const Vector<dim>& other) {
  Vector<dim> result;
  for(unsigned int i=0; i<dim; ++i) {
    result[i] = v + other[i];
  }
  return result;
}

template <unsigned int dim>
Vector<dim> operator-(const double& v, const Vector<dim>& other) {
  Vector<dim> result;
  for(unsigned int i=0; i<dim; ++i) {
    result[i] = v - other[i];
  }
  return result;
}

template <unsigned int dim>
Vector<dim> operator*(const double& v, const Vector<dim>& other) {
  Vector<dim> result;
  for(unsigned int i=0; i<dim; ++i) {
    result[i] = v * other[i];
  }
  return result;
}

template <unsigned int dim>
Vector<dim> operator/(const double& v, const Vector<dim>& other) {
  Vector<dim> result;
  for(unsigned int i=0; i<dim; ++i) {
    result[i] = v / other[i];
  }
  return result;
}

template <unsigned int dim>
std::vector<double> Vector<dim>::to_std_vector() const {
  assert(dim > 0);
  std::vector<double> result(dim);
  for(unsigned int i=0; i<dim; ++i) {
    result[i] = m_elements[i];
  }
  return result;
}


