# ADIOS2-Examples gray-scott

This is a 3D 7-point stencil code to simulate the following [Gray-Scott
reaction diffusion model](https://doi.org/10.1126/science.261.5118.189):

```
u_t = Du * (u_xx + u_yy + u_zz) - u * v^2 + F * (1 - u)
v_t = Dv * (v_xx + v_yy + v_zz) + u * v^2 - (F + k) * v
```

## How to run

Make sure MPI and ADIOS2 are installed and that the `PYTHONPATH` includes the ADIOS2 package.
Make sure the adios2-examples/bin installation directory is in the `PATH` (conda and spack installations should take care of this aspect).

From a scratch directory copy the config files from your installation of adios2-examples:

```
$ cp -r <adios2-examples-install-prefix>/share/adios2-examples/gray-scott .
$ cd gray-scott
$ mpirun -n 4 adios2-gray-scott settings-files.json
========================================
grid:             64x64x64
steps:            1000
plotgap:          10
F:                0.01
k:                0.05
dt:               2
Du:               0.2
Dv:               0.1
noise:            1e-07
output:           gs.bp
adios_config:     adios2.xml
process layout:   2x2x1
local grid size:  32x32x64
========================================
Simulation at step 10 writing output step     1
Simulation at step 20 writing output step     2
Simulation at step 30 writing output step     3
Simulation at step 40 writing output step     4
...


$ bpls -l gs.bp
  double   U     100*{64, 64, 64} = 0.0907758 / 1
  double   V     100*{64, 64, 64} = 0 / 0.674811
  int32_t  step  100*scalar = 10 / 1000


$ python3 gsplot.py -i gs.bp

```

## Analysis example how to run

```
$ mpirun -n 4 adios2-gray-scott settings-files.json
$ mpirun -n 2 adios2-pdf-calc gs.bp pdf.bp 100
$ bpls -l pdf.bp
  double   U/bins  100*{100} = 0.0907758 / 0.991742
  double   U/pdf   100*{64, 100} = 0 / 4096
  double   V/bins  100*{100} = 0 / 0.668056
  double   V/pdf   100*{64, 100} = 0 / 4096
  int32_t  step    100*scalar = 10 / 1000

$ python3 pdfplot.py -i pdf.bp
OR
$ mpirun -n 8 python3 pdfplot.py -i pdf.bp -o u
This is a parallel script, each process plots one PDF.
Each process plots the middle slice of their subarray U/pdf[x:y,:]

```

## How to change the parameters

Edit settings.json to change the parameters for the simulation.

| Key           | Description                           |
| ------------- | ------------------------------------- |
| L             | Size of global array (L x L x L cube) |
| Du            | Diffusion coefficient of U            |
| Dv            | Diffusion coefficient of V            |
| F             | Feed rate of U                        |
| k             | Kill rate of V                        |
| dt            | Timestep                              |
| steps         | Total number of steps to simulate     |
| plotgap       | Number of steps between output        |
| noise         | Amount of noise to inject             |
| output        | Output file/stream name               |
| adios_config  | ADIOS2 XML file name                  |

Decomposition is automatically determined by MPI_Dims_create.

## Examples

| D_u | D_v | F    | k      | Output
| ----|-----|------|------- | -------------------------- |
| 0.2 | 0.1 | 0.02 | 0.048  | ![](img/example1.jpg?raw=true) |
| 0.2 | 0.1 | 0.03 | 0.0545 | ![](img/example2.jpg?raw=true) |
| 0.2 | 0.1 | 0.03 | 0.06   | ![](img/example3.jpg?raw=true) |
| 0.2 | 0.1 | 0.01 | 0.05   | ![](img/example4.jpg?raw=true) |
| 0.2 | 0.1 | 0.02 | 0.06   | ![](img/example5.jpg?raw=true) |


## In situ pipeline example

In adios2.xml, change all IO groups' engine to SST.

      <engine type="SST"

Launch the pipeline in 4 separate terminals:
```
$ mpirun -n 4 adios2-gray-scott settings-staging.json
$ mpirun -n 1 adios2-pdf-calc gs.bp pdf.bp 100
$ mpirun -n 1 python3 pdfplot.py -i pdf.bp
$ mpirun -n 1 python3 gsplot.py -i gs.bp
```

MPMD mode run in a single terminal:
```
$ mpirun -n 4 adios2-gray-scott settings-staging.json : \
         -n 1 adios2-pdf-calc gs.bp pdf.bp 100 :           \
         -n 1 python3 pdfplot.py -i pdf.bp :         \
         -n 1 python3 gsplot.py -i gs.bp
```

