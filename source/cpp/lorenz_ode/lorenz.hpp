#ifndef LORENZ_HPP
#define LORENZ_HPP
#include <iostream>
#include <vector>
#include <array>
#include <cmath>
#include <cassert>
#include <algorithm>


// Solves the Lorenz system using Taylor methods.
// See: https://en.wikipedia.org/wiki/Lorenz_system
// and Corliss, "A Graduate Introduction to Numerical Methods" (https://doi.org/10.1007/978-1-4614-8453-0)
// for an introduction to Taylor methods for ODEs.

template<typename Real>
class lorenz {
public:
    lorenz(const Real sigma, const Real beta, const Real rho,
           std::array<Real, 3> const & initial_conditions, const Real tmax, const Real absolute_error_goal)
    {
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
            const Real m = std::min({abs(ddotx), abs(ddoty), abs(ddotz)});
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

            // Taylor series:
            t += dt;
            x += dt*dotx + dt*dt*ddotx/2;
            y += dt*doty + dt*dt*ddoty/2;
            z += dt*dotz + dt*dt*ddotz/2;

            // Now compute the derivatives at the new location:
            dotx = sigma*(y - x);
            doty = x*(rho - z) - y;
            dotz = x*y - beta*z;
            ddotx = sigma*(doty - dotx);
            ddoty = dotx*(rho - z) - x*dotz - doty;
            ddotz = dotx*y + x*doty - beta*dotz;

            // And store the state:
            state_.emplace_back(std::array<Real, 7>{t, x, y, z, dotx, doty, dotz});
        }
    }

    // Load data:
    lorenz(std::vector<std::array<Real, 7>> && state) : state_{std::move(state)}
    {};

    std::array<Real, 3> operator()(Real t) const {
        Real nan = std::numeric_limits<Real>::quiet_NaN();
        return {nan, nan, nan};
    }

    const std::vector<std::array<Real, 7>>& state() const {
        return state_;
    }


private:
    std::vector<std::array<Real, 7>> state_;
};

template<typename Real>
void test_lorenz()
{
    // Kinda ridiculous to run tests this way,
    // but I don't want to introduce a dependency on a unit test framework into this repo.
    // Test 1: If x(0) = y(0) = 0, then x(t) = y(t) = 0 and z(t) = z(0)exp(-βt).
    Real sigma = 10;
    Real beta = Real(8)/Real(3);
    Real rho = 28;
    Real tmax = 10;
    Real absolute_error = 1e-5;
    const std::array<Real, 3> initial_conditions{0, 0, Real(1)};
    auto solution = lorenz<double>(sigma, beta, rho, initial_conditions, tmax, absolute_error);
    auto const & skeleton = solution.state();

    for (auto const & s : skeleton) {
        Real t = s[0];
        Real x = s[1];
        Real y = s[2];
        Real z = s[3];
        if (abs(x) > std::numeric_limits<Real>::epsilon()) {
            throw std::logic_error("x < eps doesn't hold");
        }
        if (abs(y) > std::numeric_limits<Real>::epsilon()) {
            throw std::logic_error("y < eps doesn't hold");
        }
        Real expected = std::exp(-beta*t);
        if (abs(expected - z) > 100*absolute_error) {
            std::cerr << "Expected z = " << expected << "\n";
            std::cerr << "Computed z = " << z << "\n";
            throw std::logic_error("z(t) = exp(-βt) doesn't hold");
        }
    }
}

#endif
