#include "functions.hpp"

#include <gtest/gtest.h>
#include <vector>
#include <cmath>
#include <string>


namespace {

#define dim 3

class PolynomialTest : public ::testing::Test
{
protected:
  Polynomial<dim>* f;

  virtual void SetUp() override {
    f = new Polynomial<dim>(std::string(PROJECT_SOURCE_DIR) + "/tests/data/poly.dat");
  };

  virtual void TearDown() override {
    delete f;
  };
};

class MultivariatePolynomialTest : public ::testing::Test
{
protected:
  MultivariatePolynomial<3, 4, 2>* f;

  virtual void SetUp() override {
    f = new MultivariatePolynomial<3, 4, 2>(std::string(PROJECT_SOURCE_DIR) + "/tests/data/multipoly.dat");
  };

  virtual void TearDown() override {
    delete f;
  };
};

class LinearTest : public ::testing::Test
{
protected:
  Linear<3, 4>* f;

  virtual void SetUp() override {
    f = new Linear<3, 4>(std::string(PROJECT_SOURCE_DIR) + "/tests/data/linear.dat");
  };

  virtual void TearDown() override {
    delete f;
  };
};

class SumExponentialTest : public ::testing::Test
{
protected:
  SumExponential<dim>* f;

  virtual void SetUp() override {
    f = new SumExponential<dim>(std::string(PROJECT_SOURCE_DIR) + "/tests/data/sumexp.dat");
  };

  virtual void TearDown() override {
    delete f;
  };
};

class SumLogarithmTest : public ::testing::Test
{
protected:
  SumLogarithm<dim>* f;

  virtual void SetUp() override {
    f = new SumLogarithm<dim>(std::string(PROJECT_SOURCE_DIR) + "/tests/data/sumlog.dat");
  };

  virtual void TearDown() override {
    delete f;
  };
};

class CombinationTest : public ::testing::Test
{
protected:
  Polynomial<dim>* f1;
  SumExponential<dim>* f2;
  SumLogarithm<dim>* f3;

  virtual void SetUp() override {
    f1 = new Polynomial<dim>(std::string(PROJECT_SOURCE_DIR) + "/tests/data/poly.dat");
    f2 = new SumExponential<dim>(std::string(PROJECT_SOURCE_DIR) + "/tests/data/sumexp.dat");
    f3 = new SumLogarithm<dim>(std::string(PROJECT_SOURCE_DIR) + "/tests/data/sumlog.dat");
  };

  virtual void TearDown() override {
    delete f1;
    delete f2;
    delete f3;
  };
};

TEST_F(PolynomialTest, PolynomialEval) {
  Vector<dim> x = 1.;
  double y = (*f)(x)[0];
  EXPECT_DOUBLE_EQ(y, 14.300000);
}

TEST_F(MultivariatePolynomialTest, MultivariatePolynomialEval) {
  Vector<dim> x(std::vector<double>({2., 0., 1.}));
  Vector<4> y = (*f)(x);

  EXPECT_DOUBLE_EQ(y[0], 23.400000);
  EXPECT_DOUBLE_EQ(y[1], 2.400000);
  EXPECT_DOUBLE_EQ(y[2], 12.000000);
  EXPECT_DOUBLE_EQ(y[3], 11.000000);
}

TEST_F(LinearTest, LinearEval) {
  Vector<3> x(std::vector<double>({1., 0., 1.}));
  Vector<4> y = (*f)(x);

  // [7.2 1.2 4.5 3.5]
  EXPECT_DOUBLE_EQ(y[0], 7.2);
  EXPECT_DOUBLE_EQ(y[1], 1.2);
  EXPECT_DOUBLE_EQ(y[2], 4.5);
  EXPECT_DOUBLE_EQ(y[3], 3.5);
}

TEST_F(SumExponentialTest, SumExponentialEval) {
  Vector<dim> x(std::vector<double>({2., 0., 1.}));
  double y = (*f)(x)[0];
  EXPECT_DOUBLE_EQ(y, 83.094544059464582);
}

TEST_F(SumLogarithmTest, SumLogarithmEval) {
  Vector<dim> x = 1.;
  double y = (*f)(x)[0];
  EXPECT_DOUBLE_EQ(y, 7.1670378769122198);
}

TEST_F(CombinationTest, CombinedSum) {
  // Check that the sum of two functions is evaluated correctly
  Vector<dim> x = 1.;
  double y12 = ((*f1) + (*f2))(x)[0];
  EXPECT_DOUBLE_EQ(y12, 63.447633538017826);
  double y13 = ((*f1) + (*f3))(x)[0];
  EXPECT_DOUBLE_EQ(y13, 21.467037876912222);
  double y23 = ((*f2) + (*f3))(x)[0];
  EXPECT_DOUBLE_EQ(y23, 56.314671414930046);
  double y123 = ((*f1) + (*f2) + (*f3))(x)[0];
  EXPECT_DOUBLE_EQ(y123, 70.614671414930044);
  // Check commutativity
  double y21 = ((*f2) + (*f1))(x)[0];
  EXPECT_DOUBLE_EQ(y12, y21);
}

TEST_F(CombinationTest, CombinedDiff) {
  // Check that the difference of two functions is evaluated correctly
  Vector<dim> x = 1.;
  double y12 = ((*f1) - (*f2))(x)[0];
  EXPECT_DOUBLE_EQ(y12, -34.847633538017831);
  double y13 = ((*f1) - (*f3))(x)[0];
  EXPECT_DOUBLE_EQ(y13, 7.1329621230877809);
  double y23 = ((*f2) - (*f3))(x)[0];
  EXPECT_DOUBLE_EQ(y23, 41.98059566110561);
  double y123 = ((*f1) - (*f2) - (*f3))(x)[0];
  EXPECT_DOUBLE_EQ(y123, -42.014671414930049);

  // Check commutativity
  double y21 = ((*f2) - (*f1))(x)[0];
  EXPECT_DOUBLE_EQ(y12, -y21);
}

TEST_F(CombinationTest, CombinedProd) {
  // Check that the product of two functions is evaluated correctly
  Vector<dim> x = 1.;
  double y12 = ((*f1) * (*f2))(x)[0];
  EXPECT_DOUBLE_EQ(y12, 702.81115959365502);
  double y13 = ((*f1) * (*f3))(x)[0];
  EXPECT_DOUBLE_EQ(y13, 102.48864163984474);
  double y23 = ((*f2) * (*f3))(x)[0];
  EXPECT_DOUBLE_EQ(y23, 352.24295112757511);
  double y123 = ((*f1) * (*f2) * (*f3))(x)[0];
  EXPECT_DOUBLE_EQ(y123, 5037.0742011243246);

  // Check commutativity
  double y21 = ((*f2) * (*f1))(x)[0];
  EXPECT_DOUBLE_EQ(y12, y21);
}

TEST_F(CombinationTest, CombinedDiv) {
  // Check that the division of two functions is evaluated correctly
  Vector<dim> x = 1.;
  double y12 = ((*f1) / (*f2))(x)[0];
  EXPECT_DOUBLE_EQ(y12, 0.29096009249231358);
  double y13 = ((*f1) / (*f3))(x)[0];
  EXPECT_DOUBLE_EQ(y13, 1.995245489920709);
  double y23 = ((*f2) / (*f3))(x)[0];
  EXPECT_DOUBLE_EQ(y23,  6.8574541368535558);
  double y123 = ((*f1) / (*f2) / (*f3))(x)[0];
  EXPECT_DOUBLE_EQ(y123, 0.040596979880573494);

  // Check commutativity
  double y21 = ((*f2) / (*f1))(x)[0];
  EXPECT_DOUBLE_EQ(y12, 1/y21);
}

TEST_F(CombinationTest, ComplexCombination) {
  Vector<dim> x = 1.;
  double y1 = ((*f1) + (*f2) * (*f3))(x)[0];
  double y2 = ((*f1) + ((*f2) * (*f3)))(x)[0];
  double y3 = (((*f1) + (*f2)) * (*f3))(x)[0];
  EXPECT_DOUBLE_EQ(y1, 366.54295112757512);
  EXPECT_DOUBLE_EQ(y2, 366.54295112757512);
  EXPECT_DOUBLE_EQ(y3, 454.73159276741984);
}

} // namespace
