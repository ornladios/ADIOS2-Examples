#------------------------------------------------------------------------------#
# Distributed under the OSI-approved Apache License, Version 2.0.  See
# accompanying file Copyright.txt for details.
#------------------------------------------------------------------------------#

add_executable(adios2-variables-shapes-cpp variables-shapes.cpp)
target_link_libraries(adios2-variables-shapes-cpp adios2::adios2 MPI::MPI_C)
add_test(NAME variables-shapes-cpp 
         COMMAND mpirun -np ${NPROCS} $<TARGET_FILE:adios2-variables-shapes-cpp>)
install(TARGETS adios2-variables-shapes-cpp 
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

add_executable(adios2-variables-shapes-hl-cpp variables-shapes-hl.cpp)
target_link_libraries(adios2-variables-shapes-hl-cpp adios2::adios2 MPI::MPI_C)
add_test(NAME variables-shapes-hl-cpp 
         COMMAND mpirun -np ${NPROCS} $<TARGET_FILE:adios2-variables-shapes-hl-cpp>)
install(TARGETS adios2-variables-shapes-hl-cpp 
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
       
if(Threads_FOUND)
    add_executable(adios2-thread-write-cpp thread-write.cpp)
    target_link_libraries(adios2-thread-write-cpp adios2::adios2 MPI::MPI_C Threads::Threads)
    add_test(NAME thread-write-cpp 
         COMMAND mpirun -np ${NPROCS} $<TARGET_FILE:adios2-thread-write-cpp>)
    install(TARGETS adios2-thread-write-cpp 
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
endif()
