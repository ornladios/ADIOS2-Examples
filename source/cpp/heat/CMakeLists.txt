#------------------------------------------------------------------------------#
# Distributed under the OSI-approved Apache License, Version 2.0.  See
# accompanying file Copyright.txt for details.
#------------------------------------------------------------------------------#

cmake_minimum_required(VERSION 3.6)

# Fail immediately if not using an out-of-source build
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_CURRENT_BINARY_DIR)
  message(FATAL_ERROR
    "In-source builds are not supported.  Please create a build directory "
    "separate from the source directory")
endif()

project(ADIOS2HeatTransfer)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
else()
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/cpp/heat)
endif()
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/runtimecfg
  DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/adios2.xml
  DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)

find_package(ADIOS2 REQUIRED)
find_package(MPI REQUIRED)

# Workaround for various MPI implementations forcing the link of C++ bindings
add_definitions(-DOMPI_SKIP_MPICXX -DMPICH_SKIP_MPICXX)

add_subdirectory(simulation)
add_subdirectory(analysis)
add_subdirectory(visualization)
