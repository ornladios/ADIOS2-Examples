#------------------------------------------------------------------------------#
# Distributed under the OSI-approved Apache License, Version 2.0.  See
# accompanying file Copyright.txt for details.
#------------------------------------------------------------------------------#

add_executable(a2e_002_basics-variables-shapes_cpp variables-shapes.cpp)
target_link_libraries(a2e_002_basics-variables-shapes_cpp adios2::adios2 MPI::MPI_C)
add_test(NAME 002_basics-variables-shapes_cpp 
         COMMAND mpirun -np ${NPROCS} $<TARGET_FILE:a2e_002_basics-variables-shapes_cpp>)
install(TARGETS a2e_002_basics-variables-shapes_cpp 
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

add_executable(a2e_002_basics-variables-shapes_hl_cpp variables-shapes_hl.cpp)
target_link_libraries(a2e_002_basics-variables-shapes_hl_cpp adios2::adios2 MPI::MPI_C)
add_test(NAME 002_basics-variables-shapes_hl_cpp 
         COMMAND mpirun -np ${NPROCS} $<TARGET_FILE:a2e_002_basics-variables-shapes_hl_cpp>)
install(TARGETS a2e_002_basics-variables-shapes_hl_cpp 
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
