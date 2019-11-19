
add_executable(a2e_001_hello-world_cpp hello-world.cpp)
target_link_libraries(a2e_001_hello-world_cpp adios2::adios2 MPI::MPI_C)
add_test(NAME 001_hello-world_cpp COMMAND mpirun -np ${NPROCS} $<TARGET_FILE:a2e_001_hello-world_cpp>)
install(TARGETS a2e_001_hello-world_cpp RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

add_executable(a2e_001_hello-world_hl_cpp hello-world_hl.cpp)
target_link_libraries(a2e_001_hello-world_hl_cpp adios2::adios2 MPI::MPI_C)
add_test(NAME 001_hello-world_hl_cpp COMMAND mpirun -np ${NPROCS} $<TARGET_FILE:a2e_001_hello-world_hl_cpp>)
install(TARGETS a2e_001_hello-world_hl_cpp RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

