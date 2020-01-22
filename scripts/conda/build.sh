#!/bin/bash

# builds a special adios2 version for Jupyter Notebooks cling using openmpi

set -e
set -x

mkdir build-dir
cd build-dir

cmake \
    -DCMAKE_INSTALL_PREFIX=$PREFIX \
    -DCMAKE_POSITION_INDEPENDENT_CODE=ON \
    -DCMAKE_BUILD_TYPE=Release \
    ..
    
make -j 8
make install

