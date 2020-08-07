cmake_minimum_required(VERSION 3.10)

project(Example LANGUAGES CXX)

set (EXAMPLE_HAVE_FLUX_CAPACITOR False CACHE BOOL "Flux capacitor option enabled")
configure_file(config.h.in config.h)

# Add two subdirectories to the project build
add_subdirectory(library)
add_subdirectory(main)


