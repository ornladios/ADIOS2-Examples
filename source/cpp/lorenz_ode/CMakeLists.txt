#------------------------------------------------------------------------------#
# Distributed under the OSI-approved Apache License, Version 2.0.  See
# accompanying file Copyright.txt for details.
#------------------------------------------------------------------------------#

add_executable(lorenz_writer lorenz_writer.cpp)
target_link_libraries(lorenz_writer adios2::adios2 MPI::MPI_C)

add_executable(lorenz_reader lorenz_reader.cpp)
target_link_libraries(lorenz_reader adios2::adios2 MPI::MPI_C)
