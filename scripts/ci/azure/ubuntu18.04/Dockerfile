FROM ubuntu:18.04
MAINTAINER William F Godoy godoywf@ornl.gov
RUN apt-get update -y &&\
    DEBIAN_FRONTEND=noninteractive \
    apt-get install build-essential openmpi-bin libopenmpi-dev libzmq3-dev \
                    python3-dev python3-mpi4py python3-numpy python3-pip \
                    libblosc-dev libbz2-dev libpng-dev \
                    libhdf5-openmpi-dev \
                    cmake git vim ninja-build mono-complete \
                    -y

RUN pip3 install meson

RUN cd /tmp &&\
    mkdir -p Software

RUN cd /tmp/Software &&\
    git clone https://github.com/LLNL/zfp.git --single-branch --branch 0.5.5 --depth 1 &&\
    mkdir -p zfp-build &&\
    cd zfp-build &&\
    cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/opt/zfp -DBUILD_EXAMPLES=OFF ../zfp &&\
    make -j &&\
    make install
    
RUN cd /tmp/Software &&\
    git clone https://github.com/disheng222/SZ.git --single-branch --branch v2.1.5.0 --depth 1 &&\
    cd SZ &&\
    ./configure --prefix=/opt/sz &&\
    make -j &&\
    make install

RUN cd /tmp/Software &&\
    git clone https://github.com/ornladios/ADIOS2.git --single-branch --branch v2.5.0 --depth 1 &&\
    mkdir -p ADIOS2-build &&\
    cd ADIOS2-build &&\
    cmake -DCMAKE_INSTALL_PREFIX=/opt/adios2 \
          -DCMAKE_BUILD_TYPE=Release \ 
          -DZFP_ROOT=/opt/zfp \
          -DSZ_ROOT=/opt/sz \
          -DADIOS2_BUILD_TESTING=OFF \
          -DADIOS2_BUILD_EXAMPLES=OFF \
          ../ADIOS2 &&\
    make -j &&\
    make install
    
RUN cd /tmp &&\
    rm -fr Software

ENV PYTHONPATH=/usr/local/lib/python3.6/site-packages/:/opt/adios2/lib/python3.6/site-packages:$PYTHONPATH
ENV PATH=/opt/adios2/bin:$PATH
ENV LD_LIBRARY_PATH=/usr/local/lib:/opt/zfp/lib:/opt/sz/lib:/opt/adios2/lib:$LD_LIBRARY_PATH
