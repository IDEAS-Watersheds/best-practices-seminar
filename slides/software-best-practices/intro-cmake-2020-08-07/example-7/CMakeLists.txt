cmake_minimum_required(VERSION 3.10)

project(Example)

set (EXAMPLE_HAVE_FLUX_CAPACITOR False CACHE BOOL "Flux capacitor option enabled")

# Configure with user supplied flux capacitor option
configure_file(config.h.in config.h)

add_executable(example7 example7.cxx)

target_include_directories(example7 PUBLIC "${PROJECT_BINARY_DIR}")
