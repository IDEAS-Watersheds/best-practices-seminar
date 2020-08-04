
# Simple application that uses the lib8 library
add_executable(example8 example8.cxx)

# Note we don't have to specify include directories and libraries explicity.  This is
# done by specify the target_include_directories when defining the library.  The library
# include directories will be included when compiling the example8.cxx file because
# we introduced the dependency on lib8.
target_link_libraries(example8 PRIVATE lib8)

# We are targeting C++ 14
target_compile_features(example8 PUBLIC cxx_std_14)

# Interesting side note, if you specify C++11 for the main example code
# the compile will get promoted to C++ 14 since lib8 specified C++14 was needed.
# target_compile_features(example8 PUBLIC cxx_std_11)
