
add_executable(hello-world hello-world.cpp)
target_link_libraries(hello-world adios2::adios2 MPI::MPI_C)
add_test(NAME 001_hello-world COMMAND $<TARGET_FILE:hello-world>)
install(TARGETS hello-world RUNTIME DESTINATION cpp/001_hello-world)


add_executable(hello-world_hl hello-world_hl.cpp)
target_link_libraries(hello-world_hl adios2::adios2 MPI::MPI_C)
add_test(NAME 001_hello-world_hl COMMAND $<TARGET_FILE:hello-world_hl>)
install(TARGETS hello-world_hl RUNTIME DESTINATION cpp/001_hello-world)

