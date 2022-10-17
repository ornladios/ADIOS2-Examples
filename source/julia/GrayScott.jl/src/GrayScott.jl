module GrayScott

import MPI

include("simulation/Settings.jl")

include("helper/Helper.jl")
import .Helper

include("simulation/Inputs.jl")
import .Inputs

include("simulation/Simulation.jl")
import .Simulation

function julia_main()::Cint
    try
        main(ARGS)
    catch
        Base.invokelatest(Base.display_error, Base.catch_stack())
        return 1
    end
    return 0
end

function main(args::Vector{String})
    @show args

    # Initialize MPI and get world comm, rank, size
    MPI.Init()
    comm = MPI.COMM_WORLD
    rank = MPI.Comm_rank(comm)
    size = MPI.Comm_size(comm)

    settings = Inputs.get_settings(args, comm)
end

end # module GrayScott
