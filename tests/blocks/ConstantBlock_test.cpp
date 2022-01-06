//
// Created by Hamza El-Kebir on 12/23/21.
//

#include "catchOnce.hpp"
#include "Lodestar/blocks/std/ConstantBlock.hpp"


TEST_CASE("ConstantBlock", "[blocks][std]")
{
    ls::blocks::std::ConstantBlock<double> cb(3);

    REQUIRE(cb.constant() == Approx(3));
    REQUIRE(cb.p<0>() == Approx(3));

    cb.trigger();

    REQUIRE(cb.o<0>().object == Approx(3));

    cb.constant() = 6;
    cb.trigger();

    REQUIRE(cb.o<0>().object == Approx(6));
}