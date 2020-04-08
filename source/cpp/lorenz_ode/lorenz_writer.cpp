#include <iostream>
#include <vector>
#include <array>
#include <cassert>
#include <adios2.h>
#include "lorenz.hpp"

int main()
{
    using Real = double;
    Real sigma = 10;
    Real beta = Real(8)/Real(3);
    Real rho = 28;
    Real tmax = 10;
    Real absolute_error = 1e-5;

    adios2::ADIOS adios;
    adios2::IO io = adios.DeclareIO("myio");
    io.DefineAttribute<Real>("σ", sigma);
    io.DefineAttribute<Real>("β", beta);
    io.DefineAttribute<Real>("ρ", rho);
    io.DefineAttribute<Real>("‖û-u‖", absolute_error);
    io.DefineAttribute<std::string>("interpretation", "7D array of structs {tᵢ, xᵢ, yᵢ, zᵢ, ẋᵢ, ẏᵢ, żᵢ}");
    adios2::Engine adios_engine = io.Open("lorenz.bp", adios2::Mode::Write);

    size_t paths = 2;
    for (size_t i = 0; i < paths; ++i) {
        for (size_t j = 0; j < paths; ++j) {
            for (size_t k = 0; k < paths; ++k) {
                std::array<Real, 3> initial_conditions{Real(i),Real(j),Real(k)};
                auto solution = lorenz<double>(sigma, beta, rho, initial_conditions, tmax, absolute_error);
                auto const & skeleton = solution.state();
                std::cout << skeleton.size() << " points in solution skeleton.\n";
                for (size_t i = 0; i < skeleton.size(); ++i) {
                    const double * const p = skeleton[0].data();
                    for (size_t j = 0; j < 7; ++j) {
                        assert(skeleton[i][j] == p[7*i+j]);
                    }
                }
                std::string variable = "u" + std::to_string(i) + std::to_string(j) + std::to_string(k);
                auto state_variable = io.DefineVariable<Real>(variable, {7*skeleton.size()}, {0}, {7*skeleton.size()}, adios2::ConstantDims);
                adios_engine.BeginStep();
                adios_engine.Put(state_variable, skeleton[0].data());
                adios_engine.EndStep();
            }
        }
    }
    adios_engine.Close();
}