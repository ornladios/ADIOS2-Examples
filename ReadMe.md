
# ADIOS2-Examples
This repository contains code examples of how to use the Adaptable Input Output system, ADIOS2, bindings. ADIOS2 and ADIOS2-Examples are developed as part of the U.S. Department of Energy Exascale Computing Program.
The ADIOS2 source code is located at 
[https://github.com/ornladios/ADIOS2](https://github.com/ornladios/ADIOS2)


## Directory layout

* scripts:
    
    - developer: setup scripts for developers

* source: location for all examples source code
	
    - cpp: examples for the low-level, high-level ADIOS2 C++ APIs and combined examples with Python
    - c: examples for the C APIs (build on top of the C++ low-level API)
	

## Package Distributions (preferred)

This is the preferred method as it includes dependencies (e.g. adios2, openmpi, matplotlib) required by the source.

1. Conda installation on Linux, Mac and Windows Linux Subsystem from new environment:
   
    ```
    $ conda create --name adios2-examples
    $ conda activate adios2-examples 
    $ conda install adios2-examples-openmpi -c williamfgc -c conda-forge
    ```

Meson and CMake installations from source are provided if none of the methods above are available.


## Installing from source with [Meson](https://mesonbuild.com/)

1. Requirements:

    - meson build >= 0.52.0, from `pip3 install meson` 
    - ninja
    - mono-complete (might be already installed)
    - mpi: openmpi or mpich
    - adios2 mpi version: 
      - macOS: `brew install adios2`
    - cmake >= v3.8 (optional) if adios2 is installed in non-system location (e.g. `/opt`)
    - python: mpi4py, numpy, matplotlib


2. Build, Test, Install:

    From the ADIOS2-Examples directory:
    
    if adios2 is on a standard installation (e.g. system location `/usr`, spack, conda, etc.) 
    
    ```
    $ meson build-meson --prefix=/path/to/install/adios2-examples
    ```
    
    if adios2 is on a non-standard location (e.g. `/opt`)
    
    ```
    $ meson build-meson --prefix=/path/to/install/adios2-examples 
                        -DADIOS2_DIR=/path/to/adios2/lib/cmake/adios2
    ```
    
    ```
    $ cd build-meson
    $ ninja
    $ ninja test
    $ ninja install
    ``` 		

## Installing from source with [CMake](https://cmake.org/)

1. Requirements:

    - mpi: openmpi or mpich
    - adios2 mpi and python version: 
        - macOS: `brew install adios2`
    - cmake >= v3.8
    - python: mpi4py, numpy, matplotlib

2. Build, Test, Install:

    From the ADIOS2-Examples directory:
	
    ```
    $ mkdir build-cmake
    $ cd build-cmake
    ```
    
    if using an adios2 standard installation (e.g. system location /usr, spack, conda, etc.):
    
    ```
    $ cmake -DCMAKE_INSTALL_PREFIX=/path/to/install/adios2-examples ..
    ```
    
    if using an adios2 non-standard location (e.g. /opt):
    
    ```
    $ cmake -DCMAKE_INSTALL_PREFIX=/path/to/install/adios2-examples \
            -DADIOS2_DIR=/path/to/adios2/lib/cmake/adios2 \
            ..
    ```
    
    ```
    $ make -j
    $ ctest
    $ make install
    ```

## Running the Examples

The final installation structure of the adios2-examples package include a bin directory for the executables and a share directory for the config files and scripts to a particular example.
    
adios2-examples installation structure:
   
    - bin/
        a2e_001_hello-world
        a2e_001_hello-world_hl
        ...
    	a2e_003_gray-scott
        a2e_003_pdf_calc
    	
    - share/adios2-examples/
        003_gray-scott
        
Each executable under `bin` starts with the `a2e_XYZ_*` prefix, where a2e is fixed and XYZ is the example number. Whereas, each `share/adios2-examples` directory has a ReadMe.md file with instructions. 

For example, to run `001_hello-world` examples (assuming `adios2-examples/bin` is in the `$PATH`):

    ```
    $ mpirun -n 4 a2e_001_hello-world_cpp
    Hello World from ADIOS2
    Hello World from ADIOS2
    Hello World from ADIOS2
    Hello World from ADIOS2
    ```
    
or for the high-level C++ API:
    
    ```
    $ mpirun -n 4 a2e_001_hello-world_hl_cpp
    Hello World from ADIOS2
    Hello World from ADIOS2
    Hello World from ADIOS2
    Hello World from ADIOS2
    ```   
   
these runs would generate corresponding bp files that can be inspected with the [bpls utility](https://adios2.readthedocs.io/en/latest/ecosystem/utilities.html#bpls-inspecting-data) in ADIOS2.
   
    ```
    $ ls -d *.bp
    hello-world.bp  hello-world_hl.bp
    
    $ bpls hello-world.bp -lav
    File info:
    of variables:  1
    of attributes: 0
    statistics:    Min / Max
    
    string   Greeting  scalar = "Hello World from ADIOS2"
    ```

For a more elaborated use case see example [003_gray-scott](https://github.com/ornladios/ADIOS2-Examples/tree/master/source/cpp/003_gray-scott).

   
## Credits

* William F Godoy godoywf@ornl.gov
* Norbert Podhorszki pnb@ornl.gov
* Keichi Takahashi keichi@is.naist.jp
* Hiroshi Watanabe

