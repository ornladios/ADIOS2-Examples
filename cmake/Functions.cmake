#------------------------------------------------------------------------------#
# Distributed under the OSI-approved Apache License, Version 2.0.  See
# accompanying file Copyright.txt for details.
#------------------------------------------------------------------------------#


function(add_mpi_test DIR_NAME BASE LANG)
  add_executable(a2e_${DIR_NAME}-${BASE}_${LANG} ${BASE}.${LANG})
  target_link_libraries(a2e_002_basics-variables_cpp adios2::adios2 MPI::MPI_C)
  add_test(NAME 002_basics-variables_cpp COMMAND mpirun -np ${NPROCS} $<TARGET_FILE:a2e_002_basics-variables_cpp>)
  install(TARGETS a2e_002_basics-variables_cpp RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
end function()

