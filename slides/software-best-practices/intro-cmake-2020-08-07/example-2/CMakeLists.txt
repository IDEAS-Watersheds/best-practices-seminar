# What version of CMake is require for this project
cmake_minimum_required(VERSION 3.10)

# Name of the project
project(Example2 LANGUAGES CXX)

# Use C++14 options in this compile as example of using CMake to
# set compilation options in a platform/compiler independent way.
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Adds an example to the project, single source file
add_executable(example2 example2.cxx)

# Note the current 'modern' way to specify compiler is using an INTERFACE target
# and not set the CMake compiler variables directly:
# target_compile_features(example2 PRIVATE cxx_std_14)




