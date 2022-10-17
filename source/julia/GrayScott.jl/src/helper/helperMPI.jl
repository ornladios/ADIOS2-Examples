
import MPI

function bcast_file(file_name::String, comm)
    rank = MPI.Comm_rank(comm)
    if rank == 0
        io = open(file_name, "r")
        @show typeof(io)
        data = read(io)
        @show length(data)
        # buffer::Vector{Int8}
        # read!(io, buffer)
        #println(io)
    else
    end
end
