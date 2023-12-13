#include <gtest/gtest.h>
#include <vector>
#include <cmath>

#include "functions.hpp"

namespace{


class PolynomialTest : public ::testing::Test {
protected:
    // Define the coefficients of the polynomial
    Polynomial<1, 1>* f;
    std::vector<double>* coeffs;

    virtual void SetUp() override{
        coeffs = new std::vector<double> {1., 2., 3., 4., 5., 6., 7., 8.};
        f = new Polynomial<1, 1>(*coeffs);
    };
    virtual void TearDown() override{
        delete f;
        delete coeffs;
    };
};

TEST_F(PolynomialTest, PolynomialEval1D)
{
    // Check that the polynomial is evaluated correctly
    for (int i = 0; i < 10; ++i) {
        // Define the input vector
        Vector<1> x{i}; 

        // Evaluate the polynomial
        Vector<1> y = (*f)(x);

        // Evaluate the polynomial manually
        Vector<1> y2(0.);
        for (int j = 0; j < coeffs->size(); ++j) {
            y2[0] += (*coeffs)[j] * std::pow(x[0], j); 
        }

        // We use exact evaluation of double because 
        // the exact same operations are supposed to be performed
        EXPECT_EQ(y[0], y2[0]); 
    }
}

}