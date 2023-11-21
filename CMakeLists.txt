cmake_minimum_required(VERSION 3.10)

project(PCSC-MC VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Eigen library
add_subdirectory(eigen)

add_executable(main mc/main.cpp)

## How to add data file
# file(COPY test.dat DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
