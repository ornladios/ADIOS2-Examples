include ../../../make.settings

#all: adios2-values-c \
#     adios2-global-array-fixed-write-c adios2-global-array-fixed-read-c \
#     adios2-global-array-changing-shape-write-c adios2-global-array-changing-shape-read-c

all: adios2-global-array-fixed-write-c


default: all

adios2-values-c: mpivars.o values.c
	${MPICC} -g -o adios2-values-c ${C_MPI_FLAGS} values.c mpivars.o ${C_MPI_LDFLAGS}

adios2-global-array-fixed-write-c: mpivars.o decomp.o global-array-fixed-write.c
	${MPICC} -g -o adios2-global-array-fixed-write-c ${C_MPI_FLAGS} global-array-fixed-write.c mpivars.o decomp.o ${C_MPI_LDFLAGS}

adios2-global-array-fixed-read-c: mpivars.o decomp.o global-array-fixed-read.c
	${MPICC} -g -o adios2-global-array-fixed-read-c ${C_MPI_FLAGS} global-array-fixed-read.c mpivars.o decomp.o ${C_MPI_LDFLAGS}

adios2-global-array-changing-shape-write-c: mpivars.o decomp.o global-array-changing-shape-write.c
	${MPICC} -g -o adios2-global-array-changing-shape-write-c ${C_MPI_FLAGS} global-array-changing-shape-write.c mpivars.o decomp.o ${C_MPI_LDFLAGS}

mpivars.o: mpivars.c
	${MPICC} -c mpivars.c

decomp.o: decomp.c
	${MPICC} -c decomp.c


clean:
	rm -rf adios2-values-f
	rm -rf adios2-global-array-fixed-write-f adios2-global-array-fixed-read-f
	rm -rf adios2-global-array-changing-shape-write-f adios2-global-array-changing-shape-read-f
	rm -rf *.o *.mod
	rm -rf *.bp *.sst
