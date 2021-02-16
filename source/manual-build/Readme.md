These examples show how to quickly compile an example from the command line. 
The adios2-config script from the ADIOS2 installation provides compiler and linker flags for C, C++ and Fortran. It provides flags for both serial and parallel applications. 

The notes below assume, ADIOS2 is in the path, and the MPI compilers are (mpic++, mpicc, mpif90) and serial compilers are (g++, gcc, gfortran). You need to modify the commands below for your own environment and choice of compilers. 

Compiling and linking a C++/MPI program
=======================================

Compile and link example-mpi.cpp -> example-mpi-cpp

CXXFLAGS=`adios2-config --cxx-flags`
LDFLAGS=`adios2-config --cxx-libs`
mpic++ -o example-mpi-cpp ${CXXFLAGS} example-mpi.cpp ${LDFLAGS}

Compiling and linking a C++ serial program
==========================================

Compile and link example-serial.cpp -> example-serial-cpp

CXXFLAGS=`adios2-config --cxx-flags -s`
LDFLAGS=`adios2-config --cxx-libs -s`
g++ -o example-serial-cpp ${CXXFLAGS} example-serial.cpp ${LDFLAGS}


Compiling and linking a C/MPI program 
=====================================

Compile and link example-mpi.c -> example-mpi-c

CFLAGS=`adios2-config --c-flags`
LDFLAGS=`adios2-config --c-libs`
mpicc -o example-mpi-c ${CFLAGS} example-mpi.c ${LDFLAGS}

Compiling and linking a C serial program
========================================

Compile and link example-serial.c -> example-serial-c

CFLAGS=`adios2-config --c-flags -s`
LDFLAGS=`adios2-config --c-libs -s`
gcc -o example-serial-c ${CXXFLAGS} example-serial.c ${LDFLAGS}


Compiling and linking a Fortran/MPI program 
===========================================

Compile and link example-mpi.F90 -> example-mpi-f

FCFLAGS=`adios2-config --fortran-flags`
LDFLAGS=`adios2-config --fortran-libs`
mpif90 -o example-mpi-f ${FCFLAGS} example-mpi.F90 ${LDFLAGS}

Compiling and linking a Fortran serial program
==============================================

Compile and link example-serial.F90 -> example-serial-f

FCFLAGS=`adios2-config --fortran-flags -s`
LDFLAGS=`adios2-config --fortran-libs -s`
gfortran -o example-serial-f ${FCFLAGS} example-serial.F90 ${LDFLAGS}


 

