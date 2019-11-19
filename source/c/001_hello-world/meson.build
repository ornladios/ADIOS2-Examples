
hello_world_exe = executable('a2e_001_hello-world_c', 'hello-world.c', 
                              dependencies : [mpi_dep, adios2_dep], install: true)

# MPI test
test('001_hello-world_c', mpiexec, args:['-np', nprocs, hello_world_exe], timeout: 10, is_parallel: false)
