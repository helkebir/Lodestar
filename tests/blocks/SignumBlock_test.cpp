//
// Created by Hamza El-Kebir on 12/23/21.
//

#include "catchOnce.hpp"
#include "blocks/std/SignumBlock.hpp"


TEST_CASE("SignumBlock", "[blocks][std]")
{
    ls::blocks::std::SignumBlock<double> sb{};

    sb.i<0>() = 2;
    sb.trigger();

    REQUIRE(sb.isPositive());

    sb.i<0>() = -3;
    sb.trigger();

    REQUIRE(sb.isNegative());

    sb.i<0>() = 0;
    sb.trigger();

    REQUIRE(sb.isZero());
}