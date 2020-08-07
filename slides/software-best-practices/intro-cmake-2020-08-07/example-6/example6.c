#include "config.h"

#include <mpi.h>

// Optionally include ZLIB
#ifdef EXAMPLE_HAVE_ZLIB
#include "zlib.h"
#endif

#include <stdio.h>

/* 
 * MPI example 
 * Example copied from https://mpitutorial.com/tutorials/mpi-hello-world/
 */

int main(int argc, char** argv) {

    // Initialize the MPI environment
    MPI_Init(NULL, NULL);

    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of the process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // Get the name of the processor
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);

    // Print off a hello world message
    printf("Hello world from processor %s, rank %d out of %d processors\n",
           processor_name, world_rank, world_size);

#ifdef EXAMPLE_HAVE_ZLIB    
    // Using zlib stream here as check to see of zlib was found.
    {
      int ret;
      z_stream strm;
      ret = deflateInit(&strm, Z_DEFAULT_COMPRESSION);
      if (ret != Z_OK)
        return ret;

      printf("ZLIB initialized correctly\n");
    }
#endif

    // Finalize the MPI environment.
    MPI_Finalize();
}
