
import Test: @testset, @test, @test_throws
import GrayScott: Helper

#@testset "unit-Helper.bcast_file" begin
config_file = joinpath(dirname(Base.active_project()), "examples",
                       "settings-files.json")
@show config_file
Helper.bcast_file(config_file, MPI.COMM_WORLD)
#end