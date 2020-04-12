#include <iostream>
#include <vector>
#include <array>
#include <cassert>
#include <adios2.h>
#include "lorenz.hpp"

int main()
{
    using Real = double;
    adios2::ADIOS adios;
    adios2::IO io = adios.DeclareIO("myio");
    adios2::Engine adios_engine = io.Open("lorenz.bp", adios2::Mode::Read);
    auto sigma_att = io.InquireAttribute<Real>("σ");
    if (sigma_att) {
        Real sigma = sigma_att.Data()[0];
        std::cout << "σ = " << sigma << "\n";
    }

    auto beta_att = io.InquireAttribute<Real>("β");
    if (beta_att) {
        Real beta = beta_att.Data()[0];
        std::cout << "β = " << beta << "\n";
    }

    auto rho_att = io.InquireAttribute<Real>("ρ");
    if (rho_att) {
        Real rho = rho_att.Data()[0];
        std::cout << "ρ = " << rho << "\n";
    }

    auto interpretation_att = io.InquireAttribute<std::string>("interpretation");
    if (interpretation_att) {
        std::string interpretation = interpretation_att.Data()[0];
        std::cout << "Interpretation: " << interpretation << "\n";
    }

    auto absolute_error_att = io.InquireAttribute<Real>("‖û-u‖");
    if (absolute_error_att) {
        std::cout << "Solutions computed with absolute error goal of " << absolute_error_att.Data()[0] << "\n";
    }

    size_t paths = 2;
    std::vector<std::array<Real, 7>> v;
    for (size_t i = 0; i < paths; ++i) {
        for (size_t j = 0; j < paths; ++j) {
            for (size_t k = 0; k < paths; ++k) {
                std::string variable = "u" + std::to_string(i) + std::to_string(j) + std::to_string(k);
                auto state_variable = io.InquireVariable<Real>(variable);
                if (state_variable) {
                    std::cout << "We have state variable " << variable << "\n";
                }
            }
        }
    }
    adios_engine.Close();
}