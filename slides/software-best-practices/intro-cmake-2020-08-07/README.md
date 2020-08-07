# Ideas Best Practices Debugging with DDT Tutorial

The goal of this tutorial is to show the basics of CMake.

This README is not a stand-alone text, it is intended to go along with
the Webinar tutorial.

CMake is a large system so only touching the surface here.  The focus
is on setting up a first CMake project with a few simple extensions.

## What is CMake?

According to the developers of CMake (Cross-platform Makefile Generator) :

*CMake is a cross-platform free and open-source software tool for
managing the build process of software using a compiler-independent
method.*

A key thing to note is CMake does not build software, CMake manages
the setup of other tools to do the actual compilation steps.
Supported 'generators' are Unix Make (and some other makes), Visual
Studio, XCode, Eclipse, and CodeBlocks.

Some key things CMake does:

- Are utilities installed
  - Is compiler installed and does it work?
  - Where is grep?
- Finds dependencies
  - Where is Hypre installed?
  - What libraries are needed?
- Determines compiler options
  - What is the C++ 14 flag?
  - Debug/Release builds

If you have used the GNU Autoconf utilities, CMake does many of the same tasks.

CMake ecosystems also includes packages for:

- Executing tests
  - CTest testing framework
  - CDash web based reporting for test results
- Creating software installers
  - CPack


What makes CMake hard? Make cross platform builder is hard.

- There is no standard for how Unix is setup, there are many 'standards'
- Multiple versions of utilities, libraries.
- HPC systems are frequently slightly odd
  - Lots of 'special sauce'
    - Compiling MPI applications with 'mpicc'
  - Cross compiling
- CMake has it's own language

CMake uses a DSL language for specifying what is to be configured and how.

## Additional Tutorials/Documentation

### Kitware documentation

Kitware, the creators of CMake, have a good online collection of documentation and tutorials

Kitware also offers CMake classes.

#### Reference manuals and other documentation sources

https://cmake.org/documentation/

#### Introductory Tutorial

https://cmake.org/cmake/help/latest/guide/tutorial/index.html

#### Modern CMake by Henry Schreiner and others

https://cliutils.gitlab.io/modern-cmake/

#### CMake Community Wiki

Useful guides to specific CMake features.

https://gitlab.kitware.com/cmake/community/-/wikis/home

### *Mastering CMake* by Ken Martin and Bill Hoffman

I have mixed feelings about this book.  The first chapters can be
useful for getting a general introduction but more than half the book
is reference content.  Easier and more up-to-date to just look at the
online reference material.  Also needs an update, covers CMake 3.1.

### *CMake Cookbook* by Radovan Bast and Roberto Di Remigio

Has anyone in group read this?

## Installing CMake

Should be available on most HPC center and in software package for Linux distributions.

https://cmake.org/download/

### CMake binaries

ParFlow requires a CMake version newer than what some systems provide,
we have had good success downloading the binaries provided by KitWare.

Here is example from our Dockerfile for ParFlow and we have used the same method for
installing on other platforms when needed.

```bash
CMAKE_DIR=/home/parflow/cmake-3.14.5-Linux-x86_64
PATH=$PATH:$CMAKE_DIR/bin
cd /home/parflow
wget -nv --no-check-certificate http://cmake.org/files/v3.14/cmake-3.14.5-Linux-x86_64.tar.gz
tar -xvf cmake-3.14.5-Linux-x86_64.tar.gz
```

## Downloading the tutorial examples

All of the tutorials are in the IDEAS-Watersheds repository.

```bash
git clone https://github.com/IDEAS-Watersheds/best-practices-seminar.git
cd best-practices-seminar/slides/software-best-practices/intro-cmake-2020-08-07
```

## Single File Example

The example-1 directory has a very basic CMake example.   Single source file (example1.cxx) and no dependencies.

### CMakeLists.txt

CMake uses text files (CMakeLists.txt) for configuring a project.   Here what the CMakeList.txt looks like:

```cmake
# What version of CMake is require for this project
cmake_minimum_required(VERSION 3.10)

# Name of the project
project(Example1)

# Adds an example to the project, single source file
add_executable(example1 example1.cxx)
```

#### Creating a UNIX Makefile

You setup a build directory for running CMake, this keeps the
temporary build files, object files, executables separated from the
source code.  Directory is conventionally called 'build' and is
normally created at the root of the source tree or parallel to it.

Command to run CMake on a Unix system:

```bash
cd example-1

mkdir build

cmake ..
```

The ".." argument to cmake specifies the path to the project CMakeLists.txt file.

This doesn't build the example, it creates the files needed to build.  In this case a Makefile and several other support files:

```
CMakeCache.txt CMakeFiles cmake_install.cmake Makefile
```

#### Building the application with Unix Make

You then build using the generated Makefile:

```bash
make
```

To see list of available make build targets:

```bash
make help
``` 
CMake can be used to invoke 'make' for more portability (e.g. when
using something other than 'make' to build).

```bash
cmake -- build .
```
And execute the example built:

```bash
./example1
```
## Setting CMake Variables

CMake uses variables to configure/store options for the build,
variables are used for build configure items like path to install,
compiler options, paths to libraries etc.

Variables are split into two groups non-advanced (unadvanced) and
advanced.  This is used in CMake GUI applications, user sees
non-advanced only unless they click an 'advanced' button.

Two common variable to set when building are the installation prefix and 
the build type.  Default build type is normally release but if you want
extra debugging information Debug is useful.

```bash
cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=<directory> ..
```

To see list of non-advanced variables:

```bash
cmake -L
```

To see list of all variables:

```bash
cmake -LA
```

You can also configure with the 'ccmake' command to get a simple terminal based GUI:

```bash
ccmake ..
```

The 'cmake-gui' command is a full GUI application:

```bash
cmake-gui ..
```

Guide on how to use CMake:

https://cmake.org/cmake/help/latest/guide/user-interaction/index.html

A GUI also exist for Windows; MacOS supports cmake-gui.

## Example with a library and application

The example8 directory has an example with a main application and a library.

## Example Adding Setting Compiler Flag

A common portability problem is platforms/compilers use different
options/flags.  CMake can help specify these in a platform/compiler
independent way.  This assumes that your compiler is support by CMake but
most are (GNU, Intel, Cray, XLC).

Example is supplied in example-2 directory.

### CMakeLists.txt

```cmake
# What version of CMake is require for this project
cmake_minimum_required(VERSION 3.10)

# Name of the project
project(Example2)

# Use C++14 options in this compile as example of using CMake to
# set compilation options in a platform/compiler independent way.
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Adds an example to the project, single source file
add_executable(example2 example2.cxx)
```

### Creating the Unix Makefile

Same as example 1:

```bash
cd example-2
mkdir build
cmake ..
```

### What is going on in my build?

By default CMake hides what the build is doing.  The 'VERBOSE=1' flag will show commands as they execute:

```bash
make VERBOSE=1
```

On my system one of the verbose output lines shows the compile step.
Here we can see CMake add the '-std=gnu++14' argument to use C++14 as
requested.

```bash
/usr/bin/c++    -std=gnu++14 -o CMakeFiles/example2.dir/example2.cxx.o -c /home/smithsg/projects/ideas/best-practices-seminar/slides/software-best-practices/intro-cmake-2020-08-07/example-2/example2.cxx
```

For problems with CMake there is a trace option to print what CMake is doing

```bash
cmake --trace ..
```

This generates a stupendous amount of output.   Can limit to a single CMake file with --trace-source="filename".

## Multiple Source Files and First Look At CMake Variables

Multiple source files, showing use of a variable in CMake.

This example is in directory example-3.  Steps to build are same as previous examples.

```cmake
# Adds an example to the project, multiple source files using a
# local variable to store names of the source files
set(SRC example3.cxx unique-code.cxx)
add_executable(example3 ${SRC})
```

## MPI Example Using An IMPORTED Target

There are several ways to create dependencies on libraries/packages in CMake.

- A Package as an IMPORTED target
  - This is the best way
  - Newer feature (requires CMake 3.9)
  - Not all packages support this feature 
  - find_package()
  - IMPORTED target is added to target_link_libraries
- A Package as imported variables
  - The older style
  - find_package()
  - Variables are imported like
    - HYPRE_FOUND
    - HYPRE_INCLUDE_DIR
	- HYPRE_LIBRARIES
  - Not all package maintainers supply the same variables and quality of the finders varies
    - Conventions are not always followed and were not very well documented
- Manually specify directories, libraries
  - Not as flexible, have to be careful if you want platform independence.
  - Can directly specify 
    - include paths
	- libraries
	- etc

CMake packages are documented here:
https://cmake.org/cmake/help/latest/manual/cmake-packages.7.html

This example is in directory example-4.  Steps to build are same as previous examples.

This example will require MPI to be installed and use an MPI which is
supported by the CMake supplied MPI scripts for finding MPI.  So far I
have found this be portable across all systems tested.  Have built on MacOS, Linux,
various HPC centers and several implementations of MPI (OpenMPI, MVAPICH).

For MPI, highly recommend to use CMake version 3.10 or greater since
support was improved in that release.

Many libraries have scripts supplied by CMake to determine what include paths
and libraries need to be included for compilation using
find_package.  Here we find MPI, since this is an MPI application it
is marked as required.

find_package is used to find packages.  You need to supply the package
name.  "REQUIRED" can be used to make it a required package; CMake
will stop if package isn't found.

```cmake
find_package(MPI REQUIRED)
```

MPI dependency is add as an IMPORTED target.

```cmake
target_link_libraries(example4 PRIVATE MPI::MPI_C)
```

## Zlib Example Using Package With Variables

This is the old style, will likely see this if you look at CMake
examples and other projects.  For example ParFlow is still using this
older method.

Rather than libraries and paths being added abstractly, the
find_package sets variables with information needed.  You then add the
paths/libraries as needed.

```cmake
  find_package(ZLIB)

  target_include_directories(example5 PUBLIC "${ZLIB_INCLUDE_DIRS}")

  target_link_libraries(example5 PRIVATE ${ZLIB_LIBRARIES} )
```

This example is in directory example-5.  Steps to build are same as previous examples.

## Optionally Compile With Zlib

For cases when you optionally wish to use a library you can do
standard C/C++ compile guards using symbols defined by CMake.  First
we use the ZLIB_FOUND variable which is set by the find_package to
create a new CMake variable for our project.

```cmake
find_package(ZLIB)

if (${ZLIB_FOUND})
  set(EXAMPLE_HAVE_ZLIB "yes")
endif (${ZLIB_FOUND})
```

We want to get EXAMPLE_HAVE_LIB visible to the compiler, could do a
command line flag but putting configuration state into a file is
better.

This line will process the template config.h.in file to config.h; replaces symbols
in the .in file based on CMake variables.  Here EXAMPLE_HAVE_ZLIB
will be set in config.h when ZLIB is found.

```cmake
configure_file(config.h.in config.h)
```

The config.h.in template file has a place-holder for the EXAMPLE_HAVE_ZLIB

```c
#cmakedefine EXAMPLE_HAVE_ZLIB
```

The generated config.h file is put in the binary directory by default
so we need to put the directory on the include path for the
compilation.

```cmake
target_include_directories(example6 PUBLIC "${PROJECT_BINARY_DIR}")
```

CMake has a number of pre-defined variables for the source, binary,
install directories.  There are also many variables that give you
information about the compilation environment and let you control the
compilation.

https://cmake.org/cmake/help/latest/manual/cmake-variables.7.html

This example is in directory example-6.  Steps to build are same as previous examples.
  
## User configuration flags example

You can create your own flags to enable a user to set compile options.
Say we have an optional flux capacitor feature.  In the CMakeLists.txt
file we can create a new variable that will be put in the
configuration cache.

The value (False) is the default value which user can override.  Type
is just a boolean, CMake treats 0/1, true/false, on/off, yes/no all as boolean
values.  Comment description is supplied and can be seen in the CMake GUI.

```cmake
set (EXAMPLE_HAVE_FLUX_CAPACITOR False CACHE BOOL "Flux capacitor option enabled")
```

In our config.h.in file we use #cmakedefine so symbol will be replaced

```c
#cmakedefine EXAMPLE_HAVE_FLUX_CAPACITOR
```

Example is directory example-7. Since we now have a user configuration
flag for the build we need need to set it.

With no options:

```bash
cmake ..
```

we will get the default (flux capacitor turned off).


You can set CMake variables from the command line using the -D option:

```bash
cmake -DEXAMPLE_HAVE_FLUX_CAPACITOR=on ..
```

This will turn on the flux capacitor.


