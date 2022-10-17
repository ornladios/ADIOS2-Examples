
import Test: @testset, @test, @test_throws
import GrayScott: Inputs

@testset "unit-Inputs._parse_args" begin
    @test Inputs._parse_args(["hello.json"]) == "hello.json"

    @test_throws(ArgumentError, Inputs._parse_args(["hello.nojson"]))
end