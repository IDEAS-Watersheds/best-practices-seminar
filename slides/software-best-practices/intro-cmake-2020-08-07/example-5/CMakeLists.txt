# What version of CMake is require for this project
cmake_minimum_required(VERSION 3.10)

# Name of the project
project(Example5)

find_package(MPI REQUIRED)

find_package(ZLIB)

set(SRC example5.c )
add_executable(example5 ${SRC})

# ZLIB libraries are added to link; ZLIB_LIBRARIES variable is set by find_package(ZLIB)
# MPI dependency is add as an IMPORTED target.
# See https://cmake.org/cmake/help/latest/manual/cmake-packages.7.html#id8
target_link_libraries(example5 PRIVATE MPI::MPI_C ${ZLIB_LIBRARIES} )

