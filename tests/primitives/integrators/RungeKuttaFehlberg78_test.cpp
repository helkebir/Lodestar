//
// Created by Hamza El-Kebir on 6/19/21.
//

#include "catchOnce.hpp"
#include "Lodestar/primitives/integrators/RungeKuttaFehlberg78.hpp"
#include <Eigen/Dense>

TEST_CASE("Runge-Kutta-Fehlberg 78", "[primitives][integrators]")
{
    std::function<double(double, double)> f = [](double t, double y) {
        return t * t * t;
    };

    typedef Eigen::Matrix<double, 3, 1> TDStateVector;
    std::function<TDStateVector(double, const TDStateVector&)> F = [](double t, const TDStateVector &x) {
        TDStateVector xdot;
        xdot << t, t*t, t*t*t;

        return xdot;
    };

    SECTION("Higher order") {
        double t = 0, y = 0;
        double h = 0.025;
        int N = 20;
        ls::primitives::RungeKuttaFehlberg78<double>::integrateSimple(f, t, y, h, N);

        REQUIRE(y == Approx(0.015625));
    }

    SECTION("Multivariate") {
        double t = 0;
        TDStateVector x;
        x.setZero();
//        x.array() += 2;

        double h = 0.025;
        int N = 20;
        ls::primitives::RungeKuttaFehlberg78<TDStateVector>::integrateSimple(F, t, x, h, N);

        REQUIRE(x(0) == Approx(0.125));
        REQUIRE(x(1) == Approx(0.0416667));
        REQUIRE(x(2) == Approx( 0.015625));
    }

    SECTION("Truncation error") {
        double t = 0, y = 0;
        double h = 0.5;
        int N = 1;
        auto err = ls::primitives::RungeKuttaFehlberg78<double>::integrateEmbedded(f, t, y, h, N);

        REQUIRE(y == Approx(0.015625));
    }
}