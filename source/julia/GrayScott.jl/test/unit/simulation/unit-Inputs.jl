
import Test: @testset, @test, @test_throws
import GrayScott: Inputs

@testset "unit-Inputs.get_settings" begin
    config_file = joinpath(dirname(Base.active_project()), "examples",
                           "settings-files.json")
    Inputs.get_settings([config_file], MPI.COMM_WORLD)
end

@testset "unit-Inputs._parse_args" begin
    @test Inputs._parse_args(["hello.json"]) == "hello.json"

    @test_throws(ArgumentError, Inputs._parse_args(["hello.nojson"]))
end