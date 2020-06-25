
# For NERSC CORI
CXX=CC
MPI_EXEC=srun --qos=interactive -C haswell 

# For OpenMPI
#CXX=mpicxx
#MPI_EXEC=mpiexec

EXAMPLES=hello-world core-dump

default : $(EXAMPLES)

# NERSC recommends using -O0 with the Intel compiler (used by default on Cori system)
hello-world: hello-world.cpp
	$(CXX) -g -O0 -o hello-world hello-world.cpp

run-hello: hello-world
	 $(MPI_EXEC) -n 4 ./hello-world


core-dump: core-dump.cpp
	$(CXX) -g -O0 -o core-dump core-dump.cpp

run-hello: core-dump
	 $(MPI_EXEC) -n 4 ./core-dump

clean:
	rm -f $(EXAMPLES)
