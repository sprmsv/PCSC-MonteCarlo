# OUR TODO LIST

!!. Document the code

?. Write output to files
    - Graphs
    - Output samples as CSV

* Change unnecessary pointers to references + use smart pointers
*. Make some of the class members private/protected
*. Set precision and formatting for the output streams
    - use std::cout.flush()
    - use ofstream.setf(std::ios::scientific)
    - use ofstream.setf(std::ios::showpos)
    - use ofstream.precision(4)
*. Features not used:
    - function pointers and std::function
    - private members and friend classes/functions
    - Copy the pointer or copy the content when copying another object??
    - (non-pure) virtual methods and calling them from the daughter classes
    - ...

*. Add more tests

!!. Code check and cleaning on the main branch:
    - Remove extra comments
    - Consistent spacing
    - Add more assertions if related
    - Remove trailing whitespaces

!!. Proof-read the readme and the documentation

## LET'S DROP THESE:
?. Use erf_inv from Boost and add a test for it + parameter
?. Resolve the segmentation fault issue for CombinedFunctionSum and add other operators..
    - I couldn't do it in the end. I used debugger and breakpoints but what happens is really weird. A reference suddenly changes its address when a Vector object is created! Let's drop this for now. It wouldn't affect our code at all.


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
