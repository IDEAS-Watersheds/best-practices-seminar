# What version of CMake is require for this project
cmake_minimum_required(VERSION 3.10)

# Name of the project
project(Example2)

# Use C++14 options in this compile as example of using CMake to
# set compilation options in a platform/compiler independent way.
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Adds an example to the project, multiple source files using a
# variable to store names of the source files
set(SRC example3.cxx unique-code.cxx)
add_executable(example3 ${SRC})
