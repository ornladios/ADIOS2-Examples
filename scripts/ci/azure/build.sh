#!/bin/bash --login


# Check ADIOS2 is responsive
bpls --help

export OMPI_MCA_rmaps_base_oversubscribe=1

# Get locations
export SOURCE_DIR="${BUILD_SOURCESDIRECTORY}"
export BIN_DIR="${BUILD_BINARIESDIRECTORY}/${joblabel}"

# CMAKE test
cd $BIN_DIR
mkdir build.cmake
cd build.cmake
cmake -DADIOS2_DIR=/opt/adios2/lib/cmake/adios2 $SOURCE_DIR
make -j
ctest

# MESON test
cd $BIN_DIR
mkdir build.meson
cd build.meson
meson $SOURCE_DIR -DADIOS2_DIR=/opt/adios2/lib/cmake/adios2
ninja
ninja test
