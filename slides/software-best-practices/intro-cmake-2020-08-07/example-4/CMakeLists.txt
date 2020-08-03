# What version of CMake is require for this project
cmake_minimum_required(VERSION 3.10)

# Name of the project
project(Example4)


# Many libraries have scripts supplied to determine what include paths
# and libraries need to be included for compliation.  Here we find
# MPI, since this is an MPI application it is marked as required.
find_package(MPI REQUIRED)

# Adds an example to the project, multiple source files using a
# variable to store names of the source files
set(SRC example4.c )
add_executable(example4 ${SRC})
