#include "unique-code.h"

/*
 * Example copied from https://en.cppreference.com/w/cpp/memory/unique_ptr/make_unique
 */
void afunction (void)
{

  // Use the default constructor.
  std::unique_ptr<Vec3> v1 = std::make_unique<Vec3>();
  // Use the constructor that matches these arguments
  std::unique_ptr<Vec3> v2 = std::make_unique<Vec3>(0, 1, 2);
  // Create a unique_ptr to an array of 5 elements
  std::unique_ptr<Vec3[]> v3 = std::make_unique<Vec3[]>(5);
  
  std::cout << "make_unique<Vec3>():      " << *v1 << '\n'
	    << "make_unique<Vec3>(0,1,2): " << *v2 << '\n'
	    << "make_unique<Vec3[]>(5):   " << '\n';
  for (int i = 0; i < 5; i++) {
    std::cout << "     " << v3[i] << '\n';
  }
}
