//
// Created by Hamza El-Kebir on 2/19/22.
//

#include "catchOnce.hpp"
#include <Lodestar/blocks/std/MinMaxBlock.hpp>
#include <Eigen/Dense>

TEST_CASE("MinMaxBlock", "[blocks][std]")
{
    Eigen::Matrix3d M;
    M << 1, 2, -3,
         4, 15, -6,
         5, 4, -5;

    ls::blocks::std::MinMaxBlock<decltype(M), ls::blocks::std::MinMaxBlockOperator::Min> minBlock;
    ls::blocks::std::MinMaxBlock<decltype(M), ls::blocks::std::MinMaxBlockOperator::Max> maxBlock;

    minBlock.i<0>() = M;
    maxBlock.i<0>() = M;

    minBlock.trigger();
    maxBlock.trigger();

    REQUIRE(::std::is_same<typename decltype(minBlock)::OutputType, double>::value);
    REQUIRE(::std::is_same<typename decltype(maxBlock)::OutputType, double>::value);

    REQUIRE(minBlock.o<0>().object == Approx(-6));
    REQUIRE(maxBlock.o<0>().object == Approx(15));
}