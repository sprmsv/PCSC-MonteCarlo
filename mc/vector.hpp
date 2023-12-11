#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <cmath>
#include <vector>

template <unsigned int dim = 1>
class Vector
{
public:
    // Constructors and destructor
    Vector();
    Vector(const double& v);
    Vector(const std::vector<double>& v);
    Vector(const Vector<dim>& other);
    ~Vector();

    // Assignment operators
    Vector<dim>& operator=(const Vector<dim>& other);
    Vector<dim>& operator=(const double& v);
    Vector<dim>& operator=(const std::vector<double>& v);

    // Access operators
    double& operator[](unsigned int idx);
    const double& operator[](unsigned int idx) const;

    // Self operators
    Vector<dim> operator-() const;

    // Arithmetic vector operators (element-wise)
    Vector<dim> operator+(const Vector<dim>&) const;
    Vector<dim> operator-(const Vector<dim>&) const;
    Vector<dim> operator*(const Vector<dim>&) const;
    Vector<dim> operator/(const Vector<dim>&) const;
    // Combined arithmetic vector operators (element-wise)
    Vector<dim>& operator+=(const Vector<dim>&);
    Vector<dim>& operator-=(const Vector<dim>&);
    Vector<dim>& operator*=(const Vector<dim>&);
    Vector<dim>& operator/=(const Vector<dim>&);

    // Arithmetic double operators
    Vector<dim> operator+(const double&);
    Vector<dim> operator-(const double&);
    Vector<dim> operator*(const double&);
    Vector<dim> operator/(const double&);
    Vector<dim> operator^(const double&);
    // Combined arithmetic double operators
    Vector<dim>& operator+=(const double&);
    Vector<dim>& operator-=(const double&);
    Vector<dim>& operator*=(const double&);
    Vector<dim>& operator/=(const double&);

    std::vector<double> to_std_vector() const;
private:
    unsigned int m_dim;
    double m_elements[dim];
};

#include "vector.tpp"

#endif
