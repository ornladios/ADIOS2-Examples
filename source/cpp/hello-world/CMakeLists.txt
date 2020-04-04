
add_executable(adios2-hello-world-cpp hello-world.cpp)
target_link_libraries(adios2-hello-world-cpp adios2::cxx11_mpi)
add_test(NAME hello-world.cpp COMMAND mpirun -np ${NPROCS} $<TARGET_FILE:adios2-hello-world-cpp>)
install(TARGETS adios2-hello-world-cpp RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

add_executable(adios2-hello-world-hl-cpp hello-world-hl.cpp)
target_link_libraries(adios2-hello-world-hl-cpp adios2::cxx11_mpi)
add_test(NAME hello-world-hl.cpp COMMAND mpirun -np ${NPROCS} $<TARGET_FILE:adios2-hello-world-hl-cpp>)
install(TARGETS adios2-hello-world-hl-cpp RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

