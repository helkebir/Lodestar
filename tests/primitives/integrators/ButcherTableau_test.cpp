//
// Created by Hamza El-Kebir on 6/18/21.
//

#include "catchOnce.hpp"
#include "Lodestar/primitives/integrators/ButcherTableau.hpp"
#include "Lodestar/primitives/integrators/BogackiShampine.hpp"

TEST_CASE("ButcherTableau", "[primitives][integrators]")
{
    SECTION("Simple Butcher tableau") {
        ls::primitives::ButcherTableau<4, false> bt;

        bt.setNode<0>(1.0 / 2.0);
        bt.setCoefficient<0,0>(1.0 / 2.0);

        bt.setNode<1>(3.0 / 4.0);
        bt.setCoefficient<1,0>(0.0);
        bt.setCoefficient<1,1>(3.0 / 4.0);

        bt.setNode<2>(1.0);
        bt.setCoefficient<2,0>(2.0 / 9.0);
        bt.setCoefficient<2,1>(1.0 / 3.0);
        bt.setCoefficient<2,2>(4.0 / 9.0);

        bt.setWeight<0>(2.0 / 9.0);
        bt.setWeight<1>(1.0 / 3.0);
        bt.setWeight<2>(4.0 / 9.0);
        bt.setWeight<3>(0.0);

        REQUIRE(bt.getNode<0>() == Approx(1.0 / 2.0));
        REQUIRE(bt.getNode<1>() == Approx(3.0 / 4.0));
        REQUIRE(bt.getNode<2>() == Approx(1.0));

        REQUIRE(bt.getCoefficient<0,0>() == Approx(1.0 / 2.0));

        REQUIRE(bt.getCoefficient<1,0>() == Approx(0.0));
        REQUIRE(bt.getCoefficient<1,1>() == Approx(3.0 / 4.0));

        REQUIRE(bt.getCoefficient<2,0>() == Approx(2.0 / 9.0));
        REQUIRE(bt.getCoefficient<2,1>() == Approx(1.0 / 3.0));
        REQUIRE(bt.getCoefficient<2,2>() == Approx(4.0 / 9.0));

        REQUIRE(bt.getWeight<0>() == Approx(2.0 / 9.0));
        REQUIRE(bt.getWeight<1>() == Approx(1.0 / 3.0));
        REQUIRE(bt.getWeight<2>() == Approx(4.0 / 9.0));
        REQUIRE(bt.getWeight<3>() == Approx(0.0));
    }

    SECTION("Extended Butcher tableau") {
        ls::primitives::ButcherTableau<4, true> btExtended;

        btExtended.setNode<0>(1.0 / 2.0);
        btExtended.setCoefficient<0, 0>(1.0 / 2.0);

        btExtended.setNode<1>(3.0 / 4.0);
        btExtended.setCoefficient<1, 0>(0.0);
        btExtended.setCoefficient<1, 1>(3.0 / 4.0);

        btExtended.setNode<2>(1.0);
        btExtended.setCoefficient<2, 0>(2.0 / 9.0);
        btExtended.setCoefficient<2, 1>(1.0 / 3.0);
        btExtended.setCoefficient<2, 2>(4.0 / 9.0);

        btExtended.setWeight<0, true>(2.0 / 9.0);
        btExtended.setWeight<1, true>(1.0 / 3.0);
        btExtended.setWeight<2, true>(4.0 / 9.0);
        btExtended.setWeight<3, true>(0.0);

        btExtended.setWeight<0, false>(7.0 / 24.0);
        btExtended.setWeight<1, false>(1.0 / 4.0);
        btExtended.setWeight<2, false>(1.0 / 3.0);
        btExtended.setWeight<3, false>(1.0 / 8.0);

        REQUIRE(btExtended.getNode<0>() == Approx(1.0 / 2.0));
        REQUIRE(btExtended.getNode<1>() == Approx(3.0 / 4.0));
        REQUIRE(btExtended.getNode<2>() == Approx(1.0));

        REQUIRE(btExtended.getCoefficient<0, 0>() == Approx(1.0 / 2.0));

        REQUIRE(btExtended.getCoefficient<1, 0>() == Approx(0.0));
        REQUIRE(btExtended.getCoefficient<1, 1>() == Approx(3.0 / 4.0));

        REQUIRE(btExtended.getCoefficient<2, 0>() == Approx(2.0 / 9.0));
        REQUIRE(btExtended.getCoefficient<2, 1>() == Approx(1.0 / 3.0));
        REQUIRE(btExtended.getCoefficient<2, 2>() == Approx(4.0 / 9.0));

        REQUIRE(btExtended.getWeight<0, true>() == Approx(2.0 / 9.0));
        REQUIRE(btExtended.getWeight<1, true>() == Approx(1.0 / 3.0));
        REQUIRE(btExtended.getWeight<2, true>() == Approx(4.0 / 9.0));
        REQUIRE(btExtended.getWeight<3, true>() == Approx(0.0));

        REQUIRE(btExtended.getWeight<0, false>() == Approx(7.0 / 24.0));
        REQUIRE(btExtended.getWeight<1, false>() == Approx(1.0 / 4.0));
        REQUIRE(btExtended.getWeight<2, false>() == Approx(1.0 / 3.0));
        REQUIRE(btExtended.getWeight<3, false>() == Approx(1.0 / 8.0));
    }
}