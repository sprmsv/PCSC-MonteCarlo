#include "io.hpp"


void write_line(std::ostream& stream, char symbol, int width) {
  for (int i=0; i < width; ++i) {
    stream << symbol;
  }
  stream << std::endl;
}

template <unsigned int dim>
void write_csv(std::ostream& stream, const std::vector<Vector<dim>>& data) {
  for (const auto& vec : data) {
    stream << vec << std::endl;
  }
}

ArgParser::ArgParser(int argc, char* argv[])
  : args(std::vector<std::string>(argv, argv + argc)) {
    this->parse();
}

void ArgParser::parse()
{
  auto pos_function = std::find(args.begin(), args.end(), "--function");
  auto pos_order = std::find(args.begin(), args.end(), "-k");
  auto pos_mode = std::find(args.begin(), args.end(), "--mode");
  auto pos_dist = std::find(args.begin(), args.end(), "--dist");
  auto pos_n = std::find(args.begin(), args.end(), "-n");
  auto pos_output = std::find(args.begin(), args.end(), "--output");
  auto pos_plot = std::find(args.begin(), args.end(), "--plot");
  auto pos_clt = std::find(args.begin(), args.end(), "--clt");

  // Set the function file
  std::set<std::string> allowed_functypes = {"polynomial", "sumexponential", "sumlogarithm", "linear"};
  if (pos_function != args.end()) {
    function = *(pos_function + 1);
    // Check existence of the file
    if (!std::filesystem::is_regular_file(function)) {
      throw FileNotFoundException("--function", "Could not find file \"" + function + "\".");
    }
    // Read file and store function type and dimensions
    std::ifstream file(function);
    if (!file.is_open()) {
        throw InvalidArgumentException("--function", "Could not open file \"" + function + "\".");
    }
    std::string line;
    std::getline(file, line);
    functype = line;
    if (std::find(allowed_functypes.begin(), allowed_functypes.end(), functype) == allowed_functypes.end()) {
        file.close();
        throw InvalidArgumentException("--function", "Function type \"" + functype + "\" is not supported.");
    }
    std::getline(file, line);
    std::istringstream(line) >> dim_inp >> dim_out;
    if (dim_inp < 1 || dim_out < 1) {
        file.close();
        throw InvalidArgumentException("--function", "Dimensions (" + line + ") must be positive integers.");
    }
    std::getline(file, line);
    if (!line.empty()) {
        file.close();
        throw InvalidArgumentException("--function", "The third line has to be empty in \"" + function + "\".");
    }
    file.close();
  }
  else {
    throw ArgumentMissingException("--function", "Function file must be provided.");
  }

  // Set the moment order (k)
  if (pos_order != args.end()) {
    try {
      order = std::stoi(*(pos_order + 1));
    }
    catch (std::invalid_argument &e){
      throw InvalidArgumentException("-k", "Moment order (k) must be an integer (\"" + *(pos_order + 1) + "\").");
    }
  }
  else {
    order = 0;
  }

  // Set the moment type
  std::set<std::string> allowed_modes = {"raw", "central", "standardized"};
  if (pos_mode != args.end()) {
    mode = *(pos_mode + 1);
    if (std::find(allowed_modes.begin(), allowed_modes.end(), mode) == allowed_modes.end()) {
      throw InvalidArgumentException("--mode", "Moment type \"" + mode + "\" is not supported.");
    }
  }
  else {
    mode = "standardized";
  }

  // Set the distribution
  std::set<std::string> allowed_dists = {"normal", "uniform"};
  if (pos_dist != args.end()) {
    dist = *(pos_dist + 1);
    if (std::find(allowed_dists.begin(), allowed_dists.end(), dist) == allowed_dists.end()) {
      throw InvalidArgumentException("--dist", "Distribution \"" + dist + "\" is not supported.");
    }
  }
  else {
    dist = "normal";
  }

  // Set the number of the samples
  if (pos_n != args.end()) {
    try {
      n_samples = std::stoi(*(pos_n + 1));
    }
    catch (std::invalid_argument &e){
      throw InvalidArgumentException("-k", "Number of samples (n) must be an integer (\"" + *(pos_n + 1) + "\").");
    }
  }
  else {
    n_samples = 1000;
  }

  // Set the output file
  if (pos_output != args.end()) {
    output = *(pos_output + 1);
    if (!std::filesystem::is_directory(output)) {
      throw FileNotFoundException("--output", "Could not find directory \"" + output + "\".");
    }
  }
  else {
    output = "";
  }

  // Set the plotting argument
  if (pos_plot != args.end()) {
    if (*(pos_plot + 1) != "0" && *(pos_plot + 1) != "1") {
      throw InvalidArgumentException("--plot", "Plot argument must be 0 or 1.");
    }
    plot = (*(pos_plot + 1) == "1");
  }
  else {
    plot = false;
  }

  // Set the clt argument
  if (pos_clt != args.end()) {
    if (*(pos_clt + 1) != "0" && *(pos_clt + 1) != "1") {
      throw InvalidArgumentException("clt", "CLT argument must be 0 or 1.");
    }
    clt = (*(pos_clt + 1) == "1");
  }
  else {
    clt = false;
  }
}

template <unsigned int dim_inp, unsigned int dim_out>
Workflow<dim_inp, dim_out>::Workflow(const ArgParser& parser)
: m_parser(parser)
{
  // Construct the function dynamically
  // TODO: Specialize for dim_out and add other functions
  // TODO: Separate this part in another method and only specialize that method
  if ((m_parser.functype == "linear")) {
    m_function = new Linear<dim_inp, dim_out>(m_parser.function);
  }
  // TODO: Add other function types (some of them only with dim_out = 1 specialization)
  else {
    throw FunctionNotSupported(m_parser.functype + " is not supported.");
  }

  // Construct the distibution and MCA
  // TODO: Parameterize mean and variance
  if (m_parser.dist == "uniform") {
    m_distribution = new Uniform<dim_inp>(0., 1.);
    m_mca = m_function->mca(m_parser.n_samples, *m_distribution);
  }
  // TODO: Parameterize mean and variance
  else if (m_parser.dist == "normal") {
    m_distribution = new Normal<dim_inp>(0., 1.);
    m_mca = m_function->mca(m_parser.n_samples, *m_distribution);
  }
  else {
    throw InvalidArgumentException("--dist");
  }
}

template <unsigned int dim_inp, unsigned int dim_out>
void Workflow<dim_inp, dim_out>::launch() {
  // Calculate the statistics
  std::map<std::string, Eigen::VectorXd> stats {
    {"mean", m_mca.mean()},
    {"variance", m_mca.var()},
    {"std", m_mca.std()},
    {"skewness", m_mca.skewness()},
    {"kurtosis", m_mca.kurtosis()},
    {"hyperskewness", m_mca.hyperskewness()},
    {"hypertailedness", m_mca.hypertailedness()}
  };
  if (m_parser.order > 0) {
    stats.insert(
        {"moment ({" + std::to_string(m_parser.order) + "}, {" + m_parser.mode + "})",
        m_mca.moment(m_parser.order, m_parser.mode)}
    );
  }

  // Print the statistics to standard output
  write_report(std::cout, stats);

  // Generate clt convergence results
  if (m_parser.clt) {
    int w_line = 80;
    write_line(std::cout, '-', w_line);
    std::cout << "CENTRAL LIMIT THEOREM" << std::endl;
    write_line(std::cout, '-', w_line);
    for (int n = 10; n < 100; n += 40) {
      auto errors = clt(n);
      std::cout << std::left << std::setw(20) << "n = " + std::to_string(n) << std::endl;
      std::cout << std::right << std::setw(20) << "err_rel_mean" << ": " << errors.first << std::endl;
      std::cout << std::right << std::setw(20) << "err_rel_var" << ": " << errors.second << std::endl;
    }
    std::cout << std::endl;
  }

  // Write to output directory
  if (!m_parser.output.empty()) {
    // Open a report file in the output directory and write report
    std::string reportfile = m_parser.output + "/" + "report.out";
    std::ofstream reportstream(reportfile);
    if (reportstream.is_open()) {
      write_report(reportstream, stats);
      reportstream.close();
      std::cout << "Report is stored in \"" + reportfile + "\"." << std::endl;
    }
    else {
      std::cerr << "Error opening file: \"" << reportfile << "\"." << std::endl;
    }

    // Open a csv file in the output directory and export the samples
    std::string samplesfile = m_parser.output + "/" + "samples.csv";
    std::ofstream samplesstream(samplesfile);
    if (samplesstream.is_open()) {
      write_csv(samplesstream, m_mca.data());
      samplesstream.close();
      std::cout << "Samples are exported to \"" + samplesfile + "\"." << std::endl;
    }
    else {
      std::cerr << "Error opening file: \"" << samplesfile << "\"." << std::endl;
    }

    // TODO: Plot mca->samples and save it
    if (m_parser.plot) {
      // ...
    }
  }
}

template <unsigned int dim_inp, unsigned int dim_out>
void Workflow<dim_inp, dim_out>::write_report(
  std::ostream& stream, const std::map<std::string, Eigen::VectorXd>& stats)
{
  // Set parameters
  int w_title = 20;
  int w_line = 80;

  // Write info about the approximations
  write_line(stream, '-', w_line);
  stream << "INFO" << std::endl;
  write_line(stream, '-', w_line);
  stream << std::left << std::setw(w_title) << "function file" << ": " << m_parser.function << std::endl;
  stream << std::left << std::setw(w_title) << "function type" << ": " << m_parser.functype << std::endl;
  stream << std::left << std::setw(w_title) << "input dimension" << ": " << m_parser.dim_inp << std::endl;
  stream << std::left << std::setw(w_title) << "output dimension" << ": " << m_parser.dim_out << std::endl;
  stream << std::left << std::setw(w_title) << "srouce distribution" << ": " << m_parser.dist << std::endl;
  stream << std::left << std::setw(w_title) << "number of samples" << ": " << m_parser.n_samples << std::endl;
  stream << std::left << std::setw(w_title) << "output directory" << ": " << m_parser.output << std::endl;
  stream << std::endl;

  // Set the numeric output settings
  stream.setf(std::ios::scientific);
  stream.setf(std::ios::showpos);
  stream.precision(4);

  // Write the statistics
  write_line(stream, '-', w_line);
  stream << "APPROXIMATED STATISTICS" << std::endl;
  write_line(stream, '-', w_line);
  for (std::pair<std::string, Eigen::VectorXd> pair : stats) {
    auto& stat = pair.first;
    auto& value = pair.second;
    stream << std::left << std::setw(w_title) << stat.c_str() << ": ";
    stream << value.reshaped(1, m_parser.dim_out) << std::endl;
  }
  stream << std::endl;
  stream.flush();
}

template <unsigned int dim_inp, unsigned int dim_out>
Workflow<dim_inp, dim_out>::~Workflow() {
  delete m_function;
  delete m_distribution;
}

// replace clt() with run()
template<unsigned int dim_inp, unsigned int dim_out>
std::pair<Vector<dim_out>, Vector<dim_out>> Workflow<dim_inp, dim_out>::clt(int n) {

  std::pair<Vector<dim_out>, Vector<dim_out>> relative_error;

  // Get samples from the approximated mean distribution ($\mu_n$)
  std::vector<Vector<dim_out>> means(m_parser.n_samples);
  std::for_each(means.begin(), means.end(),
    [this, n](auto& mean){mean = this->m_function->mean(n, *(this->m_distribution));});

  // Get MC approximator from the means
  MonteCarloApproximator<dim_out> mca(std::make_shared<std::vector<Vector<dim_out>>>(means));

  // Get the theoretical mean using a more accurate approximation
  Vector<dim_out> mean_the = m_function->mean(m_parser.n_samples, *m_distribution);
  relative_error.first = (mean_the - mca.mean()).abs() / mean_the;

  // Get the theoretical variance using a more accurate approximation
  Vector<dim_out> var_the = m_function->var(m_parser.n_samples, *m_distribution) / n;
  relative_error.second = (var_the - mca.var()).abs() / var_the;

  return relative_error;
}
