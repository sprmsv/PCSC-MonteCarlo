cmake_minimum_required(VERSION 3.10)
project(PCSC-MC VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# # Include paths
# include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# External libraries
add_subdirectory(eigen)

# Executables
add_executable(main mc/main.cpp)

# External libraries
target_link_libraries(main PUBLIC eigen)
target_include_directories(main PUBLIC ${PROJECT_BINARY_DIR} ${PROJECT_SOURCE_DIR}/eigen)

# # How to add data file
# file(COPY test.dat DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# TODO: Consider adding options and messages
