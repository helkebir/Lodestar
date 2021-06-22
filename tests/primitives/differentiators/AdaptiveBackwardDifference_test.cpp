//
// Created by Hamza El-Kebir on 6/20/21.
//

#include "catchOnce.hpp"
#include "primitives/differentiators/AdaptiveBackwardDifference.hpp"
#include <cmath>
//#include <iostream>

TEST_CASE("Adaptive backward difference", "[primitives][differentiators]")
{
    std::array<double, 2> a = {1.0 / 7.0, 0};
    double h = 1;
    REQUIRE(ls::primitives::AdaptiveBackwardDifference<double, 1>::compute(h, a) == Approx(1.0 / 7.0));

    std::array<double, 3> a3 = {pow(1.0, 6.0) / 7.0, pow(0.5, 6.0) / 7.0, 0.0};
    ls::primitives::AdaptiveBackwardDifference<double, 1>::compute(0.5, a3);
//    std::cout << "A3 differential: " << ls::primitives::AdaptiveBackwardDifference<double, 1>::compute(0.5, a3) << std::endl;

    std::array<double, 5> a5 = {pow(1.0, 6.0) / 7.0,
                                pow(0.5, 6.0) / 7.0,
                                pow(0.0, 6.0) / 7.0,
                                pow(-0.5, 6.0) / 7.0,
                                pow(-1.0, 6.0) / 7.0,};
    ls::primitives::AdaptiveBackwardDifference<double, 1>::compute(0.5, a5);
//    std::cout << "A5 differential: " << ls::primitives::AdaptiveBackwardDifference<double, 1>::compute(0.5, a5) << std::endl;

    std::array<double, 7> a7 = {pow(1.0, 6.0) / 7.0,
                                pow(0.5, 6.0) / 7.0,
                                pow(0.0, 6.0) / 7.0,
                                pow(-0.5, 6.0) / 7.0,
                                pow(-1.0, 6.0) / 7.0,
                                pow(-1.5, 6.0) / 7.0,
                                pow(-2.0, 6.0) / 7.0,};
//    std::cout << "A7 differential: " << ls::primitives::AdaptiveBackwardDifference<double, 1>::compute(0.5, a7) << std::endl;
    REQUIRE(ls::primitives::AdaptiveBackwardDifference<double, 1>::compute(0.5, a7) == Approx(6.0 / 7.0));
}