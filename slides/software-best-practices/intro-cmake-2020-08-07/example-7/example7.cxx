#include "config.h"

#include <iostream>

int main(int argv, char** argc)
{
  std::cout << "CMake example\n";

#ifdef EXAMPLE_HAVE_FLUX_CAPACITOR
  std::cout << "Flux capacitor initiated\n";
#endif
}
