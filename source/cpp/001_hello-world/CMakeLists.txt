
add_executable(a2e_001_hello-world hello-world.cpp)
target_link_libraries(a2e_001_hello-world adios2::adios2 MPI::MPI_C)
add_test(NAME 001_hello-world COMMAND $<TARGET_FILE:a2e_001_hello-world>)
install(TARGETS a2e_001_hello-world)


add_executable(a2e_001_hello-world_hl hello-world_hl.cpp)
target_link_libraries(a2e_001_hello-world_hl adios2::adios2 MPI::MPI_C)
add_test(NAME 001_hello-world_hl COMMAND $<TARGET_FILE:a2e_001_hello-world_hl>)
install(TARGETS a2e_001_hello-world_hl)

