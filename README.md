# Monte Carlo Approximation

This library deals with the statistical study of non-linear operators by approximating expectations and statistical moments using Monte Carlo methods.

All the following instructions presume that the current working directory is the project's root directory.

First, make sure that [Doxygen](https://www.doxygen.nl/manual/install.html) and [Graphviz](https://graphviz.org/download/) are installed:
```bash
doxygen --version
dot --version
```
If not, please install them.

Initialize the submodules:
```bash
git submodule update --init eigen
git submodule update --init gtest
```

To build the project:
```bash
cmake -S . -B ./build
cmake --build ./build
```

To run the tests:
```bash
build/tests
```

To run the code:
```bash
build/main ...
```

To see the input arguments:
```bash
build/main --help
```

To open the documentation:
```bash
open build/documentation/html/index.html
```

# Contributions

This project is part of the Programming Concepts in Scientific Computing (MATH-458) course at École Polytechnique Fédérale de Lausanne (EPFL), given in Fall 2023.

## Authors

- Sepehr Mousavi ([sepehr.mousavi@epfl.ch](mailto:sepehr.mousavi@epfl.ch))
- Paul Devianne ([paul.devianne@epfl.ch](mailto:paul.devianne@epfl.ch))

## Instructors

- Guillaume Anciaux ([guillaume.anciaux@epfl.ch](mailto:guillaume.anciaux@epfl.ch))
- Haoze He ([haoze.he@epfl.ch](mailto:haoze.he@epfl.ch))
