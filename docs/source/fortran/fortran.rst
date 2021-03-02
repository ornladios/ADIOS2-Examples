.. _section_fortran:

Fortran examples
################

The ADIOS2 Fortran bindings are documented in `<https://adios2.readthedocs.io/en/latest/api_full/api_full.html#fortran-bindings>`_.

When writing Fortran code, it comes handy to look at the `source code of the Fortran bindings <https://github.com/ornladios/ADIOS2/blob/master/bindings/Fortran/modules/>`_ directly to find the possible signatures of each function, and especially at the `ADIOS2 constants <https://github.com/ornladios/ADIOS2/blob/master/bindings/Fortran/modules/adios2_parameters_mod.f90>`_.

Including ADIOS2 in a Fortran application
*****************************************

ADIOS2 is using a Fortran 90 interface, so it cannot be directly used in an F77 code base. Files that include adios calls, should be named \*.F90 (capital F) so that macros are pre-processed by the Fortran compiler. 

Since ADIOS2 is object-oriented and is implemented in C++, there is a need to use global variables in Fortran to initialize an ``adios`` object and to keep it alive ("in scope") as long as it is needed. Usually, the adios object is created after MPI is initialized and destroyed before MPI is finalized. An ``io`` object is used to define all variables, attributes and runtime parameters for an input or output. Finally, an ``engine`` object needed to call the actual operations on the input or output (open, close and read/write-related calls).

The easiest way to manage the objects is to put them into a new module for ADIOS I/O. The example is in ``source/fortran/adios-module/adiosio.F90``

Assuming you have the MPI communicator in another module name *mpivars*, and the communicator is named *app_comm*:

.. literalinclude:: ../../../source/fortran/adios-module/adiosio.F90
   :language: fortran

.. note::

    The example above adds an IO and an Engine object to the module, which is not required if you write an output or read an input in a single subroutine and do so only once. However, if you want to refer to them in multiple subroutines, or you want to read/write multiple steps, you need to keep these objects (technically, object references) alive to avoid premature destruction of the C++ objects behind.

.. note::

    The example above also closes the engine object in the finalization. This is an example to follow if you want to open an output somewhere else in the code, and output new data (new steps) regularly until the end. This usage is not encouraged here. It is cleaner if you manage the (single) open and (single) close of your outputs and the (multiple) output steps yourself. However, in existing large applications with many optional modules it may be difficult to find the exact spot where the output stream actually ends. This subroutine is the last point where the output must be closed. 


In the main program, include these snippets of code:

.. code-block:: fortran 

    program adios2_module_example
        use mpivars
    #ifdef ADIOS2
        use adiosio
    #endif
        implicit none

    ...

        ! After call MPI_Init()
    #ifdef ADIOS2
        call init_adiosio()
    #endif

    ...

        ! Before call MPI_Finalize()
    #ifdef ADIOS2
        call finalize_adiosio()
    #endif

.. note::

    We are using the *ADIOS2* macro everywhere to allow for building the application with or without ADIOS2. If you make ADIOS2 a required dependency, there is no need for this macro.

