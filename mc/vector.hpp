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
    Vector(const Vector<dim>& other);
    ~Vector();

    // Operators
    Vector& operator=(const Vector& other);
    Vector& operator=(const double& v);
    double& operator[](unsigned int idx); 
    const double& operator[](unsigned int idx) const;

    Vector<dim>& operator-() const;
    Vector<dim>& operator+(const Vector<dim>& other) const;
    Vector<dim>& operator-(const Vector<dim>& other) const;
    Vector<dim>& operator*(const Vector<dim>& other) const;
    void operator+=(const Vector<dim>& other);
    void operator-=(const Vector<dim>& other);
    void operator*=(const Vector<dim>& other);
    void operator/=(const Vector<dim>& other);
    Vector<dim>& operator+(const double& v);
    Vector<dim>& operator-(const double& v);
    Vector<dim>& operator*(const double& v);
    Vector<dim>& operator/(const double& v);
    Vector<dim>& operator^(unsigned int& d);

    std::vector<double> to_std_vector() const;
private:
    unsigned int m_dim;
    double m_elements[dim];
};

#include "vector.tpp"

#endif
