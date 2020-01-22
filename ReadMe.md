
# Adaptable Input / Output System version 2, ADIOS2-Examples
This repository contains code examples of how to use the ADIOS I/O system, which is being developed as part of the
U.S. Department of Energy Exascale Computing Program.
The ADIOS2 source code is located at 
[https://github.com/ornladios/ADIOS2](https://github.com/ornladios/ADIOS2)


## Directory layout

* scripts:
    
    - developer: setup scripts for developers

* source: location for all examples source code 
	
	- cpp: examples for the low-level and high-level ADIOS2 C++ APIs
	
		- 001_hello-world:
		
	- c: examples for the C APIs (build on top of the C++ low-level APIs)
	
	
## Getting Started

1. Clone the repository, and cd into it:

    ```bash
    $ git clone https://github.com/ornladios/ADIOS2-examples.git
    ```

    ```bash
    $ cd ADIOS2-Examples
    ```

Meson and CMake build options are provided. In the future, we expect to distribute the adios2-examples as a package in conda, spack, dockerfile, etc.


## Installing with [Meson](https://mesonbuild.com/)

1. Requirements:

     - meson build >= 0.52.0, from `pip3 install meson` 
	- ninja
	- mono-complete (might be already installed)
	- mpi: openmpi or mpich
	- adios2 mpi version: 
		- macOS: `brew install adios2`
	- cmake >= v3.8 (optional) if adios2 is installed in non-system location (e.g. /opt)


2. Build, Test, Install:

    From the ADIOS2-Examples directory:
    
    if adios2 is on a standard installation (e.g. system location /usr, spack, conda, etc.) 
    
    ```
    $ meson build-meson --prefix=/path/to/install/adios2-examples
    ```
    
    if adios2 is on a non-standard location (e.g. /opt)
    
    ```bash
    $ meson build-meson --prefix=/path/to/install/adios2-examples -DADIOS2_DIR=/path/to/adios2/lib/cmake/adios2
    ```
    
    ```bash
    $ cd build-meson
    $ ninja
    $ ninja test
    $ ninja install
    ``` 		

## Installing with [CMake](https://cmake.org/)

1. Requirements:

	- mpi: openmpi or mpich
	- adios2 mpi version: 
		- macOS: `brew install adios2`
	- cmake >= v3.8

2. Build, Test, Install:

    From the ADIOS2-Examples directory:
	
    ```
    $ mkdir build-cmake
    $ cd build-cmake
    ```
    
    if using an adios2 standard installation (e.g. system location /usr, spack, conda, etc.) 
    
    ```
    $ cmake -DCMAKE_INSTALL_PREFIX=/path/to/install/adios2-examples ..
    ```
    
    if using an adios2 non-standard location (e.g. /opt)
    
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

   The final installation structure of the adios2-examples package follows the source directory
   
   adios2-install:
   
    - bin/
        - a2e_001_hello-world
        - a2e_001_hello-world_hl
    	   - ...
    	
    - share/
        - ReadMe_001_hello-world.md
        
   Each executables starts with the `a2e_XYZ_*` prefix, where XYZ is the example number, 
   and a ReadMe.md file with instructions on how to run each example.
   
   For example, to run 001_hello-world examples (assuming `adios2-examples/bin` is in the `$PATH`):
   
    ```
    $ mpirun -n 4 a2e_001_hello-world
    Hello World from ADIOS2
    Hello World from ADIOS2
    Hello World from ADIOS2
    Hello World from ADIOS2
    ```
    
   or for the high-level C++ API
    
    ```
    $ mpirun -n 4 a2e_001_hello-world_hl
    Hello World from ADIOS2
    Hello World from ADIOS2
    Hello World from ADIOS2
    Hello World from ADIOS2
    ```   
   
   these would generate corresponding bp files that can be inspected with the [bpls utility](https://adios2.readthedocs.io/en/latest/ecosystem/utilities.html#bpls-inspecting-data) in ADIOS2.
   
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

## Credits

* William F Godoy godoywf@ornl.gov
* Norbert Podhorszki pnb@ornl.gov
* Keichi Takahashi keichi@is.naist.jp
* Hiroshi Watanabe
