# OUR TODO LIST

?. Write output to files
    - Output samples as CSV
*. Set precision and formatting for the output streams
    - use std::cout.flush()
    - use ofstream.setf(std::ios::scientific)
    - use ofstream.setf(std::ios::showpos)
    - use ofstream.precision(4)

!!. Document the code
    - io.hpp

!!. Fix the tests + check the tests

* Change unnecessary pointers to references + use smart pointers
    - MonteCarloApproximator(std::shared_ptr<std::vector<Vector<dim>>> samples) -> by-reference?
    - MonteCarloApproximator::m_samples -> reference?

    - Workflow::m_function -> reference?
    - Workflow::m_dist -> reference?

    - Function::mca(unsigned int n, Distribution<dim_inp>* dist) -> dist by-reference !! output by-reference?
    - Function::mean -> dist by-reference !!
    - Function::var -> dist by-reference !!
    - Workflow::m_mca -> reference / copy?

*. Make some of the class members private/protected

*. Features not used:
    - function pointers and std::function
    - private members and friend classes/functions
    - Copy the pointer or copy the content when copying another object??
    - (non-pure) virtual methods and calling them from the daughter classes

!!. Code check and cleaning on the main branch:
    - Remove extra comments
    - Consistent spacing
    - Add more assertions if related
    - Remove trailing whitespaces



# REPORT:

- Make a report delivered as an extended README:
    - how to compile the program
    - typical program execution (the flow) and usage
    - List of features & tests
    - TODOs and perspectives
    1. the implementation in a consise way
    2. the validating tests
    3. the limitations and problems

- Make one oral presentation per student
    - the structure of the program
    - list of features
    - limitations and problems

!!. Proof-read the readme
