#include <gtest/gtest.h>
#include <memory>
#include "functions.hpp"
#include <Eigen/Core>

namespace{

class SamplerTest : public ::testing::Test {
protected:
  // Define the function
  MonteCarloApproximator<2>* mca;

  virtual void SetUp() override{
    std::vector<Vector<2>> samples = {
      std::vector<double>{1, 2},
      std::vector<double>{3, 4},
      std::vector<double>{10, 11},
      std::vector<double>{12, 13},
      std::vector<double>{20, 26},
    };
    mca = new MonteCarloApproximator<2>(std::make_shared<std::vector<Vector<2>>>(samples));
  };

  virtual void TearDown() override{
    delete mca;
  };
};

TEST_F(SamplerTest, Mean){
  Eigen::VectorXd expected_mean(2);
  expected_mean << 9.2, 11.2;
  EXPECT_TRUE(mca->mean().isApprox(expected_mean));
}

TEST_F(SamplerTest, Var){
  Eigen::VectorXd expected_var(2);
  expected_var << 46.16, 71.76;
  EXPECT_TRUE(mca->var().isApprox(expected_var));
}

TEST_F(SamplerTest, Std){
  Eigen::VectorXd expected_std(2);
  expected_std << 6.7941151005852, 8.4711274338189;
  EXPECT_TRUE(mca->std().isApprox(expected_std));
}

TEST_F(SamplerTest, Moment2){
  Eigen::VectorXd expected_moment2(2);
  expected_moment2 << 130.8, 197.2;
  EXPECT_TRUE(mca->moment(2, "raw").isApprox(expected_moment2));
}

TEST_F(SamplerTest, Moment3){
  Eigen::VectorXd expected_moment3(2);
  expected_moment3 << 2151.2, 4235.2;
  EXPECT_TRUE(mca->moment(3, "raw").isApprox(expected_moment3));
}

TEST_F(SamplerTest, Moment4){
  Eigen::VectorXd expected_moment4(2);
  expected_moment4 << 38163.6, 100090;
  EXPECT_TRUE(mca->moment(4, "raw").isApprox(expected_moment4));
}

TEST_F(SamplerTest, Skewness){
  Eigen::VectorXd expected_skewness(2);
  expected_skewness << 0.3140652553488, 0.6894953146694;
  std::cout << mca->skewness() << std::endl;
  EXPECT_TRUE(mca->skewness().isApprox(expected_skewness));
}

TEST_F(SamplerTest, Kurtosis){
  Eigen::VectorXd expected_kurtosis(2);
  expected_kurtosis << 1.8458905652557, 2.2464457891970;
  std::cout << mca->kurtosis() << std::endl;
  EXPECT_TRUE(mca->kurtosis().isApprox(expected_kurtosis));
}

TEST_F(SamplerTest, Hyperskewness){
  Eigen::VectorXd expected_hyperskewness(2);
  expected_hyperskewness << 1.3935649003221, 2.8648065866564;
  std::cout << mca->hyperskewness() << std::endl;
  EXPECT_TRUE(mca->hyperskewness().isApprox(expected_hyperskewness));
}

TEST_F(SamplerTest, Hypertailedness){
  Eigen::VectorXd expected_hypertailedness(2);
  expected_hypertailedness << 3.9614845940708, 6.0915113577404;
  std::cout << mca->hypertailedness() << std::endl;
  EXPECT_TRUE(mca->hypertailedness().isApprox(expected_hypertailedness));
}

}
