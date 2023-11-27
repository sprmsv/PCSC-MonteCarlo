cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Project specifications
project(MC VERSION 0.1)
set(MC_VERSION_NUMBER ${MC_VERSION_MAJOR}.${MC_VERSION_MINOR})
enable_testing()

# Get source and test files
set(MC_SOURCE_DIR mc)
set(TESTS_SOURCE_DIR tests)
file(GLOB sourcefiles ${MC_SOURCE_DIR}/*.cpp)
file(GLOB testfiles ${TESTS_SOURCE_DIR}/*.cpp)

# Add libraries
add_library(mc ${sourcefiles})
add_subdirectory(mc)
add_subdirectory(eigen)

# Add executables
add_executable(main main.cpp)
target_link_libraries(main PUBLIC eigen mc)
target_include_directories(main PUBLIC ${PROJECT_BINARY_DIR} ${PROJECT_SOURCE_DIR}/eigen ${PROJECT_SOURCE_DIR}/mc)

# Add tests
FOREACH(testfile ${testfiles})
    get_filename_component(testname ${testfile} NAME_WLE)
    add_executable(${testname} ${testfile})
    target_link_libraries(${testname} PRIVATE eigen mc)
    target_include_directories(${testname} PRIVATE ${PROJECT_BINARY_DIR} ${PROJECT_SOURCE_DIR}/eigen ${PROJECT_SOURCE_DIR}/mc)
    add_test(NAME ${testname} COMMAND $<TARGET_FILE:${testname}>)
ENDFOREACH(testfile)

# # How to add data file
# file(COPY test.dat DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# TODO: Consider adding options
# TODO: Consider deinitializing submodules if not needed

message(STATUS "")
message(STATUS "Configured MC ${MC_VERSION_NUMBER}")
message(STATUS "")
