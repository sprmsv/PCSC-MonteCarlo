# OUR TODO LIST

WEDNESDAY NIGHT
*. Add more assertions and custom exceptions
*. Add more tests
* Change unnecessary pointers to references + use smart pointers
*. Make some of the class members private/protected
8. Add documentation
9. Code check and cleaning on the main branch

?. Write output to files
    - Graphs
    - Output samples as CSV

?. Use erf_inv from Boost and add a test for it + parameter
?. Resolve the segmentation fault issue for CombinedFunctionSum and add other operators..
    - I couldn't do it in the end. I used debugger and breakpoints but what happens is really weird. A reference suddenly changes its address when a Vector object is created! Let's drop this for now. It wouldn't affect our code at all.


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