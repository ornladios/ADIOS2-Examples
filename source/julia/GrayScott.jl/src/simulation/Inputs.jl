
# submodule used by GrayScott to handle inputs 
module Inputs

export get_settings

import ArgParse

# public facing function
function get_settings(args::Vector{String}, comm)
    config_file = _parse_args(args)

    if endWith(config_file, ".json")
        return _parse_settings_json(config_file, comm)
    end

    return
end

# local scope functions
function _parse_settings_json(config_file::String, comm)
end

function _parse_args(args::Vector{String};
                     error_handler = ArgParse.default_handler)::String
    s = ArgParse.ArgParseSettings(description = "gray-scott workflow simulation example configuration file, Julia version, GrayScott.jl",
                                  exc_handler = error_handler)

    ArgParse.@add_arg_table! s begin
        "config_file"
        help = "configuration file"
        arg_type = String
        required = true
    end

    # parse_args return a dictionary with key/value for arguments
    parsed_arguments = ArgParse.parse_args(args, s)

    # key is mandatory, so it's safe to retrieve
    config_file::String = parsed_arguments["config_file"]

    # check format extension
    if !endswith(config_file, ".json") &&
       !(endswith(config_file, ".yaml") || endswith(config_file, ".yml"))
        throw(ArgumentError("config file must be json, yaml format. Extension not recognized.\n"))
    end

    return config_file
end

end # module