# What version of CMake is require for this project
cmake_minimum_required(VERSION 3.10)

# Name of the project
project(Example4)


# Many libraries have scripts supplied to determine what include paths
# and libraries need to be included for compliation using
# find_package.  Here we find MPI, since this is an MPI application it
# is marked as required.
find_package(MPI REQUIRED)

set(SRC example4.c )
add_executable(example4 ${SRC})

# MPI dependency is add as an IMPORTED target.
# See https://cmake.org/cmake/help/latest/manual/cmake-packages.7.html#id8
target_link_libraries(example4 PRIVATE MPI::MPI_C)
