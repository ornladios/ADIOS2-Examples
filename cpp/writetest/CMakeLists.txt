#------------------------------------------------------------------------------#
cmake_minimum_required(VERSION 3.6)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

project(WriteTest C CXX)

find_package(MPI REQUIRED)
find_package(ADIOS2 REQUIRED)
find_package(ADIOS REQUIRED)

# Workaround for various MPI implementations forcing the link of C++ bindings
add_definitions(-DOMPI_SKIP_MPICXX -DMPICH_SKIP_MPICXX)

include_directories(${ADIOS_DIR}/include)

add_executable(writetest writetest.cpp)
target_link_libraries(writetest adios2::adios2 ${ADIOS_LIBRARIES} MPI::MPI_C)
