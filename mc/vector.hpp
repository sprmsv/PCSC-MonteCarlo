#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "exceptions.hpp"

#include <Eigen/Core>

#include <iostream>
#include <cmath>
#include <vector>

/**
 * @brief Vector of doubles with fixed dimension
 * Class for storing and manipuating a vector of doubles.
 * The data is stored in a fixed-size double arary.
 * Element-wise arithmetic operators with other vectors or scalars are possible.
 * Constructing from a standard vector is also possible.
 * @tparam dim Dimension of the vector. Defaults to 1.
 */
template <unsigned int dim = 1>
class Vector
{
public:
  /// Construct a new Vector object from a scalar.
  Vector();
  /**
   * @brief Construct a new Vector object.
   * Initializes all the elements with a scalar.
   * @param s Scalar value to assign to all elements.
   */
  Vector(const double& s);
  /**
   * @brief Construct a new Vector object from a standard vector.
   * Initializes all the elements with the elements of the initializer.
   * The dimension of the vector must match with the size of the initializer.
   * @param v Initializer vector.
   */
  Vector(const std::vector<double>& v);
  /**
   * @brief Construct a new Vector object from another vector.
   * Initializes all the elements with the elements of the initializer.
   * The dimension of the vector must match with the size of the initializer.
   * @param v Initializer vector.
   */
  Vector(const Vector<dim>& v);
  /**
   * @brief Construct a new Vector object from a vector from Eigen.
   * Initializes all the elements with the elements of the initializer.
   * The dimension of the vector must match with the size of the initializer.
   * @param v Initializer vector.
   */
  Vector(const Eigen::VectorXd& v);
  /// @brief Destroy the Vector object
  ~Vector();

  /// @brief Assign the elements of the vector to another vector.
  Vector<dim>& operator=(const Vector<dim>& v);
  /// @brief Assign the elements of the vector to a scalar.
  Vector<dim>& operator=(const double& s);
  /// @brief Assign the elements of the vector to a standard vector.
  Vector<dim>& operator=(const std::vector<double>& v);

  /// @brief Access operator for accessing an element as a lvalue reference
  double& operator[](unsigned int idx);
  /// @brief Access operator for accessing an element as a rvalue reference
  const double& operator[](unsigned int idx) const;

  /// @brief Negation operator
  Vector<dim> operator-() const;

  /// @brief Gets absoulte values of all the elements of the vector
  /// @return A vector with absolute values of the original vector
  Vector<dim> abs() const;
  /// @brief Gets element-wise exponential of the vector
  /// @return A vector with exponential values of the original vector
  Vector<dim> exp() const;
  /// @brief Gets element-wise logarithm of the vector
  /// @return A vector with logarithm values of the original vector
  Vector<dim> log() const;

  /// @brief Operator for summation with another vector
  Vector<dim> operator+(const Vector<dim>&) const;
  /// @brief Operator for subtraction by another vector
  Vector<dim> operator-(const Vector<dim>&) const;
  /// @brief Operator for multiplication by another vector
  Vector<dim> operator*(const Vector<dim>&) const;
  /// @brief Operator for division by another vector
  Vector<dim> operator/(const Vector<dim>&) const;

  /// @brief Operator for assign-summation with another vector
  Vector<dim>& operator+=(const Vector<dim>&);
  /// @brief Operator for assign-subtraction by another vector
  Vector<dim>& operator-=(const Vector<dim>&);
  /// @brief Operator for assign-multiplication by another vector
  Vector<dim>& operator*=(const Vector<dim>&);
  /// @brief Operator for assign-division by another vector
  Vector<dim>& operator/=(const Vector<dim>&);

  /// @brief Operator for element-wise summation with a scalar
  Vector<dim> operator+(const double&);
  /// @brief Operator for element-wise subtraction by a scalar
  Vector<dim> operator-(const double&);
  /// @brief Operator for element-wise multiplication by a scalar
  Vector<dim> operator*(const double&);
  /// @brief Operator for element-wise division by a scalar
  Vector<dim> operator/(const double&);
  /// @brief Operator for element-wise power by a scalar
  Vector<dim> operator^(const double&);

  /// @brief Operator for element-wise assign-summation with a scalar
  Vector<dim>& operator+=(const double&);
  /// @brief Operator for element-wise assign-subtraction by a scalar
  Vector<dim>& operator-=(const double&);
  /// @brief Operator for element-wise assign-multiplication by a scalar
  Vector<dim>& operator*=(const double&);
  /// @brief Operator for element-wise assign-division by a scalar
  Vector<dim>& operator/=(const double&);

  /// @brief Perform a dot-product of the vector with another vector
  /// @param v The other vector with the same dimension
  /// @return The dot-product of the two vectors
  double dot(const Vector<dim>& v) const;

  /// @brief Convert the vector to a standard library vector
  /// @return A standard library vector with the same elements
  std::vector<double> to_std_vector() const;

private:
  /// @brief Array for storing the elements of the vector.
  double m_elements[dim];
};

#include "vector.tpp"

#endif
