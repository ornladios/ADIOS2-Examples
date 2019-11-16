#!/bin/bash --login

sudo apt-get update -y
sudo apt-get install build-essential sudo gfortran \
                    openmpi-bin libopenmpi-dev libzmq3-dev \
                    cmake \
                    git vim \
                    -y

cd ~
mkdir -p Software
cd Software

git clone https://github.com/ornladios/ADIOS2.git --single-branch --branch v2.5.0 --depth 1
mkdir -p ADIOS2-build
cd ADIOS2-build
cmake -DCMAKE_INSTALL_PREFIX=/opt/adios2 \
          -DCMAKE_BUILD_TYPE=Release \
          -DADIOS2_BUILD_TESTING=OFF \
          -DADIOS2_BUILD_EXAMPLES=OFF \
          ../ADIOS2
make -j
sudo make install

./bpls --help
