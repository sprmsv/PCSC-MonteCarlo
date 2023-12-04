#include "sampler.hpp"

template<unsigned int dim>
MonteCarloApproximater<dim>::MonteCarloApproximater(std::vector<std::vector<double>>* samples)
  : m_samples(samples) {}

template<unsigned int dim>
MonteCarloApproximater<dim>::~MonteCarloApproximater() {}

template<unsigned int dim>
double MonteCarloApproximater<dim>::moment_dim(unsigned int k, std::string mode, const Eigen::VectorXd& samples_dim) {

  if (mode == "raw"){
    return samples_dim.array().pow(k).mean();
  }
  else if (mode == "central"){
    double mean = moment_dim(1, "raw", samples_dim);
    return (samples_dim.array() - mean).array().pow(k).mean();
  }
  else if (mode == "standardized"){
    double std = sqrt(moment_dim(2, "central", samples_dim));
    double central = moment_dim(k, "central", samples_dim);
    return central / pow(std, k);
  }
  else {
    throw std::exception();
  }

};

template<unsigned int dim>
Eigen::VectorXd MonteCarloApproximater<dim>::moment(std::vector<unsigned int> &orders, std::string mode) {
  // TODO: Assert mode is in "raw", "central", "standardized"

  // Build mapped matrix from the samples
  Eigen::MatrixXd samples(m_samples->size(), dim);
  for (int i=0; i < m_samples->size(); ++i){
      samples.row(i) = Eigen::Matrix<double, dim, 1>::Map(&m_samples->at(i)[0]);
  }

  // Calculate moment for each dimension
  Eigen::VectorXd moment(dim);
  for (int i = 0; i < dim; ++i){
      moment[i] = moment_dim(orders[i], mode, samples.col(i));
  }

  return moment;
}

template<unsigned int dim>
Eigen::VectorXd MonteCarloApproximater<dim>::moment(unsigned int order, std::string mode) {

  // Build the order vector
  std::vector<unsigned int> orders(dim);
  for (auto& o : orders){
    o = order;
  }

  return moment(orders, mode);
}

template <unsigned int dim>
Eigen::VectorXd MonteCarloApproximater<dim>::mean() {
    return moment(1, "raw");
}

template <unsigned int dim>
Eigen::VectorXd MonteCarloApproximater<dim>::var() {
    return moment(2, "central");
}

template <unsigned int dim>
Eigen::VectorXd MonteCarloApproximater<dim>::std() {
    return var().array().sqrt();
}

template <unsigned int dim>
Eigen::VectorXd MonteCarloApproximater<dim>::skewness() {
    return moment(3, "standardized");
}

template <unsigned int dim>
Eigen::VectorXd MonteCarloApproximater<dim>::kurtosis() {
    return moment(4, "standardized");
}

template <unsigned int dim>
Eigen::VectorXd MonteCarloApproximater<dim>::hyperskewness() {
    return moment(5, "standardized");
}

template <unsigned int dim>
Eigen::VectorXd MonteCarloApproximater<dim>::hypertailedness() {
    return moment(6, "standardized");
}