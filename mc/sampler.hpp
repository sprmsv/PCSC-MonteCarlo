#ifndef MC_SAMPLER_HPP
#define MC_SAMPLER_HPP

#include <functional>
#include <string>

#include "../eigen/Eigen/Core"

#include "distributions.hpp"
#include "functions.hpp"


template <unsigned int dim = 1>
class MonteCarloApproximator {
public:
  // Constructors and destructor
  MonteCarloApproximator(std::vector<Vector<dim>>* samples);
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
  
  // CLT 
  bool is_clt_valid(unsigned int n_samples, unsigned int m_means, Distribution<dim>* dist);
  
private:
  double moment_dim(unsigned int order, std::string mode, const Eigen::VectorXd& samples_dim);
  std::vector<Vector<dim>>* m_samples;
};

// CLT
template <unsigned int dim>
std::vector<Vector<dim>> get_sample_means(unsigned int n_samples, unsigned int m_means, Distribution<dim>* dist);

#include "sampler.tpp"

#endif
