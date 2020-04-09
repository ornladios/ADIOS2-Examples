#include <iostream>
#include <vector>
#include <array>
#include <cassert>
#include <adios2.h>
#include "lorenz.hpp"

void read_solution()
{
    using Real = double;
    adios2::ADIOS adios;
    adios2::IO io = adios.DeclareIO("myio");
    adios2::Engine adios_engine = io.Open("lorenz.bp", adios2::Mode::Read);
    auto sigma_att = io.InquireAttribute<Real>("σ");
    std::cout << "Simulation performed with ";
    if (sigma_att) {
        Real sigma = sigma_att.Data()[0];
        std::cout << "σ = " << sigma << ", ";
    }

    auto beta_att = io.InquireAttribute<Real>("β");
    if (beta_att) {
        Real beta = beta_att.Data()[0];
        std::cout << "β = " << beta << ", ";
    }

    auto rho_att = io.InquireAttribute<Real>("ρ");
    if (rho_att) {
        Real rho = rho_att.Data()[0];
        std::cout << "and ρ = " << rho << ".\n";
    }

    auto interpretation_att = io.InquireAttribute<std::string>("interpretation");
    if (interpretation_att) {
        std::string interpretation = interpretation_att.Data()[0];
        std::cout << "The data should be interpreted as a " << interpretation << ".\n";
    }

    auto absolute_error_att = io.InquireAttribute<Real>("‖û-u‖");
    if (absolute_error_att) {
        std::cout << "Solutions were computed with an absolute error goal of " << absolute_error_att.Data()[0] << "\n";
    }

    // Check that std::vector<std::array<Real, 7>> has the proper memory layout.
    static_assert(sizeof(std::array<Real, 7>)==7*sizeof(Real),
                  "The std::array on your system does not have the proper layout to be correctly deserialized in ADIOS2.");


    std::vector<std::array<Real, 7>> v;
    auto const & m = io.AvailableVariables();
    for (auto const & [key, val] : io.AvailableVariables())
    {
        auto state_variable = io.InquireVariable<Real>(key);
        if (!state_variable) {
            std::cerr << "We do not have a state variable " << key << "\n";
            continue;
        }
        const auto shape = state_variable.Shape();
        if (shape.size() != 1) {
            std::cerr << "Expected 1D layout.\n";
            continue;
        }
        if ((shape[0] % 7) != 0) {
            std::cerr << "The size of a 7D array of structs must be a multiple of 7.\n";
            continue;
        }
        size_t states = shape[0]/7;
        v.resize(states);

        double* d = v[0].data();
        adios_engine.Get(key, d, adios2::Mode::Sync);
        std::vector<Real> times(v.size());
        for (size_t i = 0; i < v.size(); ++i) {
            times[i] = v[i][0];
        }
        // One property of the data:
        if (!std::is_sorted(times.begin(), times.end())) {
            std::cerr << "Times should be sorted in increasing order t0 < t1 < ... < tn\n";
        }
    }
    adios_engine.Close();
}

int main()
{
    try
    {
        read_solution();
    }
    catch (std::exception const & e)
    {
        std::cerr << "Caught exception reading Lorenz ODE solution: " << e.what() << "\n";
        return 1;
    }
    return 0;
}