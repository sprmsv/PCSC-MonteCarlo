#include <gtest/gtest.h>
#include <vector>

#include "distributions.hpp"

namespace {
    class DistributionTest : public ::testing::Test {
    protected:
        Distribution<5>* dist;

        virtual void SetUp() = 0;
        virtual void TearDown() = 0;
    };

    class UniformTest : public DistributionTest {
    protected:
        std::vector<double>* lower;
        std::vector<double>* upper;

        virtual void SetUp() override {
            lower = new std::vector<double>({0., 1., 2., 3., 4.});
            upper = new std::vector<double>({1., 3., 5., 7., 9.});
            dist = new Uniform<5>(*lower, *upper);
        };
        virtual void TearDown() override {
            delete lower;
            delete upper;
            delete dist;
        };
    };

    class NormalTest : public DistributionTest {
    protected:
        std::vector<double>* mean;
        std::vector<std::vector<double>>* covariance;
        virtual void SetUp() override {
            mean = new std::vector<double>({0., 1., 2., 3., 4.});
            covariance = new std::vector<std::vector<double>>({
                {1., 2., 3., 4., 5.},
                {2., 1., 2., 3., 4.},
                {3., 2., 1., 2., 3.},
                {4., 3., 2., 1., 2.},
                {5., 4., 3., 2., 1.},
            });
            dist = new Normal<5>(*mean, *covariance);
        };
        virtual void TearDown() override {
            delete mean;
            delete covariance;
            delete dist;
        };
    };

    TEST_F(UniformTest, UniformSamples) {
        // Check that the samples are within the bounds
        int n = 1000;
        auto samples = dist->samples(n);
        for (int i = 0; i < n; ++i) {
            auto sample = (*samples)[i];
            for (int d = 0; d < 5; ++d) {
                EXPECT_GE(sample[d], (*lower)[d]);
                EXPECT_LE(sample[d], (*upper)[d]);
            }
        }
    }

    TEST_F(UniformTest, UniformMean) {
        // Check that the mean is computed correctly
        std::vector<double> true_mean({0.5, 2., 3.5, 5., 6.5});
        auto mean = dist->mean();
        for (int d = 0; d < 5; ++d) {
            EXPECT_NEAR(mean[d], true_mean[d], 1.e-15);
        }
    }

    TEST_F(UniformTest, UniformVariance) {
        // Check that the variance is computed correctly
        std::vector<double> true_var({1./12., 4./12., 9./12., 16./12., 25./12.});
        auto var = dist->var();
        for (int d = 0; d < 5; ++d) {
            EXPECT_NEAR(var[d], true_var[d], 1.e-15);
        }
    }

    TEST_F(NormalTest, NormalVariance){
        // Check that the variance is computed correctly
        std::vector<double> true_var({1., 1., 1., 1., 1.});
        auto var = dist->var();
        for (int d = 0; d < 5; ++d) {
            EXPECT_NEAR(var[d], true_var[d], 1.e-15);
        }
    }

};
