# What version of CMake is require for this project
cmake_minimum_required(VERSION 3.10)

# Name of the project
project(Example3 LANGUAGES CXX)

# Adds an example to the project, multiple source files using a
# variable to store names of the source files
set(SRC example3.cxx unique-code.cxx)
add_executable(example3 ${SRC})

target_compile_features(example3 PRIVATE cxx_std_14)
