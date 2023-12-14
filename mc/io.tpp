#include "io.hpp"


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
  Function<dim_inp, dim_out>* f;
  if ((m_parser.functype == "linear")) {
    f = new Linear<dim_inp, dim_out>(m_parser.function);
  }
  // TODO: Add other function types (some of them only with dim_out = 1 specialization)
  else {
    throw FunctionNotSupported("--function");
  }

  // Construct the distibution and MCA
  // TODO: Parameterize mean and variance
  if (m_parser.dist == "uniform") {
    Uniform<dim_inp> dist(0., 1.);
    m_mca = f->mca(m_parser.n_samples, &dist);
  }
  // TODO: Parameterize mean and variance
  else if (m_parser.dist == "normal") {
    Normal<dim_inp> dist(0., 1.);
    m_mca = f->mca(m_parser.n_samples, &dist);
  }
  else {
    throw InvalidArgumentException("--dist");
  }

  // Destruct the function on heap memory
  delete f;
}

template <unsigned int dim_inp, unsigned int dim_out>
void Workflow<dim_inp, dim_out>::launch() {

  // TODO: Measure time and report

  // Calculate the statistics
  std::map<std::string, Eigen::VectorXd> stats {
    {"mean", m_mca->mean()},
    {"variance", m_mca->var()},
    {"std", m_mca->std()},
    {"skewness", m_mca->skewness()},
    {"kurtosis", m_mca->kurtosis()},
    {"hyperskewness", m_mca->hyperskewness()},
    {"hypertailedness", m_mca->hypertailedness()}
  };
  if (m_parser.order > 0) {
    stats.insert({"moment ({" + std::to_string(m_parser.order) + "}, {" + m_parser.mode + "})", m_mca->moment(m_parser.order, m_parser.mode)});
  }

  // TODO: Separate the following steps in other methods

  // TODO: Write info about the parser to stdout
  // ...
  // Write stats to standard output
  for (std::pair<std::string, Eigen::VectorXd> pair : stats) {
    auto& stat = pair.first;
    auto& value = pair.second;
    std::cout << stat << ": " << value.reshaped(1, m_parser.dim_out) << std::endl;
  }

  // Output file
  if (!m_parser.output.empty()) {
    // TODO: Write info about the parser to an output file
    // ...

    // TODO: Write stats to an output file
    // ...

    // TODO: Write mca->m_samples to an output file
    // ...

    // TODO: Plot mca->samples and save it
    if (m_parser.plot) {
      // ...
    }

    // TODO: Plot CLT convergence and save it
    if (m_parser.clt) {
      // ...
    }

  }
}
