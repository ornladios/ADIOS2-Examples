#include <iostream>
#include <vector>
#include <array>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <adios2.h>

template<typename Real>
class lorenz {
public:
    lorenz(Real sigma, Real beta, Real rho,
           std::array<Real, 3> const & initial_conditions, Real tmax, Real absolute_error_goal)
    {
        static_assert(sizeof(std::array<Real, 7>)==7*sizeof(Real),
                             "The std::array on your system does not have the proper layout to be correctly serialized in ADIOS2.");
        using std::sqrt;
        using std::abs;
        using std::cbrt;
        if (tmax <= 0)
        {
            throw std::domain_error("tmax > 0 is required");
        }
        if (absolute_error_goal <= std::numeric_limits<Real>::epsilon())
        {
            throw std::domain_error("Abolute error goal > eps is required");
        }
        Real t = 0;
        Real x = initial_conditions[0];
        Real y = initial_conditions[1];
        Real z = initial_conditions[2];
        Real dotx = sigma*(y - x);
        Real doty = x*(rho - z) - y;
        Real dotz = x*y - beta*z;
        Real ddotx = sigma*(doty - dotx);
        Real ddoty = dotx*(rho - z) - x*dotz - doty;
        Real ddotz = dotx*y + x*doty - beta*dotz;
        state_.emplace_back(std::array<Real, 7>{t, x, y, z, dotx, doty, dotz});
        while (t < tmax)
        {
            // ∆t must satisfy three constraints:
            // ∆t^2 < 2µ/|ddot(x)|, ∆t^2 < 2µ/|ddot(y)|, ∆t^2 < 2µ/|ddot(z)|.
            // where µ = absolute_error_goal.
            Real m = std::min({abs(ddotx), abs(ddoty), abs(ddotz)});
            Real dt;
            // If all second derivaties are zero, we're actually *more* accurate:
            if (m==0)
            {
                dt = cbrt(6*absolute_error_goal);
            }
            else
            {
                dt = sqrt(2*absolute_error_goal/m);
            }

            t += dt;
            x += dt*dotx + dt*dt*ddotx/2;
            y += dt*doty + dt*dt*ddoty/2;
            z += dt*dotz + dt*dt*ddotz/2;
            dotx = sigma*(y - x);
            doty = x*(rho - z) - y;
            dotz = x*y - beta*z;
            ddotx = sigma*(doty - dotx);
            ddoty = dotx*(rho - z) - x*dotz - doty;
            ddotz = dotx*y + x*doty - beta*dotz;

            state_.emplace_back(std::array<Real, 7>{t, x, y, z, dotx, doty, dotz});
        }
    }

    const std::vector<std::array<Real, 7>>& state() const {
        return state_;
    }


private:
    std::vector<std::array<Real, 7>> state_;
};


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
                std::string variable = "u_" + std::to_string(i) + "_" + std::to_string(j) + "_" + std::to_string(k);
                auto state_variable = io.DefineVariable<Real>(variable, {7*skeleton.size()}, {0}, {7*skeleton.size()}, adios2::ConstantDims);
                adios_engine.BeginStep();
                adios_engine.Put(state_variable, skeleton[0].data());
                adios_engine.EndStep();
            }
        }
    }

    adios_engine.Close();
}