#------------------------------------------------------------------------------#
# Distributed under the OSI-approved Apache License, Version 2.0.  See
# accompanying file Copyright.txt for details.
#------------------------------------------------------------------------------#

names = ['variables-shapes', 'variables-shapes-hl']

# meson is not Turing-complete, so user-defined functions are not possible
# still this is a great workaround
foreach name : names
  exe = executable('adios2-'+name+'-cpp', name+'.cpp', 
                   dependencies : [mpi_dep, adios2_dep], install: true)
  test(name+'-cpp', mpiexec, args:['-np', nprocs, exe], 
                                 timeout: 10, is_parallel: false)
endforeach
