#include <gtest/gtest.h>
#include <vector>
#include <cmath>

#include "functions.hpp"

namespace{

class FunctionTest : public ::testing::Test {
protected:
    // Define the function
    Function<5, 5>* f;

    virtual void SetUp() = 0;
    virtual void TearDown() = 0;
};

class PolynomialTest : public FunctionTest {
protected:
    // Define the coefficients of the polynomial
    std::vector<double>* coeffs;

    virtual void SetUp() override{
        coeffs = new std::vector<double> {1., 2., 3., 4., 5., 6., 7., 8.};
        f = new Polynomial<5, 5>(*coeffs);
    };
    virtual void TearDown() override{
        delete f;
        delete coeffs;
    };
};

TEST_F(PolynomialTest, PolynomialEval)
{
    // Check that the polynomial is evaluated correctly
    for (double i = 0.; i < 10.; i+=0.1) {
        // Define the input vector
        Vector<5> x = std::vector<double>{i, i + 1, i + 2, i + 3, i + 4};
        // Evaluate the polynomial
        Vector<5> y = f->call(x);
        // Evaluate the polynomial manually
        Vector<5> y_manual = 0.;
        for (int j = 0; j < coeffs->size(); ++j) {
            y_manual += (*coeffs)[j] * (x ^ j);
        }
        for (int j = 0; j < 5; ++j) {
            EXPECT_DOUBLE_EQ(y[j], y_manual[j]);
        }
    }
}

}