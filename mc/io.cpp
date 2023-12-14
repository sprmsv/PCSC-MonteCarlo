#include "io.hpp"

#include <set>
#include <sys/types.h>
#include <sys/stat.h>

Reader::Reader() {}

ArgParser::ArgParser(int argc, char* argv[])
  : Reader(), args(std::vector<std::string>(argv, argv + argc)) {
    this->parse();
}

void ArgParser::parse()
{
  auto pos_function = std::find(args.begin(), args.end(), "--function");
  auto pos_stat = std::find(args.begin(), args.end(), "--stat");
  auto pos_k = std::find(args.begin(), args.end(), "-k");
  auto pos_mode = std::find(args.begin(), args.end(), "--mode");
  auto pos_dist = std::find(args.begin(), args.end(), "--dist");
  auto pos_n = std::find(args.begin(), args.end(), "-n");
  auto pos_output = std::find(args.begin(), args.end(), "--output");
  auto pos_plot = std::find(args.begin(), args.end(), "--plot");
  auto pos_clt = std::find(args.begin(), args.end(), "--clt");

  // Set the function file
  if (pos_function != args.end()) {
    function = *(pos_function + 1);
    if (!std::filesystem::is_regular_file(function)) {
      throw FileNotFoundException("--function", "Could not find file \"" + function + "\".");
    }

  }
  else {
    throw ArgumentMissingException("--function", "Function file must be provided.");
  }

  // Set the statistic
  std::set<std::string> allowed_stats = {
    "moment", "mean", "variance", "var", "std",
    "skewness", "kurtosis", "hyperskewness", "hypertailedness"
  };
  if (pos_stat != args.end()) {
    stat = *(pos_stat + 1);
    if (std::find(allowed_stats.begin(), allowed_stats.end(), stat) == allowed_stats.end()) {
      throw InvalidArgumentException("--stat", "Statistic \"" + stat + "\" is not supported.");
    }
  }
  else {
    stat = "moment";
  }

  // Set the moment order (k)
  if (pos_k != args.end()) {
    try {
      k = std::stoi(*(pos_k + 1));
    }
    catch (std::invalid_argument &e){
      throw InvalidArgumentException("-k", "Moment order (k) must be an integer (\"" + *(pos_k + 1) + "\").");
    }
  }
  else {
    if (stat == "moment") {
      throw ArgumentMissingException("-k", "Moment order (k) has to be passed.");
    }
    k = 0;
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
    if (stat == "moment") {
      throw ArgumentMissingException("--mode", "Moment type has to be passed.");
    }
    mode = "raw";
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

void ArgParser::setup(){
    // Check if the file exists otherwise use online definition
    if (function.find(".txt") != std::string::npos)
    {
        std::ifstream file(function);
        if (!file.is_open())
        {
            std::cerr << "Error: Could not open file " << function << std::endl;
            exit(1);
        }

        std::string line;
        std::getline(file, line);
        std::istringstream iss(line);
        std::string type;
        iss >> type;

        if ((type != "polynomial") || (type != "exponential") || (type != "logarithm"))
        {
            std::cerr << "Error: Function type not recognized\n";
            exit(1);
        }
        // Read the second line to get the dimension in and out
        std::getline(file, line);
        std::istringstream iss2(line);
        unsigned int dim_inp, dim_out;
        iss2 >> dim_inp >> dim_out;
        // Check if the dimensions are correct
        if ((dim_inp < 1) || (dim_out < 1))
        {
            std::cerr << "Error: Function dimensions must be positive\n";
            exit(1);
        }
        else if ((dim_inp == 1) && (dim_out == 1)){
            Workflow<1, 1> workflow("./", stat, mode, k, dist, type, function);
            workflow.run();
        }
        // TODO: Implement other dimensions
        // else if ((dim_inp == 1) && (dim_out == 2))
        // {
        //     Workflow<1, 2> workflow(dir, stat, mode, k, dist, type, function);
        //     workflow.run();
        // }
        else if ((dim_inp == 2) && (dim_out == 1))
        {
            Workflow<2, 1> workflow("./", stat, mode, k, dist, type, function);
            workflow.run();
        }
        // else if ((dim_inp == 2) && (dim_out == 2))
        // {
        //     Workflow<2, 2> workflow(dir, stat, mode, k, dist, type, function);
        //     workflow.run();
        // }
        else{
            std::cerr << "Error: Function dimension not supported yet\n";
            exit(1);
        }
    }

    // TODO: online implementation
    else
    {
        std::cout << "Online function definition\n";
    }
}

template <unsigned int dim_inp, unsigned int dim_out>
Workflow<dim_inp, dim_out>::Workflow()
{
}

template <unsigned int dim_inp, unsigned int dim_out>
Workflow<dim_inp, dim_out>::~Workflow()
{
    delete d;
    delete f;
}

template <unsigned int dim_inp, unsigned int dim_out>
Workflow<dim_inp, dim_out>::Workflow(std::string dir, std::string stat, std::string mode, int k, std::string dist, std::string ftype, std::string filepath)
: dir(dir), stat(stat), mode(mode), k(k)
{
    if (dist == "uniform")
    {
        std::cout << "Uniform distribution\n";
        d = new Uniform<dim_inp>(0, 1);
    }
    else if (dist == "normal")
    {
        std::cout << "Normal distribution\n";
        d = new Normal<dim_inp>(0, 1);
    }
    else
    {
        std::cerr << "Error: Distribution not supported yet\n";
        exit(1);
    }

    if ((ftype == "polynomial") && (dim_out == 1))
    {
        std::cout << "Polynomial function\n";
        f = new Polynomial<dim_inp>(filepath);
    }
    else
    {
        std::cerr << "Error: Function not supported yet\n";
        exit(1);
    }
}

template <unsigned int dim_inp, unsigned int dim_out>
void Workflow<dim_inp, dim_out>::run()
{
    std::cout << "Running workflow\n";
    int n = 10000;
    auto samples = d->samples(n);
    auto mc = f->mca(n, d);
    if (stat == "mean")
    {
        std::cout << "Mean: " << mc->mean().reshaped(1, dim_out) << std::endl;
    }
    else if (stat == "variance")
    {
        std::cout << "Variance: " << mc->var().reshaped(1, dim_out) << std::endl;
    }
    else if (stat == "moment")
    {
        std::cout << "Moment: " << mc->moment(k, mode).reshaped(1, dim_out) << std::endl;
    }
    else if (stat == "std")
    {
        std::cout << "Standard deviation: " << mc->std().reshaped(1, dim_out) << std::endl;
    }
    else if (stat == "skewness")
    {
        std::cout << "Skewness: " << mc->skewness().reshaped(1, dim_out) << std::endl;
    }
    else if (stat == "kurtosis")
    {
        std::cout << "Kurtosis: " << mc->kurtosis().reshaped(1, dim_out) << std::endl;
    }
    else if (stat == "hyperskewness")
    {
        std::cout << "Hyperskewness: " << mc->hyperskewness().reshaped(1, dim_out) << std::endl;
    }
    else if (stat == "hypertailedness")
    {
        std::cout << "Hypertailedness: " << mc->hypertailedness().reshaped(1, dim_out) << std::endl;
    }
    else
    {
        std::cerr << "Error: Statistic not supported yet\n";
        exit(1);
    }

}