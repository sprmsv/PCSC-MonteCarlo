#include "io.hpp"


template <unsigned int dim>
CSVWriter<dim>::CSVWriter(const std::string& dir, const std::string& filename)
  : outputDir(dir), filename(filename) {}

template <unsigned int dim>
bool CSVWriter<dim>::writeCSV(const std::vector<Vector<dim>>& data) {
  std::ofstream outputFile(outputDir + "/" + filename + ".csv");
  if (!outputFile.is_open()) {
    std::cerr << "Error: Unable to open file for writing." << std::endl;
    return false;
  }

  for (const auto& row : data) {
    for (size_t i = 0; i < dim; ++i) {
      if (i != 0) {
        outputFile << ",";
      }
      outputFile << row[i];
    }
    outputFile << "\n";
  }

  outputFile.close();
  std::cout << "CSV file has been created successfully in " << outputDir;
  return true;
}
