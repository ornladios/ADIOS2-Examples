#------------------------------------------------------------------------------#
# Distributed under the OSI-approved Apache License, Version 2.0.  See
# accompanying file Copyright.txt for details.
#------------------------------------------------------------------------------#

add_executable(adios2-write-read-kokkos write-read-kokkos.cpp)
target_link_libraries(adios2-write-read-kokkos ${common_deps} Kokkos::kokkos)
add_test_helper(adios2-write-read-kokkos)
install(TARGETS adios2-write-read-kokkos
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
