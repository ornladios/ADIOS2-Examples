#------------------------------------------------------------------------------#
# Distributed under the OSI-approved Apache License, Version 2.0.  See
# accompanying file Copyright.txt for details.
#------------------------------------------------------------------------------#

add_executable(adios2-gray-scott-kokkos
  main.cpp
  gray-scott.cpp
  settings.cpp
  writer.cpp
  restart.cpp
)
target_link_libraries(adios2-gray-scott-kokkos adios2::adios2 MPI::MPI_C Kokkos::kokkos)
install(TARGETS adios2-gray-scott-kokkos
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
install(FILES "adios2.xml" "settings-files.json"
        DESTINATION ${CMAKE_INSTALL_PREFIX}/share/adios2-examples/gray-scott-kokkos)
