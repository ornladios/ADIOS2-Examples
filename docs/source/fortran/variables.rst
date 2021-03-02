.. _section_fortran_variables:

Defining, writing and reading variables
#######################################

Global Array
*****************************************

Global array of fixed shape
---------------------------

This is how we define a 1D array of type *real4* and of size *nproc* x *NX* where every process has an array of size *NX*, there are *nproc* processes, and their *rank* runs from 0..*nproc*-1:

.. code-block:: fortran 
   :emphasize-lines: 14-17

    use adios2
    implicit none
    type(adios2_io) :: io
    type(adios2_variable) :: var_g
    ...
    integer*4 :: ndim
    integer*8, dimension(1) :: fixed_shape, fixed_start, fixed_count

    ndim = 1
    fixed_count = NX
    fixed_shape = nproc * NX
    fixed_start = rank * NX
    
    call adios2_define_variable(var_g, io, "GlobalArray", &
                                adios2_type_real4, ndim, &
                                fixed_shape, fixed_start, fixed_count, &
                                adios2_constant_dims, ierr)
             

.. note::

    The flag ``adios2_constant_dims`` indicates that this definition is fixed, i.e. the block selection and the global array shape cannot be changed. Use ``adios2_variable_dims`` if you intend to change any of these later. 

The example in  ``source/fortran/shapes/global-array-fixed-write.F90`` and ``global-array-fixed-read.F90`` is similar but each process holds a (random) size of array between 2 and 5 and the global shape has to be calculated that involves an MPI Allgather operation. 

.. note::

    For an N-dimensional arrays, the function is the same, just the value of *ndim* is N, and the shape, start and count arrays must have N elements. 



Global array that changes
-------------------------

If you don't know the size of the local arrays at the point of the definition, you can set this information later (before calling Put). 

.. code-block:: fortran 

        ! Change the shape and decomposition information
        call adios2_set_shape(var_g, 1, changing_shape, ierr)
        call adios2_set_selection(var_g, 1, changing_start, changing_count, ierr);

.. note::

    The global shape of the array is a single global piece of information about the array (in one output step), which can only change between steps. Technically, one can call adios2_set_shape multiple times but only the last call before the last adios2_put() call will count. The final shape must be set to the same shape on every process. 

The example in  ``source/fortran/shapes/global-array-changing-shape-write.F90`` shows how to write an array whose global size changes over time. 

Multiblock 
----------

By multiblock we mean that one process contributes more than one block to the global array. Since only one definition is allowed for a variable, one needs to call ``adios2_set_selection`` and then ``adios2_put()`` for each block once. 