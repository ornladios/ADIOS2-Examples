#------------------------------------------------------------------------------#
# Distributed under the OSI-approved Apache License, Version 2.0.  See
# accompanying file Copyright.txt for details.
#------------------------------------------------------------------------------#

add_executable(adios2-variables-shapes-cpp variables-shapes.cpp)
target_link_libraries(adios2-variables-shapes-cpp adios2::cxx11_mpi)
add_test(NAME variables-shapes-cpp 
         COMMAND mpirun -np ${NPROCS} $<TARGET_FILE:adios2-variables-shapes-cpp>)
install(TARGETS adios2-variables-shapes-cpp 
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

add_executable(adios2-variables-shapes-hl-cpp variables-shapes-hl.cpp)
target_link_libraries(adios2-variables-shapes-hl-cpp adios2::cxx11_mpi)
add_test(NAME variables-shapes-hl-cpp 
         COMMAND mpirun -np ${NPROCS} $<TARGET_FILE:adios2-variables-shapes-hl-cpp>)
install(TARGETS adios2-variables-shapes-hl-cpp 
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
