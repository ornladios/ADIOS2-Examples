#------------------------------------------------------------------------------#
# Distributed under the OSI-approved Apache License, Version 2.0.  See
# accompanying file Copyright.txt for details.
#------------------------------------------------------------------------------#

if(MPI_FOUND)
  add_subdirectory(adios-module)
  add_subdirectory(shapes)
endif()
