#------------------------------------------------------------------------------#
# Distributed under the OSI-approved Apache License, Version 2.0.  See
# accompanying file Copyright.txt for details.
#------------------------------------------------------------------------------#

set(common_deps adios2::cxx11)

find_package(CUDAToolkit QUIET)
if(CUDAToolkit_FOUND)
    add_subdirectory(basics-cuda)
endif()

find_package(hip QUIET)
if(hip_FOUND)
    add_subdirectory(basics-hip)
endif()

find_package(Kokkos QUIET)
if(Kokkos_FOUND)
    add_subdirectory(basics-kokkos)
endif()
