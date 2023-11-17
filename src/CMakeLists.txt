# cmake_minimum_require must be the first command of the file
cmake_minimum_required(VERSION 3.5.0)

project(PCSC)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(main main.cpp)

## How to add data file
# file(COPY test.dat DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
