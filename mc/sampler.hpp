#ifndef MC_SAMPLER_HPP
#define MC_SAMPLER_HPP

#include <functional>
#include <string>

#include <Eigen/Core>

#include "distributions.hpp"
#include "vector.hpp"


template <unsigned int dim = 1>
class MonteCarloApproximator {
public:
  // Constructors and destructor
  MonteCarloApproximator(std::shared_ptr<std::vector<Vector<dim>>> samples);
  ~MonteCarloApproximator();
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
  std::shared_ptr<std::vector<Vector<dim>>> m_samples;
};

#include "sampler.tpp"

#endif
