//
// Created by Hamza El-Kebir on 5/19/21.
//

#include "catchOnce.hpp"
#include "Lodestar/primitives/integrators/IntegratorNewton.hpp"

template<typename S>
void linear(ls::primitives::Integrator<S> *integrator)
{
    integrator->setState(integrator->getTime());
}

template<typename S>
void quadratic(ls::primitives::Integrator<S> *integrator)
{
    integrator->setState(integrator->getTime() * integrator->getTime());
}

/**
 * @deprecated Butcher tableau-based methods should be used instead.
 */
TEST_CASE("Newton integration", "[primitives][integrators][NewtonIntegrator]")
{
    double state = 0;
    double period = 1e-2;
    auto integrator = ls::primitives::IntegratorNewton<double>(period, &state);
    double finalTime = 0.5;

    SECTION("Linear") {
        while (integrator.getTime() <= finalTime) {
            //        quadratic(integrator);
            linear(&integrator);
            integrator.updateState();
        }

        REQUIRE(*integrator.getIntegral() == Approx(0.1225));
    }

    SECTION("Quadratic") {
        while (integrator.getTime() <= finalTime) {
            quadratic(&integrator);
            integrator.updateState();
        }

        REQUIRE(*integrator.getIntegral() == Approx(0.040425));
    }
}