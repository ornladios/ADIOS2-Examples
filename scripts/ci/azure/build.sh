#!/bin/bash --login

# Exit at error
set -e
# Show commands
set -x

export OMPI_MCA_rmaps_base_oversubscribe=1

# Get locations
export SOURCE_DIR="${BUILD_SOURCESDIRECTORY}"
export BIN_DIR="${BUILD_BINARIESDIRECTORY}/${joblabel}"

# CMAKE test
cd $BIN_DIR
mkdir build.cmake
cd build.cmake
cmake -DADIOS2_DIR=/opt/adios2/lib/cmake/adios2 \
      -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_INSTALL_PREFIX=$PWD/install \
      $SOURCE_DIR
make -j
ctest
make install

# MESON test
cd $BIN_DIR
mkdir build.meson
cd build.meson
meson $SOURCE_DIR \
      -DADIOS2_DIR=/opt/adios2/lib/cmake/adios2 \
      --prefix=$PWD/install
ninja
ninja test
ninja install
