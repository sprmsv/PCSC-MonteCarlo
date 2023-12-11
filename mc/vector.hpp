#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <Eigen/Core>

#include <iostream>
#include <cmath>
#include <vector>

template <unsigned int dim = 1>
class Vector
{
public:
    // Constructors and destructor
    Vector();
    Vector(const double&);
    Vector(const std::vector<double>&);
    Vector(const Vector<dim>&);
    Vector(const Eigen::VectorXd&);
    ~Vector();

    // Assignment operators
    Vector<dim>& operator=(const Vector<dim>&);
    Vector<dim>& operator=(const double&);
    Vector<dim>& operator=(const std::vector<double>&);

    // Access operators
    double& operator[](unsigned int idx);
    const double& operator[](unsigned int idx) const;

    // Self operators
    Vector<dim> operator-() const;
    Vector<dim> abs() const;

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
