#ifndef MC_IO_HPP
#define MC_IO_HPP

#include "functions.hpp"
#include "distributions.hpp"
#include "sampler.hpp"
#include "exceptions.hpp"

#include <string>
#include <vector>
#include <set>
#include <map>
#include <memory>
#include <fstream>
#include <iostream>
#include <sstream>
#include <sys/types.h>
#include <sys/stat.h>


/// @brief Class for parsing the input arguments and storing them.
class ArgParser
{
public:
  /// @brief Construct a new ArgParser object
  ArgParser(int argc, char* argv[]);

  /// @brief Path to function file
  std::string function;
  /// @brief Function type
  std::string functype;
  /// @brief Input dimension of the function
  unsigned int dim_inp;
  /// @brief Output dimension of the function
  unsigned int dim_out;
  /// @brief Moment order
  int order;
  /// @brief Moment type
  std::string mode;
  /// @brief Distribution name
  std::string dist;
  /// @brief Number of samples
  int n_samples;
  /// @brief Path to output directory
  std::string output;
  /// @brief Falg for saving plots
  bool plot;
  /// @brief Flag for saving clt outputs
  bool clt;

private:
  /// @brief Parse arguments and initialize members
  void parse();

  /// @brief Arguments
  std::vector<std::string> args;
};

/// @brief Class for managing the main workflow of the program
/// @tparam dim_inp Dimension of the input of the function
/// @tparam dim_out Dimension of the output of the function
template <unsigned int dim_inp, unsigned int dim_out>
class Workflow
{
public:
  /// @brief Construct a Workflow object based on the arguments in a parser.
  Workflow(const ArgParser& parser);

  /// @brief Destroy the Workflow object.
  ~Workflow();

  /// @brief Launch the main workflow.
  void launch();

  /// @brief Launch the workflow for calculating errors of the central limit theorem.
  void clt(int n = 10);

private:
  /// @brief Argument parser.
  const ArgParser& m_parser;
  /// @brief Function of interest.
  Function<dim_inp, dim_out>* m_function;
  /// @brief Source distribution.
  Distribution<dim_inp>* m_distribution;
  /// @brief Monte Carlo approximator.
  std::unique_ptr<MonteCarloApproximator<dim_out>> m_mca;
};

/**
 * @brief Class for writing a set of vectors to a CSV file.
 * @tparam dim The dimension of the vectors.
 */
template <unsigned int dim>
class CSVWriter
{
public:
  /// @brief Construct a CSVWriter object.
  /// @param dir Directory of the output
  /// @param filename Filename.
  CSVWriter(const std::string& dir, const std::string& filename);

  /// @brief Write the data to the file
  /// @param data 
  /// @return True if writing to the file has been successful.
  bool writeCSV(const std::vector<Vector<dim>>& data);
private:
  std::string outputDir;
  std::string filename;
};

#include "io.tpp"
#include "csvwriter.tpp"

#endif
