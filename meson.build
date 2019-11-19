#------------------------------------------------------------------------------#
# Distributed under the OSI-approved Apache License, Version 2.0.  See
# accompanying file Copyright.txt for details.
#------------------------------------------------------------------------------#

project('ADIOS2Examples', 
         ['cpp', 'c'],
         license: 'Apache 2',
         version: '2.5.0',
         meson_version: '>=0.52.0',
         default_options : ['c_std=c99', 'cpp_std=c++17', 'buildtype=release',
                            'layout=flat']
         )

adios2_dep = dependency('adios2', required: true, version: '>=2.5.0',
                        cmake_module_path: [get_option('ADIOS2_DIR')],
                        not_found_message: 'adios2 not found, check -DADIOS2_DIR')

mpi_dep = dependency('mpi', language: 'cpp', required: false)

# Needed for MPI tests
mpiexec = find_program('mpiexec')
nprocs = '2'

subdir('source')
