//
// Created by Hamza El-Kebir on 12/23/21.
//

#include "catchOnce.hpp"
#include "Lodestar/blocks/std/GainBlock.hpp"
#include "Eigen/Dense"


TEST_CASE("GainBlock", "[blocks][std]")
{
    SECTION("Arithmetic types") {
        ls::blocks::std::GainBlock<double> gb{};

        gb.i<0>() = 2;
        gb.setGain(3);
        gb.trigger();

        REQUIRE(gb.o<0>() == Approx(6));
    }

    SECTION("Eigen types") {
        ls::blocks::std::GainBlock<Eigen::Vector3d, Eigen::Matrix3d> gb{};

        Eigen::Vector3d v;
        v << 1, 2, 3;

        Eigen::Matrix3d m = -Eigen::Matrix3d::Identity();

        gb.i<0>() = v;
        gb.setGain(m);
        gb.trigger();

        REQUIRE(gb.o<0>().object(0) == Approx(-1));
        REQUIRE(gb.o<0>().object(1) == Approx(-2));
        REQUIRE(gb.o<0>().object(2) == Approx(-3));
    }
}