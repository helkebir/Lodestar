//
// Created by Hamza El-Kebir on 2/19/22.
//

#include "catchOnce.hpp"
#include <Lodestar/blocks/std/UnaryMeanBlock.hpp>
#include <Eigen/Dense>

TEST_CASE("UnaryMeanBlock", "[blocks][std]")
{
    Eigen::Matrix3d M;
    M << 1, 2, -3,
            4, 15, -6,
            5, 4, -5;

    ls::blocks::std::UnaryMeanBlock<decltype(M)> meanBlock;

    meanBlock.i<0>() = M;

    meanBlock.trigger();

    REQUIRE(::std::is_same<typename decltype(meanBlock)::OutputType, double>::value);

    REQUIRE(meanBlock.o<0>().object == Approx(1.88888888));
}