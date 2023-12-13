#include "io.hpp"

Reader::Reader()
{
}

ReaderCL::ReaderCL(int argc, char* argv[])
{
    commandLine = std::vector<std::string>(argv, argv + argc);
    this->parser();
}

ReaderCL::~ReaderCL() {}

void ReaderCL::parser()
{
    auto dirPos = std::find(commandLine.begin(), commandLine.end(), "--dir");
    auto statPos = std::find(commandLine.begin(), commandLine.end(), "--stat");
    auto kPos = std::find(commandLine.begin(), commandLine.end(), "-k");
    auto modePos = std::find(commandLine.begin(), commandLine.end(), "--mode");
    auto distPos = std::find(commandLine.begin(), commandLine.end(), "--dist");
    auto functionPos = std::find(commandLine.begin(), commandLine.end(), "--function");

    if (dirPos != commandLine.end())
    {
        dir = *(dirPos + 1);
    }
    else
    {
        dir = "./";
        std::cout << "No directory provided, using default: " << dir << std::endl;
    }

    if (statPos != commandLine.end())
    {
        stat = *(statPos + 1);
    }
    else
    {
        stat = "mean";
        std::cout << "No statistic provided, using default: " << stat << std::endl;
    }

    if (kPos != commandLine.end())
    {
        k = std::stoi(*(kPos + 1));
    }
    else
    {
        k = 1;
        std::cout << "No k provided, using default: " << k << std::endl;
    }

    if (modePos != commandLine.end())
    {
        mode = *(modePos + 1);
    }
    else
    {
        mode = "central";
        std::cout << "No mode provided, using default: " << mode << std::endl;
    }

    if (distPos != commandLine.end())
    {
        dist = *(distPos + 1);
    }
    else
    {
        dist = "uniform";
        std::cout << "No distribution provided, using default: " << dist << std::endl;
    }

    if (functionPos != commandLine.end())
    {
        function = *(functionPos + 1);
    }
    else
    {
        function = "online";
        std::cout << "No function provided, using default: " << function << std::endl;
    }
    this->setup();
}

void ReaderCL::setup(){
    // Check if the file exists otherwise use online definition
    if (function.find(".txt") != std::string::npos)
    {
        std::cout << "Function file provided: " << function << std::endl;
        
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
            Workflow<1, 1> workflow(dir, stat, mode, k, dist, type, function);
            workflow.run();
        }
        // else if ((dim_inp == 1) && (dim_out == 2))
        // {
        //     Workflow<1, 2> workflow(dir, stat, mode, k, dist, type, function);
        //     workflow.run();
        // }
        // else if ((dim_inp == 2) && (dim_out == 1))
        // {
        //     Workflow<2, 1> workflow(dir, stat, mode, k, dist, type, function);
        //     workflow.run();
        // }
        else if ((dim_inp == 2) && (dim_out == 2))
        {
            Workflow<2, 2> workflow(dir, stat, mode, k, dist, type, function);
            workflow.run();
        }
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

    if ((ftype == "polynomial") && (dim_inp == dim_out))
    {
        std::cout << "Polynomial function\n";
        f = new Polynomial<dim_inp, dim_out>(filepath);
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
    MonteCarloApproximator<dim_out> mc(samples);
    if (stat == "mean")
    {
        std::cout << "Mean: " << mc.mean().reshaped(1, dim_out) << std::endl;
    }
    else if (stat == "variance")
    {
        std::cout << "Variance: " << mc.var().reshaped(1, dim_out) << std::endl;
    }
    else if (stat == "moment")
    {
        std::cout << "Moment: " << mc.moment(k, mode).reshaped(1, dim_out) << std::endl;
    }
    else if (stat == "std")
    {
        std::cout << "Standard deviation: " << mc.std().reshaped(1, dim_out) << std::endl;
    }
    else if (stat == "skewness")
    {
        std::cout << "Skewness: " << mc.skewness().reshaped(1, dim_out) << std::endl;
    }
    else if (stat == "kurtosis")
    {
        std::cout << "Kurtosis: " << mc.kurtosis().reshaped(1, dim_out) << std::endl;
    }
    else if (stat == "hyperskewness")
    {
        std::cout << "Hyperskewness: " << mc.hyperskewness().reshaped(1, dim_out) << std::endl;
    }
    else if (stat == "hypertailedness")
    {
        std::cout << "Hypertailedness: " << mc.hypertailedness().reshaped(1, dim_out) << std::endl;
    }
    else
    {
        std::cerr << "Error: Statistic not supported yet\n";
        exit(1);
    }

}