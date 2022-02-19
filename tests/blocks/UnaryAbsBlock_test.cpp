//
// Created by Hamza El-Kebir on 2/19/22.
//

#include "catchOnce.hpp"
#include <Lodestar/blocks/std/UnaryAbsBlock.hpp>
#include <Eigen/Dense>

TEST_CASE("UnaryAbsBlock", "[blocks][std]")
{
    Eigen::Matrix3d M;
    M << 1, 2, -3,
            4, -15, -6,
            5, 4, -5;

    ls::blocks::std::UnaryAbsBlock<decltype(M)> absBlock;
    absBlock.i<0>() = M;
    absBlock.trigger();
    REQUIRE(absBlock.o<0>().object(1,1) == Approx(15));

    ls::blocks::std::UnaryAbsBlock<double> absBlock2;
    absBlock2.i<0>() = -2;
    absBlock2.trigger();
    REQUIRE(absBlock2.o<0>().object == Approx(2));
}