#include "sampler.hpp"

template<unsigned int dim>
MonteCarloApproximator<dim>::MonteCarloApproximator(std::vector<Vector<dim>>* samples)
  : m_samples(samples) {}

template<unsigned int dim>
MonteCarloApproximator<dim>::~MonteCarloApproximator() {}

template<unsigned int dim>
double MonteCarloApproximator<dim>::moment_dim(unsigned int k, std::string mode, const Eigen::VectorXd& samples_dim) {

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
Eigen::VectorXd MonteCarloApproximator<dim>::moment(std::vector<unsigned int> &orders, std::string mode) {
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
Eigen::VectorXd MonteCarloApproximator<dim>::moment(unsigned int order, std::string mode) {

  // Build the order vector
  std::vector<unsigned int> orders(dim);
  for (auto& o : orders){
    o = order;
  }

  return moment(orders, mode);
}

template <unsigned int dim>
Eigen::VectorXd MonteCarloApproximator<dim>::mean() {
    return moment(1, "raw");
}

template <unsigned int dim>
Eigen::VectorXd MonteCarloApproximator<dim>::var() {
    return moment(2, "central");
}

template <unsigned int dim>
Eigen::VectorXd MonteCarloApproximator<dim>::std() {
    return var().array().sqrt();
}

template <unsigned int dim>
Eigen::VectorXd MonteCarloApproximator<dim>::skewness() {
    return moment(3, "standardized");
}

template <unsigned int dim>
Eigen::VectorXd MonteCarloApproximator<dim>::kurtosis() {
    return moment(4, "standardized");
}

template <unsigned int dim>
Eigen::VectorXd MonteCarloApproximator<dim>::hyperskewness() {
    return moment(5, "standardized");
}

template <unsigned int dim>
Eigen::VectorXd MonteCarloApproximator<dim>::hypertailedness() {
    return moment(6, "standardized");
}

template <unsigned int dim>
bool MonteCarloApproximator<dim>::is_clt_valid(unsigned int n_samples, unsigned int m_means, Distribution<dim>* dist){
  std::vector<Vector<dim>> sample_means = get_sample_means(n_samples, m_means, dist);

  Eigen::VectorXd sample_means_mean = MonteCarloApproximator<dim>(&sample_means).mean();
  Eigen::VectorXd sample_means_var = MonteCarloApproximator<dim>(&sample_means).var();

  Eigen::VectorXd dist_mean = (dist->mean()).to_std_vector();
  Eigen::VectorXd dist_var = (dist->var()).to_std_vector();
  Eigen::VectorXd dist_sample_mean_var = dist_var / n_samples;

  Eigen::VectorXd error = (sample_means_mean - dist_mean).array().abs() / dist_mean.array();

  Eigen::VectorXd error_threshold = 1.96 * sqrt(dist_sample_mean_var.array() / m_means);

  return (error.array() < error_threshold.array()).all();
}

template <unsigned int dim>
std::vector<Vector<dim>> get_sample_means(unsigned int n_samples, unsigned int m_means, Distribution<dim>* dist) {
  std::vector<Vector<dim>> sample_means(m_means);

  // Sample m_means with n_samples each by c
  for(int i = 0; i < m_means; ++i){
    dist->set_time_seed();
    sample_means[i] = dist->samples(n_samples);
  }

  return sample_means;
}