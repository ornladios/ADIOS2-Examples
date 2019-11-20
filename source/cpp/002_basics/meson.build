#------------------------------------------------------------------------------#
# Distributed under the OSI-approved Apache License, Version 2.0.  See
# accompanying file Copyright.txt for details.
#------------------------------------------------------------------------------#

names = ['variables-shapes', 'variables-shapes_hl']

# meson is not Turing-complete, so user-defined functions are not possible
# still this is a great workaround
foreach name : names
  exe = executable('a2e_002_basics-'+name+'_cpp', name+'.cpp', 
                   dependencies : [mpi_dep, adios2_dep], install: true)
  test('002_basics'+name+'_cpp', mpiexec, args:['-np', nprocs, exe], 
                                 timeout: 10, is_parallel: false)
endforeach
