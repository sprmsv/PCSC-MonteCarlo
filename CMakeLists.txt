cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Project
project(MC VERSION 0.1)
set(MC_VERSION_NUMBER ${MC_VERSION_MAJOR}.${MC_VERSION_MINOR})
set(MC_SOURCE_DIR mc)

# External libraries
add_subdirectory(eigen)

# Executables
file(GLOB filesmain ${MC_SOURCE_DIR}/*.cpp)
add_executable(main ${MC_SOURCE_DIR}/main.cpp ${filesmain})

# External libraries
target_link_libraries(main PUBLIC eigen)
target_include_directories(main PUBLIC ${PROJECT_BINARY_DIR} ${PROJECT_SOURCE_DIR}/eigen)

# # How to add data file
# file(COPY test.dat DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# TODO: Consider adding options
# TODO: Consider deinitializing submodules if not needed

message(STATUS "")
message(STATUS "Configured MC ${MC_VERSION_NUMBER}")
message(STATUS "")
