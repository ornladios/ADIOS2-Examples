#------------------------------------------------------------------------------#
# Distributed under the OSI-approved Apache License, Version 2.0.  See
# accompanying file Copyright.txt for details.
#------------------------------------------------------------------------------#

add_subdirectory(c)
add_subdirectory(cpp)

if(CMAKE_Fortran_COMPILER_LOADED)
#  add_subdirectory(fortran)
endif()
