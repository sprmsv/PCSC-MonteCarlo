#ifndef MC_SAMPLER_HPP
#define MC_SAMPLER_HPP

#include <functional>
#include <string>

#include <Eigen/Core>

#include "distributions.hpp"
#include "functions.hpp"


template <unsigned int dim = 1>
class MonteCarloApproximater {
public:
  // Constructors and destructor
  MonteCarloApproximater(std::vector<std::vector<double>>* samples);
  ~MonteCarloApproximater();
  // Moment
  Eigen::VectorXd moment(std::vector<unsigned int> &orders, std::string mode);
  Eigen::VectorXd moment(unsigned int order, std::string mode);
  Eigen::VectorXd mean();
  Eigen::VectorXd var();
  Eigen::VectorXd std();
  Eigen::VectorXd skewness();
  Eigen::VectorXd kurtosis();
  Eigen::VectorXd hyperskewness();
  Eigen::VectorXd hypertailedness();

private:
  double moment_dim(unsigned int order, std::string mode, const Eigen::VectorXd& samples_dim);
  std::vector<std::vector<double>>* m_samples;
};

#include "sampler.tpp"

#endif
