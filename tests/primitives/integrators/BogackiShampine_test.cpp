//
// Created by Hamza El-Kebir on 6/19/21.
//

#include "catchOnce.hpp"
#include "Lodestar/primitives/integrators/BogackiShampine.hpp"

TEST_CASE("Bogacki-Shampine", "[primitives][integrators]")
{
    std::function<double(double, double)> f = [](double t, double y) {
        return t*t*t;
    };

    SECTION("Higher order") {
        double t = 0, y = 0;
        double h = 0.025;
        int N = 20;
        ls::primitives::BogackiShampine<double>::integrateSimple(f, t, y, h, N);

        REQUIRE(y == Approx(0.015625));
    }

    SECTION("Truncation error") {
        double t = 0, y = 0;
        double h = 0.025;
        int N = 20;
        auto err = ls::primitives::BogackiShampine<double>::integrateEmbedded(f, t, y, h, N);

        REQUIRE(y == Approx(0.015625));
    }
}