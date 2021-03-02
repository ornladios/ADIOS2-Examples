#------------------------------------------------------------------------------#
# Distributed under the OSI-approved Apache License, Version 2.0.  See
# accompanying file Copyright.txt for details.
#------------------------------------------------------------------------------#

if(MPI_FOUND)
  set(common_deps adios2::cxx11_mpi MPI::MPI_C)
else()
  set(common_deps adios2::cxx11)
endif()

add_subdirectory(basics)

if(MPI_FOUND)
  add_subdirectory(gray-scott)
endif()

add_subdirectory(hello-world)
add_subdirectory(korteweg-de-vries)

if(CMAKE_CXX_STANDARD GREATER_EQUAL 17)
  add_subdirectory(lorenz_ode)
endif()
