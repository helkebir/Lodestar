//
// Created by Hamza El-Kebir on 2/19/22.
//

#include "catchOnce.hpp"
#include <Lodestar/blocks/std/MinMaxIdxBlock.hpp>
#include <Eigen/Dense>

TEST_CASE("MinMaxIdxBlock", "[blocks][std]")
{
    Eigen::Matrix3d M;
    M << 1, 2, -3,
            4, 15, -6,
            5, 4, -5;

    ls::blocks::std::MinMaxIdxBlock<decltype(M), ls::blocks::std::MinMaxIdxBlockOperator::Min> minBlock;
    ls::blocks::std::MinMaxIdxBlock<decltype(M), ls::blocks::std::MinMaxIdxBlockOperator::Max> maxBlock;

    minBlock.i<0>() = M;
    maxBlock.i<0>() = M;

    minBlock.trigger();
    maxBlock.trigger();

    REQUIRE(minBlock.o<0>().object == 1);
    REQUIRE(minBlock.o<1>().object == 2);
    REQUIRE(minBlock.o<2>().object == Approx(-6));

    REQUIRE(maxBlock.o<0>().object == 1);
    REQUIRE(maxBlock.o<1>().object == 1);
    REQUIRE(maxBlock.o<2>().object == Approx(15));
}