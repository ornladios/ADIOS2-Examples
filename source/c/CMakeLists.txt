#------------------------------------------------------------------------------#
# Distributed under the OSI-approved Apache License, Version 2.0.  See
# accompanying file Copyright.txt for details.
#------------------------------------------------------------------------------#

if(MPI_FOUND)
  set(common_deps adios2::c_mpi MPI::MPI_C)
else()
  set(common_deps adios2::c)
endif()

add_subdirectory(hello-world)
add_subdirectory(shapes)
