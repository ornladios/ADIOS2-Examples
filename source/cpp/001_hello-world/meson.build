
example_dir = 'cpp/001_hello-world'

hello_world_exe = executable('hello-world', 'hello-world.cpp', 
           dependencies : [mpi_dep, adios2_dep], install: true,
           install_dir: example_dir)
test('001_hello-world', hello_world_exe)
                         
hello_world_hl_exe = executable('hello-world_hl', 'hello-world_hl.cpp', 
           dependencies : [mpi_dep, adios2_dep], install: true,
           install_dir: example_dir)
test('001_hello-world_hl', hello_world_hl_exe)
