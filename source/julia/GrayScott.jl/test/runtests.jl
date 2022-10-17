
import MPI

# Run all lightweight unit and functional tests within a single MPI session
MPI.Init()

# unit tests
include(joinpath("unit", "helper", "unit-helperMPI.jl"))

# functional tests
include(joinpath("unit", "simulation", "unit-Inputs.jl"))

MPI.Finalize()

# Command line tests. These are heavier tests launched as separate processes.
# The downside is that only global success can be tested and not internal states.