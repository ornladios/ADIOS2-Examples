
"""
Settings carry the settings from the simulation config file (json or yaml formats)

Using Base.@kwdef macro for easy defaults and enable keyword arguments
Settings(Du = 0.2, noise = 0.2) 
See:
https://discourse.julialang.org/t/default-value-of-some-fields-in-a-mutable-struct/33408/24?u=williamfgc
"""
Base.@kwdef mutable struct Settings
    L::Int64 = 128
    steps::Int32 = 20000
    plotgap::Int32 = 200
    F::Float64 = 0.04
    k::Float64 = 0
    dt::Float64 = 0.2
    Du::Float64 = 0.05
    Dv::Float64 = 0.1
    noise::Float64 = 0.0
    output::String = "foo.bp"
    checkpoint::Bool = false
    checkpoint_freq::Int32 = 2000
    checkpoint_output::String = "ckpt.bp"
    restart::Bool = false
    restart_input::String = "ckpt.bp"
    adios_config::String = "adios2.yaml"
    adios_span::String = false
    adios_memory_selection::Bool = false
    mesh_type::String = "image"
end
