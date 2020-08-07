
# Adds a library which called 'lib8' with functions from flux capacitor
add_library(lib8 flux-capacitor.cxx)

# Directory for config.h file
target_include_directories(lib8 PUBLIC "${PROJECT_BINARY_DIR}")

# Indicates the library should be compiled with C++ 14.  Making this
# public indicates that applications that link should also be C++ 14.
target_compile_features(lib8 PUBLIC cxx_std_14)

# Lots of special CMake magic happening here. We want to inform
# applications that use lib8 where the include headers are.   They
# could be in the current build or in the installation directory.
# The $<...> syntax is what CMake calls "generator expressions".
# There is more information here:
# https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#manual:cmake-generator-expressions(7)
target_include_directories(lib8 PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>  # <prefix>/include
)


