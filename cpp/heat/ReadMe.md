Heat Transfer 2D example

This example solves a 2D Poisson equation for temperature in homogeneous media
using finite differences. This examples shows a straight-forward way to hook 
an application to the ADIOS2 library for its IO.


1. simulation: illustrates the Write API
  
2. analysis: illustrates the Read API that allows running the reader either as

    * post-mortem to read all output steps
    * in situ to read step by step as the writer outputs them 
       (need to run with a suitable engine)

3. visualization: illustrates the Read API and use of VTK-M to produce 2D images



Example


1. Simulation: produce an output

Simulation usage:  heatSimulation  config output  N  M   nx  ny   steps iterations
  config: XML config file to use
  output: name of output data file/stream
  N:      number of processes in X dimension
  M:      number of processes in Y dimension
  nx:     local array size in X dimension per processor
  ny:     local array size in Y dimension per processor
  steps:  the total number of steps to output
  iterations: one step consist of this many iterations

The ADIOS2 executable needs an XML config file to select the Engine used for the output. 
The engines are: BPFile, ADIOS1, HDF5, SST, DataMan, InSituMPI
(corresponding XML config files are available in runtimecfg/). 


```bash
$  mpirun -n 12 ./heatSimulation runtimecfg/bpfile.xml  sim.bp  4 3  5 10 10 10
```

2. Analysis: read the output step-by-step, calculate new data, and produce another output 

Analysis Usage:   heatAnalysis  config  input output  N  M 
  config: XML config file to use
  input:  name of input data file/stream
  output: name of output data file/stream
  N:      number of processes in X dimension
  M:      number of processes in Y dimension


```bash
$ mpirun -n 2 ./heatAnalysis runtimecfg/bpfile.xml sim.bp analysis.bp 2 1 

```

Notes:
1. 	Engines for file-based output and post-mortem reading: 

   * BPFile
   * HDF5
   * ADIOS1

2. Engines for in situ execution

   * SST
   * InSituMPI
     Must run the codes together with one mpirun command (MPMD style), e.g. 
```bash
$ mpirun -n 12 ./heatSimulation runtimecfg/insitu.xml  sim.bp  4 3  5 10 10 10 :  \
         -n 2 ./heatAnalysis runtimecfg/insitu.xml sim.bp analysis.bp 2 1
```
   * DataMan
     Only for N-to-N data transfers. 
     (Must run writer and reader with the same number of processes and same decomposition)



