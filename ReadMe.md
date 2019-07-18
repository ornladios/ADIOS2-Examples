
# Adaptable Input / Output System (ADIOS) Examples
This repository contains code examples of how to use the ADIOS I/O system, which is being developed as part of the
U.S. Department of Energy Exascale Computing Program.
The ADIOS source code is located at 
[https://github.com/ornladios/ADIOS2](https://github.com/ornladios/ADIOS2)


## Directory layout

* cpp     - C++ examples (the native interface of ADIOS v2)
* fortran - Fortran 90 examples
* numpy   - Python/numpy examples

## Getting Started

To build ADIOS2 examples

1. Clone the repository, and cd into it:

```bash
$ git clone https://github.com/ornladios/ADIOS2-examples.git
```

```bash
$ cd ADIOS2-example
```

2. Enter the directory for the language you are interested in, e.g.

```bash
$ cd cpp
```

3. Edit the make.settings file for your system.

4. Enter the directory for your chosen example, e.g.

```bash
$ cd heatTransfer
```

5. Build the example

```bash
$ make
```

6. Run the example as described in its ReadMe.md

