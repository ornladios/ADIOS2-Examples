#------------------------------------------------------------------------------#
# Distributed under the OSI-approved Apache License, Version 2.0.  See
# accompanying file Copyright.txt for details.
#------------------------------------------------------------------------------#

cmake_minimum_required(VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)

# Fail immediately if not using an out-of-source build
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_CURRENT_BINARY_DIR)
  message(FATAL_ERROR
    "In-source builds are not supported.  Please create a build directory "
    "separate from the source directory")
endif()

project(ADIOS2Examples)
# to enable -DADIOS2_ROOT in modern cmake
if(POLICY CMP0074)
  cmake_policy(SET CMP0074 NEW)
endif()

# Dependencies
find_package(ADIOS2 REQUIRED)

# place executables
# define CMAKE_INSTALL_BINDIR 
include(GNUInstallDirs)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# set build type
set(CMAKE_BUILD_TYPE Release)

enable_testing()
set(NPROCS 2)

add_subdirectory(source)
