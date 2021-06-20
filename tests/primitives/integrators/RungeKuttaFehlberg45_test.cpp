//
// Created by Hamza El-Kebir on 6/19/21.
//

#include "catchOnce.hpp"
#include "primitives/integrators/RungeKuttaFehlberg45.hpp"
#include <iostream>

TEST_CASE("Runge-Kutta-Fehlberg 45", "[primitives][integrators]")
{
    std::function<double(double, double)> f = [](double t, double y) {
        return t*t*t;
    };

    SECTION("Higher order") {
        double t = 0, y = 0;
        double h = 0.025;
        int N = 20;
        ls::primitives::RungeKuttaFehlberg45<double>::integrateSimple(f, t, y, h, N);

        REQUIRE(y == Approx(0.015625));
    }

    SECTION("Truncation error") {
        double t = 0, y = 0;
        double h = 0.5;
        int N = 1;
        auto err = ls::primitives::RungeKuttaFehlberg45<double>::integrateEmbedded(f, t, y, h, N);

        REQUIRE(y == Approx(0.015625));

        std::cout << "Local truncation error: " << err << std::endl;
        std::cout << "Result: " << y << std::endl;
    }
}