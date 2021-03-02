.. _section-manual-build:

############
Manual build
############

Location of the example(s): ``source/manual-build``

The notes below assume, ADIOS2 is in the path, and the MPI compilers are (mpic++, mpicc, mpif90) and serial compilers are (g++, gcc, gfortran). You need to modify the commands below for your own environment and choice of compilers.

MPI vs serial codes
*******************

A single installation of the ADIOS2 library can be used for both serial and MPI applications. You need to use the correct compile flags and link libraries to build your code. Basically, the MPI functions are incorporated in separate libraries (`libadios2_core_mpi.so`, `libadios2_cxx_mpi.so`, `libadios2_fortran_mpi.so`, `libadios2_c_mpi.so`), which you need to add to the linking phase.

adios2-config
*************

The `adios2-config` utility is created during the installation of ADIOS2 (not during build!). It is located in the `bin/` directory of the installation. It provides the compiler flags and linker libraries to your manual/Makefile builds.

    .. code-block:: bash

        $ adios2-config -h
        adios2-config [OPTION]
          -h, --help       Display help information
          -v, --version    Display version information
          -c               Both compile and link flags for the C bindings
          --c-flags        Preprocessor and compile flags for the C bindings
          --c-libs         Linker flags for the C bindings
          -x, --cxx        Both compile and link flags for the C++ bindings
          --cxx-flags      Preprocessor and compile flags for the C++ bindings
          --cxx-libs       Linker flags for the C++ bindings
          -f, --fortran    Both compile and link flags for the F90 bindings
          --fortran-flags  Preprocessor and compile flags for the F90 bindings
          --fortran-libs   Linker flags for the F90 bindings
          -s, --serial     Select flags for serial applications
          -m, --mpi        Select flags for mpi applications



Compiling and linking a C++/MPI program
***************************************

Compile and link example-mpi.cpp -> example-mpi-cpp

    .. code-block:: bash

        CXXFLAGS=`adios2-config --cxx-flags`
        LDFLAGS=`adios2-config --cxx-libs`
        mpic++ -o example-mpi-cpp ${CXXFLAGS} example-mpi.cpp ${LDFLAGS}

Compiling and linking a C++ serial program
******************************************

Compile and link example-serial.cpp -> example-serial-cpp

    .. code-block:: bash

        CXXFLAGS=`adios2-config --cxx-flags -s`
        LDFLAGS=`adios2-config --cxx-libs -s`
        g++ -o example-serial-cpp ${CXXFLAGS} example-serial.cpp ${LDFLAGS}


Compiling and linking a C/MPI program
*************************************

Compile and link example-mpi.c -> example-mpi-c

    .. code-block:: bash

        CFLAGS=`adios2-config --c-flags`
        LDFLAGS=`adios2-config --c-libs`
        mpicc -o example-mpi-c ${CFLAGS} example-mpi.c ${LDFLAGS}

Compiling and linking a C serial program
****************************************

Compile and link example-serial.c -> example-serial-c

    .. code-block:: bash

        CFLAGS=`adios2-config --c-flags -s`
        LDFLAGS=`adios2-config --c-libs -s`
        gcc -o example-serial-c ${CXXFLAGS} example-serial.c ${LDFLAGS}


Compiling and linking a Fortran/MPI program
*******************************************

Compile and link example-mpi.F90 -> example-mpi-f

    .. code-block:: bash

        FCFLAGS=`adios2-config --fortran-flags`
        LDFLAGS=`adios2-config --fortran-libs`
        mpif90 -o example-mpi-f ${FCFLAGS} example-mpi.F90 ${LDFLAGS}

Compiling and linking a Fortran serial program
**********************************************

Compile and link example-serial.F90 -> example-serial-f

    .. code-block:: bash

        FCFLAGS=`adios2-config --fortran-flags -s`
        LDFLAGS=`adios2-config --fortran-libs -s`
        gfortran -o example-serial-f ${FCFLAGS} example-serial.F90 ${LDFLAGS}

Running the examples in *source/manual-build*
*********************************************

Each of these examples create an output file `<example>`.bp, which contains a single string variable `Greeting`. `bpls` is a tool from the ADIOS2 installation.

    .. code-block:: bash

        $ mpirun -n 4 example-mpi-f
        Hello World from ADIOS2 Fortran/MPI exam
        Hello World from ADIOS2 Fortran/MPI exam
        Hello World from ADIOS2 Fortran/MPI exam
        Hello World from ADIOS2 Fortran/MPI exam

        $ bpls -la example-mpi-f.bp/
        string   Greeting  scalar = "Hello World from ADIOS2 Fortran/MPI example"

Running other examples
**********************

Other examples in the ADIOS2-Examples repository are more complex than just a single source file. You can still create the compile and link command line yourself but we provide a simple local Makefile for each example. Each Makefile includes the ``make.settings`` file from the root directory of the repository. You need to edit this settings file to set the ADIOS2 installation directory and the names of the serial and MPI compilers. 