//
// Created by Hamza El-Kebir on 12/23/21.
//

#include "catchOnce.hpp"
#include "blocks/std/GainBlock.hpp"


TEST_CASE("GainBlock", "[blocks][std]")
{
    ls::blocks::std::GainBlock<double> gb{};

    gb.i<0>() = 2;
    gb.setGain(3);
    gb.trigger();

    REQUIRE(gb.o<0>() == Approx(6));
}