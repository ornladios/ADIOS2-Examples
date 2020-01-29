
hello_world_exe = executable('adios2-hello-world-cpp', 'hello-world.cpp', 
                              dependencies : [mpi_dep, adios2_dep], install: true)
# MPI test
test('hello-world.cpp', mpiexec, args:['-np', nprocs, hello_world_exe], 
                        timeout: 10, is_parallel: false)
                         
hello_world_hl_exe = executable('adios2-hello-world-hl-cpp', 'hello-world-hl.cpp', 
                                dependencies : [mpi_dep, adios2_dep], install: true)

# MPI test
test('hello-world-hl.cpp', mpiexec, args:['-np', nprocs, hello_world_hl_exe], 
                           timeout: 10, is_parallel: false)
