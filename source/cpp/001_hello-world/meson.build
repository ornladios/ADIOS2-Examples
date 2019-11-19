
hello_world_exe = executable('a2e_001_hello-world_cpp', 'hello-world.cpp', 
                              dependencies : [mpi_dep, adios2_dep], install: true)
# MPI test
test('001_hello-world', mpiexec, args:['-np', nprocs, hello_world_exe], timeout: 10, is_parallel: false)
                         
hello_world_hl_exe = executable('a2e_001_hello-world_hl_cpp', 'hello-world_hl.cpp', 
                                dependencies : [mpi_dep, adios2_dep], install: true)

# MPI test
test('001_hello-world_hl', mpiexec, args:['-np', nprocs, hello_world_hl_exe], timeout: 10, is_parallel: false)
