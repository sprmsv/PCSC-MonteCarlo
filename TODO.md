# OUR TODO LIST

4. Show the Central Limit Theorem
    - A function for getting m samples of mean(n), then another function which uses this one and checks the variance
    - Two tests: One for checking that mean(N) works as expected, one for checking the variance of samples from mean(n)
5. Add other function classes:
    - CombinedFunc: First implement the class, then possibly also an operators for Function::operator
    - Exponentials
    - Logarithms
6. Add assertions and custom exceptions
7. Add tests
*. Use erf_inv from Boost and add a test for it + parameter
?. Write output to files
    - Graphs
    - Output samples as CSV
*. Write the executable: mca --dir <> --stat "mean" -k 3 --mode "central" --dist "normal" ...
WEDNESDAY NIGHT
8. Add documentation
9. Code check and cleaning on the main branch


# Evaluation criteria and rules

Deadline: Friday 15th December 2023, 14h

- CMake build system

- One central executable that reads input

- Inline documentation of your code (Doxygen)

- Create Doxygen documentation

- Test suite

- Make a report delivered as an extended README:
    - how to compile the program
    - typical program execution (the flow) and usage
    - List of features & tests
    - TODOs and perspectives

- Make one oral presentation per student
    - the structure of the program
    - list of features
    - limitations and problems


# Evaluation
- The code
    1. must be compiling
    2. different options are inputs (no need to recompile to change behavior)
    3. should be clean (coding convention)
    4. should have inline comments (and Doxygen)
    5. must pass tests
    6. The git log entries/comments must be understandable

- The report should describe:
    1. the implementation in a consise way
    2. the validating tests
    3. the limitations and problems