include ../../../make.settings

all: adios2-values-f \
     adios2-global-array-fixed-write-f adios2-global-array-fixed-read-f \
     adios2-global-array-changing-shape-write-f adios2-global-array-changing-shape-read-f 

default: all

adios2-values-f: mpivars.mod mpivars.o values.F90
	${MPIFC} -g -o adios2-values-f ${F90_MPI_FLAGS} values.F90 mpivars.o ${F90_MPI_LDFLAGS}

adios2-global-array-fixed-write-f: mpivars.mod mpivars.o decomp.mod decomp.o global-array-fixed-write.F90
	${MPIFC} -g -o adios2-global-array-fixed-write-f ${F90_MPI_FLAGS} global-array-fixed-write.F90 mpivars.o decomp.o ${F90_MPI_LDFLAGS}

adios2-global-array-fixed-read-f: mpivars.mod mpivars.o decomp.mod decomp.o global-array-fixed-read.F90
	${MPIFC} -g -o adios2-global-array-fixed-read-f ${F90_MPI_FLAGS} global-array-fixed-read.F90 mpivars.o decomp.o ${F90_MPI_LDFLAGS}

adios2-global-array-changing-shape-write-f: mpivars.mod mpivars.o decomp.mod decomp.o global-array-changing-shape-write.F90
	${MPIFC} -g -o adios2-global-array-changing-shape-write-f ${F90_MPI_FLAGS} global-array-changing-shape-write.F90 mpivars.o decomp.o ${F90_MPI_LDFLAGS}

mpivars.mod: mpivars.F90
	${MPIFC} -c mpivars.F90

mpivars.o: mpivars.F90
	${MPIFC} -c mpivars.F90

decomp.mod: decomp.F90
	${MPIFC} -c decomp.F90

decomp.o: decomp.F90
	${MPIFC} -c decomp.F90


#adios2-shapes-write-f: shapes-write.F90
#	${MPIFC} -o adios2-shapes-write-f ${F90_MPI_FLAGS} shapes-write.F90 ${F90_MPI_LDFLAGS}
#
#adios2-shapes-read-f: shapes-read.F90
#	${MPIFC} -o adios2-shapes-read-f ${F90_MPI_FLAGS} shapes-read.F90 ${F90_MPI_LDFLAGS}

clean:
	rm -rf adios2-values-f 
	rm -rf adios2-global-array-fixed-write-f adios2-global-array-fixed-read-f
	rm -rf adios2-global-array-changing-shape-write-f adios2-global-array-changing-shape-read-f
	rm -rf *.o *.mod 
	rm -rf *.bp *.sst
