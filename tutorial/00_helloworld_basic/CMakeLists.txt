#------------------------------------------------------------------------------#
# Distributed under the OSI-approved Apache License, Version 2.0.  See
# accompanying file Copyright.txt for details.
#------------------------------------------------------------------------------#
cmake_minimum_required(VERSION 3.12)
project(adios2HelloWorldBasic LANGUAGES C CXX)

add_executable(ADIOS2helloworldBasic helloworld.cxx)
target_link_libraries(ADIOS2helloworldBasic adios2::cxx11)
