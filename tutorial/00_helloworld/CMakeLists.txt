#------------------------------------------------------------------------------#
# Distributed under the OSI-approved Apache License, Version 2.0.  See
# accompanying file Copyright.txt for details.
#------------------------------------------------------------------------------#
cmake_minimum_required(VERSION 3.12)
project(adios2HelloWorld LANGUAGES C CXX)

add_executable(ADIOS2helloworld helloworld.cxx)
target_link_libraries(ADIOS2helloworld adios2::cxx11)
