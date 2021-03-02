include ../../../make.settings

default: adios2-module-example

adios2-module-example: mpivars.mod mpivars.o adiosio.mod adiosio.o
	${MPIFC} -DADIOS2 -c -o main.o main.F90
	${MPIFC} -o adios2-module-example main.o mpivars.o adiosio.o ${F90_MPI_LDFLAGS}

mpivars.mod: mpivars.F90
	${MPIFC} -c mpivars.F90

adiosio.mod: adiosio.F90
	${MPIFC} -c ${F90_MPI_FLAGS} adiosio.F90

clean:
	rm -rf adios2-module-example
	rm -rf mpivars.mod adiosio.mod adiosio.smod
	rm -rf *.o *.bp *.sst
