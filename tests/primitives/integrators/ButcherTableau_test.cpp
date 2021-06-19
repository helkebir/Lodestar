//
// Created by Hamza El-Kebir on 6/18/21.
//

#include "catchOnce.hpp"
#include "primitives/integrators/ButcherTableau.hpp"

TEST_CASE("ButcherTableau", "[primitves][integrators]")
{
    ls::primitives::ButcherTableau<4> bt;

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

//    std::get<0>(bt.rows).node = 1.0 / 2.0;
//    std::get<0>(bt.rows).rkCoefficients[0] = 1.0 / 2.0;
//
//    std::get<1>(bt.rows).node = 3.0 / 4.0;
//    std::get<1>(bt.rows).rkCoefficients[0] = 0;
//    std::get<1>(bt.rows).rkCoefficients[1] = 3.0 / 4.0;
//
//    std::get<2>(bt.rows).node = 1;
//    std::get<2>(bt.rows).rkCoefficients[0] = 2.0 / 9.0;
//    std::get<2>(bt.rows).rkCoefficients[1] = 1.0 / 3.0;
//    std::get<2>(bt.rows).rkCoefficients[2] = 4.0 / 9.0;
//
//    std::get<3>(bt.rows).weights[0] = 2.0 / 9.0;
//    std::get<3>(bt.rows).weights[1] = 1.0 / 3.0;
//    std::get<3>(bt.rows).weights[2] = 4.0 / 9.0;
//    std::get<3>(bt.rows).weights[3] = 0.0;
}