#------------------------------------------------------------------------------#
# Distributed under the OSI-approved Apache License, Version 2.0.  See
# accompanying file Copyright.txt for details.
#------------------------------------------------------------------------------#

# 3.12 for object library support with Fortran modules
cmake_minimum_required(VERSION 3.12)

# Fail immediately if not using an out-of-source build
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_CURRENT_BINARY_DIR)
  message(FATAL_ERROR
    "In-source builds are not supported.  Please create a build directory "
    "separate from the source directory")
endif()

project(ADIOS2Examples LANGUAGES C CXX VERSION 2.7.0)

include(CheckLanguage)
check_language(Fortran)
if(CMAKE_Fortran_COMPILER)
  enable_language(Fortran)
endif()

# Use <PackageName>_ROOT variables if available
if(POLICY CMP0074)
  cmake_policy(SET CMP0074 NEW)
endif()

#------------------------------------------------------------------------------#
# Some boilerplate to setup nice output directories
#------------------------------------------------------------------------------#
include(GNUInstallDirs)
set(CMAKE_INSTALL_CMAKEDIR ${CMAKE_INSTALL_LIBDIR}/cmake/adios2
  CACHE STRING "Installation CMake subdirectory")
mark_as_advanced(CMAKE_INSTALL_CMAKEDIR)

list(INSERT CMAKE_MODULE_PATH 0 "${PROJECT_SOURCE_DIR}/cmake")
if(NOT CMAKE_ARCHIVE_OUTPUT_DIRECTORY)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY
    ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
endif()
if(NOT CMAKE_LIBRARY_OUTPUT_DIRECTORY)
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY
    ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
endif()
if(NOT CMAKE_RUNTIME_OUTPUT_DIRECTORY)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
    ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})
endif()

#------------------------------------------------------------------------------#
# Common dependencies
#------------------------------------------------------------------------------#
set(_components C CXX)
if(CMAKE_Fortran_COMPILER_LOADED)
  list(APPEND _components Fortran)
endif()

find_package(MPI COMPONENTS ${_components})
if(MPI_FOUND)
  # Workaround for various MPI implementations forcing the link of C++ bindings
  add_definitions(-DOMPI_SKIP_MPICXX -DMPICH_SKIP_MPICXX)

  list(APPEND _components MPI)
endif()

find_package(ADIOS2 2.7.1 REQUIRED COMPONENTS ${_components})

find_package(Threads)

#------------------------------------------------------------------------------#
# Top level build options
#------------------------------------------------------------------------------#

# Default to a Release build if not specified
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build." FORCE)
endif()

set(CMAKE_CXX_STANDARD 11 CACHE STRING "C++ Standard level to use (11)")
set_property(CACHE CMAKE_CXX_STANDARD PROPERTY STRINGS "11;17")
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Setup testing to run the examples
include(CTest)
if(BUILD_TESTING)
  enable_testing()
endif()

# This is a helper function to use mpiexec to run tests when appropriate
function(add_test_helper tgt)
  if(MPI_FOUND)
    add_test(NAME ${tgt}
      COMMAND ${MPIEXEC_EXECUTABLE} ${MPIEXEC_NUMPROC_FLAG} ${MPIEXEC_MAX_NUMPROCS} ${MPIEXEC_PREFLAGS} $<TARGET_FILE:${tgt}> ${ARGN} ${MPIEXEC_POSTFLAGS}
    )
  else()
    add_test(NAME ${tgt}
      COMMAND $<TARGET_FILE:${tgt}> ${ARGN}
    )
  endif()
endfunction()

# Add the example source tree
add_subdirectory(source)
