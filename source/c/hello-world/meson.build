#------------------------------------------------------------------------------#
# Distributed under the OSI-approved Apache License, Version 2.0.  See
# accompanying file Copyright.txt for details.
#------------------------------------------------------------------------------#

hello_world_exe = executable('adios2-hello-world-c', 'hello-world.c', 
                              dependencies : [mpi_dep, adios2_dep], install: true)

# MPI test
test('hello-world-c', mpiexec, args:['-np', nprocs, hello_world_exe], timeout: 10, 
                      is_parallel: false)
