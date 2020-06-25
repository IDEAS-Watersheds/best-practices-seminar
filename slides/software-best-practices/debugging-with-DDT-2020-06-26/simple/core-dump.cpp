#include "mpi.h"

#include <iostream>

using namespace std;

void dowork(int rank)
{
    double* ptr = 0;

    if(rank == 2)
    {
       *ptr = 1234.0;
    }
}

int main( int argc, char *argv[] )
{
    int rank, size;
    
    MPI_Init( &argc, &argv );
    
    MPI_Comm_rank( MPI_COMM_WORLD, &rank );
    MPI_Comm_size( MPI_COMM_WORLD, &size );

    cout << "Hello World from rank " << rank
	 << " of size " << size << "\n";

    dowork(rank);

    MPI_Finalize();
    
    return 0;
}
