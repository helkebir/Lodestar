//
// Created by Hamza El-Kebir on 2/24/22.
//

#include "catchOnce.hpp"
#include <Lodestar/blocks/std/DelayBlock.hpp>

TEST_CASE("DelayBlock", "[blocks][std]")
{
    ls::blocks::std::DelayBlock<double, 1> delayBlock;
    ls::blocks::std::DelayBlock<double, 2> delayBlock2;

    delayBlock.clear(0);
    delayBlock.i<0>() = 2;

    REQUIRE(delayBlock.o<0>() == 0);

    delayBlock.trigger();
    REQUIRE(delayBlock.o<0>() == Approx(0));

    delayBlock.i<0>() = 1;
    delayBlock.trigger();
    REQUIRE(delayBlock.o<0>() == Approx(2));

    delayBlock.i<0>() = 3;
    delayBlock.trigger();
    REQUIRE(delayBlock.o<0>() == Approx(1));

    delayBlock.i<0>() = 4;
    delayBlock.trigger();
    REQUIRE(delayBlock.o<0>() == Approx(3));

    delayBlock2.clear(0);
    delayBlock2.i<0>() = 2;

    REQUIRE(delayBlock2.o<0>() == 0);

    delayBlock2.trigger();
    REQUIRE(delayBlock2.o<0>() == Approx(0));

    delayBlock2.i<0>() = 1;
    delayBlock2.trigger();
    REQUIRE(delayBlock2.o<0>() == Approx(0));

    delayBlock2.i<0>() = 3;
    delayBlock2.trigger();
    REQUIRE(delayBlock2.o<0>() == Approx(2));

    delayBlock2.i<0>() = 4;
    delayBlock2.trigger();
    REQUIRE(delayBlock2.o<0>() == Approx(1));
}