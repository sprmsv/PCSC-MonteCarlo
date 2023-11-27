cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Project specifications
project(MC VERSION 0.1)
set(MC_VERSION_NUMBER ${MC_VERSION_MAJOR}.${MC_VERSION_MINOR})
enable_testing()

# Set directories
set(MC_SOURCE_DIR ${PROJECT_SOURCE_DIR}/mc)
set(TESTS_SOURCE_DIR ${PROJECT_SOURCE_DIR}/tests)
set(EIGEN_SOURCE_DIR ${PROJECT_SOURCE_DIR}/eigen)

# Get source and test files
file(GLOB mcfiles ${MC_SOURCE_DIR}/*.cpp ${MC_SOURCE_DIR}/*.hpp ${MC_SOURCE_DIR}/*.tpp)
file(GLOB testfiles ${TESTS_SOURCE_DIR}/*.cpp)

# Add subdirectories and libraries
add_subdirectory(${EIGEN_SOURCE_DIR})
add_subdirectory(${MC_SOURCE_DIR})

# Add library and executables
add_library(mc ${mcfiles})
add_executable(main main.cpp)

# Link libraries and include directories
target_link_libraries(main PRIVATE mc eigen)
target_link_libraries(mc PRIVATE eigen)
target_include_directories(main PRIVATE ${PROJECT_BINARY_DIR} ${MC_SOURCE_DIR} ${EIGEN_SOURCE_DIR})

# Add tests
FOREACH(testfile ${testfiles})
    get_filename_component(testname ${testfile} NAME_WLE)
    add_executable(${testname} ${testfile})
    target_link_libraries(${testname} PRIVATE mc eigen)
    target_include_directories(${testname} PRIVATE ${PROJECT_BINARY_DIR} ${MC_SOURCE_DIR} ${EIGEN_SOURCE_DIR})
    add_test(NAME ${testname} COMMAND $<TARGET_FILE:${testname}>)
ENDFOREACH(testfile)

# # How to add data file
# file(COPY test.dat DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# TODO: Consider adding options
# TODO: Consider deinitializing submodules if not needed

message(STATUS "")
message(STATUS "Configured MC ${MC_VERSION_NUMBER}")
message(STATUS "")
