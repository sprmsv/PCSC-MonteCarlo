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
set(GTEST_SOURCE_DIR ${PROJECT_SOURCE_DIR}/gtest)

# Get source and test files
file(GLOB mcfiles ${MC_SOURCE_DIR}/*.cpp ${MC_SOURCE_DIR}/*.hpp ${MC_SOURCE_DIR}/*.tpp)
file(GLOB testfiles ${TESTS_SOURCE_DIR}/*.cpp ${TESTS_SOURCE_DIR}/*.hpp ${TESTS_SOURCE_DIR}/*.tpp)

# Add subdirectories and libraries
add_subdirectory(${EIGEN_SOURCE_DIR})
add_subdirectory(${MC_SOURCE_DIR})
add_subdirectory(${GTEST_SOURCE_DIR})

# Add library and executables
add_library(mc ${mcfiles})
add_executable(main main.cpp)
add_executable(tests ${testfiles})


# Link libraries and include directories
target_link_libraries(main PRIVATE mc eigen)
target_link_libraries(mc PRIVATE eigen)
target_include_directories(main PRIVATE ${PROJECT_BINARY_DIR} ${MC_SOURCE_DIR} ${EIGEN_SOURCE_DIR})
target_link_libraries(tests PRIVATE mc eigen gtest gtest_main)
target_include_directories(tests PRIVATE ${PROJECT_BINARY_DIR} ${MC_SOURCE_DIR} ${EIGEN_SOURCE_DIR} ${TESTS_SOURCE_DIR})

# # How to add data file
# file(COPY test.dat DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Print success messages
message(STATUS "")
message(STATUS "Configured MC ${MC_VERSION_NUMBER}")
message(STATUS "")

# Install targets
install(TARGETS main DESTINATION bin)

# Generate API documentation with Doxygen
message(STATUS "Generating API documentation with Doxygen.")
find_package(Doxygen)
if (DOXYGEN_FOUND)
    # Set input and output files
    set(DOXYGEN_IN ${PROJECT_SOURCE_DIR}/docs/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
    # Request to configure the file
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started.")
    add_custom_target(
        doc_doxygen ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    )
else (DOXYGEN_FOUND)
  message("Doxygen was not found. Please install Doxygen and build again.")
endif (DOXYGEN_FOUND)

# Print success messages
message(STATUS "")
message(STATUS "Done!")
message(STATUS "")
