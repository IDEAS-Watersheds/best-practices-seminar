
// Note we are putting headers in subdirectory 'lib8' in order to
// put a namespace on the header files.
#include "lib8/flux-capacitor.h"

#include "config.h"

#include <iostream>

void flux_capacitor(void)
{
#ifdef EXAMPLE_HAVE_FLUX_CAPACITOR
  std::cout << "Flux capacitor initiated\n";
#else
  std::cout << "Flux capacitor not available\n";
#endif
}
