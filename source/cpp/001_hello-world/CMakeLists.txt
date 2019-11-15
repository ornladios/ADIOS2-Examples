
add_executable(a2e_001_hello-world_cpp hello-world.cpp)
target_link_libraries(a2e_001_hello-world_cpp adios2::adios2 MPI::MPI_C)
add_test(NAME 001_hello-world_cpp COMMAND $<TARGET_FILE:a2e_001_hello-world>)
install(TARGETS a2e_001_hello-world_cpp)

add_executable(a2e_001_hello-world_hl_cpp hello-world_hl.cpp)
target_link_libraries(a2e_001_hello-world_hl_cpp adios2::adios2 MPI::MPI_C)
add_test(NAME 001_hello-world_hl_cpp COMMAND $<TARGET_FILE:a2e_001_hello-world_hl>)
install(TARGETS a2e_001_hello-world_hl_cpp)
