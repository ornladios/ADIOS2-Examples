#ifndef LORENZ_HPP
#define LORENZ_HPP
#include <iostream>
#include <vector>
#include <array>
#include <cmath>
#include <cassert>
#include <algorithm>


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

    // Load data:
    lorenz(std::vector<std::array<Real, 7>> && state) : state_{std::move(state)}
    {};

    const std::vector<std::array<Real, 7>>& state() const {
        return state_;
    }


private:
    std::vector<std::array<Real, 7>> state_;
};

#endif