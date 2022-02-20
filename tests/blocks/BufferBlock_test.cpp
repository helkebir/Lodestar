//
// Created by Hamza El-Kebir on 2/19/22.
//

#include "catchOnce.hpp"
#include <Lodestar/blocks/std/BufferBlock.hpp>

TEST_CASE("BufferBlock", "[blocks][std]")
{
    ls::blocks::std::BufferBlock<double, 3> bufferBlock;

    bufferBlock.clear(0);
    bufferBlock.i<0>() = 2;

    REQUIRE(bufferBlock.o<0>() == 0);
    REQUIRE(bufferBlock.o<1>() == 0);
    REQUIRE(bufferBlock.o<2>() == 0);

    bufferBlock.trigger();
    REQUIRE(bufferBlock.o<0>() == Approx(2));
    REQUIRE(bufferBlock.o<1>() == 0);
    REQUIRE(bufferBlock.o<2>() == 0);

    bufferBlock.i<0>() = 1;
    bufferBlock.trigger();
    REQUIRE(bufferBlock.o<0>() == Approx(1));
    REQUIRE(bufferBlock.o<1>() == Approx(2));
    REQUIRE(bufferBlock.o<2>() == 0);

    bufferBlock.i<0>() = 3;
    bufferBlock.trigger();
    REQUIRE(bufferBlock.o<0>() == Approx(3));
    REQUIRE(bufferBlock.o<1>() == Approx(1));
    REQUIRE(bufferBlock.o<2>() == Approx(2));
}