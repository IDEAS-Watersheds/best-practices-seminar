# What version of CMake is require for this project
cmake_minimum_required(VERSION 3.10)

# Name of the project
project(Example6 LANGUAGES C)

find_package(MPI REQUIRED)

find_package(ZLIB)

if (${ZLIB_FOUND})
  set(EXAMPLE_HAVE_ZLIB "yes")
endif (${ZLIB_FOUND})

set(SRC example6.c )
add_executable(example6 ${SRC})

# Process the template config.h.in file to config.h; replaces symbols
# in the .in file based on CMake variables.  Here EXAMPLE_HAVE_ZLIB
# will be set in config.h when ZLIB is found.
configure_file(config.h.in config.h)

# The generated config.h file is put in the binary directory by
# default so we need to put the directory on the include path for the
# compiliation.
target_include_directories(example6 PUBLIC "${PROJECT_BINARY_DIR}" "${ZLIB_INCLUDE_DIRS}")

# ZLIB libraries are added to link; ZLIB_LIBRARIES variable is set by
# find_package(ZLIB)
# MPI dependency is add as an IMPORTED target.
# See https://cmake.org/cmake/help/latest/manual/cmake-packages.7.html
target_link_libraries(example6 PRIVATE MPI::MPI_C "${ZLIB_LIBRARIES}" )
