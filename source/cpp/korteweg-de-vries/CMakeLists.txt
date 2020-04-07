#------------------------------------------------------------------------------#
# Distributed under the OSI-approved Apache License, Version 2.0.  See
# accompanying file Copyright.txt for details.
#------------------------------------------------------------------------------#

add_executable(KdV KdV.cpp)
target_link_libraries(KdV adios2::adios2 MPI::MPI_C)
