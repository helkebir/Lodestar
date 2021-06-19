//
// Created by Hamza El-Kebir on 6/18/21.
//

#include "catchOnce.hpp"
#include "primitives/differentiators/BackwardDifference.hpp"

TEST_CASE("Backward difference", "[primitives][differentiators]")
{
    // Linear
    REQUIRE(ls::primitives::BackwardDifference<double, 2, 1>::compute(0, 1, 1) == Approx(1));

    // Quadratic
    REQUIRE(ls::primitives::BackwardDifference<double, 3, 2>::compute(0, 1, 4, 1) == Approx(2));

    // Cubic
    REQUIRE(ls::primitives::BackwardDifference<double, 4, 3>::compute(0, 1, 8, 27, 1) == Approx(6));
}