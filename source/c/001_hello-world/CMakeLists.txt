
add_executable(a2e_001_hello-world_c hello-world.c)
target_link_libraries(a2e_001_hello-world_c adios2::adios2 MPI::MPI_C)
add_test(NAME 001_hello-world_c COMMAND $<TARGET_FILE:a2e_001_hello-world_c>)
install(TARGETS a2e_001_hello-world_c)
