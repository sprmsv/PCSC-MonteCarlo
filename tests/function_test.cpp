#include <gtest/gtest.h>
#include <vector>
#include <cmath>

#include "functions.hpp"

namespace{

#define dim 3

class PolynomialTest : public ::testing::Test {
protected:
    Polynomial<dim>* f;

    virtual void SetUp() override{
        f = new Polynomial<dim>("../tests/data/poly.dat");
    };
    virtual void TearDown() override{
        delete f;
    };
};

class LinearTest : public ::testing::Test {
protected:
    Linear<3, 4>* f;

    virtual void SetUp() override{
        f = new Linear<3, 4>("../tests/data/linear.dat");
      };
    virtual void TearDown() override{
        delete f;
    };
};

class SumExponentialTest : public ::testing::Test {
protected:
    SumExponential<dim>* f;

    virtual void SetUp() override{
        f = new SumExponential<dim>("../tests/data/sumexp.dat");
    };
    virtual void TearDown() override{
        delete f;
    };
};

class SumLogarithmTest : public ::testing::Test {
protected:
    SumLogarithm<dim>* f;

    virtual void SetUp() override{
        f = new SumLogarithm<dim>("../tests/data/sumlog.dat");
    };
    virtual void TearDown() override{
        delete f;
    };
};

class CombinationTest : public ::testing::Test {
protected:
    Polynomial<dim>* f1;
    SumExponential<dim>* f2;
    SumLogarithm<dim>* f3;

    virtual void SetUp() override{
        f1 = new Polynomial<dim>("data/poly.dat");
        f2 = new SumExponential<dim>("data/sumexp.dat");
        f3 = new SumLogarithm<dim>("data/sumlog.dat");
    };
    virtual void TearDown() override{
        delete f1;
        delete f2;
        delete f3;
    };
};

TEST_F(PolynomialTest, PolynomialEval)
{
    Vector<dim> x = 1.;
    double y = (*f)(x)[0];
    EXPECT_DOUBLE_EQ(y, 14.300000);
}

// TODO : Modify once Multivariate is implemented
// TEST_F(LinearTest, LinearEval)
// {
//     Vector<3> x(std::vector<double>({1., 0., 1.}));
//     Vector<4> y = (*f)(x);

//     // [7.2 1.2 4.5 3.5]
//     EXPECT_DOUBLE_EQ(y[0], 7.2);
//     EXPECT_DOUBLE_EQ(y[1], 1.2);
//     EXPECT_DOUBLE_EQ(y[2], 4.5);
//     EXPECT_DOUBLE_EQ(y[3], 3.5);
// }

TEST_F(SumExponentialTest, SumExponentialEval)
{
    Vector<dim> x = 1.;
    double y = (*f)(x)[0];
    EXPECT_DOUBLE_EQ(y, 38.040295);
}

TEST_F(SumLogarithmTest, SumLogarithmEval)
{
    Vector<dim> x = 1.;
    double y = (*f)(x)[0];
    EXPECT_DOUBLE_EQ(y, 6.068425);
}

TEST_F(CombinationTest, CombinedSum){
    // Check that the sum of two functions is evaluated correctly
    Vector<dim> x = 1.;
    double y12 = ((*f1) + (*f2))(x)[0];
    EXPECT_DOUBLE_EQ(y12, 52.580295);
    double y13 = ((*f1) + (*f3))(x)[0];
    EXPECT_DOUBLE_EQ(y13, 20.608425);
    double y23 = ((*f2) + (*f3))(x)[0];
    EXPECT_DOUBLE_EQ(y23, 44.108425);
    double y123 = ((*f1) + (*f2) + (*f3))(x)[0];
    EXPECT_DOUBLE_EQ(y123, 62.148425);

    // Check commutativity
    double y21 = ((*f2) + (*f1))(x)[0];
    EXPECT_DOUBLE_EQ(y12, y21);
}

TEST_F(CombinationTest, CombinedDiff){
    // Check that the difference of two functions is evaluated correctly
    Vector<dim> x = 1.;
    double y12 = ((*f1) - (*f2))(x)[0];
    EXPECT_DOUBLE_EQ(y12, -23.500295);
    double y13 = ((*f1) - (*f3))(x)[0];
    EXPECT_DOUBLE_EQ(y13, 7.471575);
    double y23 = ((*f2) - (*f3))(x)[0];
    EXPECT_DOUBLE_EQ(y23, -16.028575);
    double y123 = ((*f1) - (*f2) - (*f3))(x)[0];
    EXPECT_DOUBLE_EQ(y123, -34.068575);

    // Check commutativity
    double y21 = ((*f2) - (*f1))(x)[0];
    EXPECT_DOUBLE_EQ(y12, -y21);
}

TEST_F(CombinationTest, CombinedProd){
    // Check that the product of two functions is evaluated correctly
    Vector<dim> x = 1.;
    double y12 = ((*f1) * (*f2))(x)[0];
    EXPECT_DOUBLE_EQ(y12, 553.680000);
    double y13 = ((*f1) * (*f3))(x)[0];
    EXPECT_DOUBLE_EQ(y13, 88.080000);
    double y23 = ((*f2) * (*f3))(x)[0];
    EXPECT_DOUBLE_EQ(y23, 418.080000);
    double y123 = ((*f1) * (*f2) * (*f3))(x)[0];
    EXPECT_DOUBLE_EQ(y123, 4680.960000);

    // Check commutativity
    double y21 = ((*f2) * (*f1))(x)[0];
    EXPECT_DOUBLE_EQ(y12, y21);
}

TEST_F(CombinationTest, CombinedDiv){
    // Check that the division of two functions is evaluated correctly
    Vector<dim> x = 1.;
    double y12 = ((*f1) / (*f2))(x)[0];
    EXPECT_DOUBLE_EQ(y12, 0.383333);
    double y13 = ((*f1) / (*f3))(x)[0];
    EXPECT_DOUBLE_EQ(y13, 2.400000);
    double y23 = ((*f2) / (*f3))(x)[0];
    EXPECT_DOUBLE_EQ(y23, 0.133333);
    double y123 = ((*f1) / (*f2) / (*f3))(x)[0];
    EXPECT_DOUBLE_EQ(y123, 0.016667);

    // Check commutativity
    double y21 = ((*f2) / (*f1))(x)[0];
    EXPECT_DOUBLE_EQ(y12, 1/y21);
}

TEST_F(CombinationTest, ComplexCombination){
// std::cout << "f1 + f2 * f3 = " << (f1 + f2 * f3)(x) << std::endl;
// std::cout << "f1 + (f2 * f3) = " << (f1 + (f2 * f3))(x) << std::endl;
// std::cout << "(f1 + f2) * f3 = " << ((f1 + f2) * f3)(x) << std::endl;
    Vector<dim> x = 1.;
    double y1 = ((*f1) + (*f2) * (*f3))(x)[0];
    double y2 = ((*f1) + ((*f2) * (*f3)))(x)[0];
    double y3 = (((*f1) + (*f2)) * (*f3))(x)[0];
    EXPECT_DOUBLE_EQ(y1, 245.3844869839);
    EXPECT_DOUBLE_EQ(y2, 245.3844869839);
    EXPECT_DOUBLE_EQ(y3, 319.0795766854);
}

}