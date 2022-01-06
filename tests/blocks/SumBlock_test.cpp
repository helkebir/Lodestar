//
// Created by Hamza El-Kebir on 12/23/21.
//

#include "catchOnce.hpp"
#include "Lodestar/blocks/std/SumBlock.hpp"


TEST_CASE("SumBlock", "[blocks][std]")
{
    ls::blocks::std::SumBlock<double, 3> sb{};
    sb.i<0>() = 2.4;
    sb.i<1>() = 3;
    sb.i<2>() = 3.2;

    SECTION("Default settings") {
        sb.trigger();

        REQUIRE(sb.o<0>() == Approx(2.4 + 3 + 3.2));
    }

    SECTION("Set operators") {
        sb.setOperators(decltype(sb)::Minus,
                        decltype(sb)::Plus,
                        decltype(sb)::Plus);
        sb.trigger();

        REQUIRE(sb.o<0>() == Approx(-2.4 + 3 + 3.2));
    }

    SECTION("Set superset of operators") {
        sb.setOperators(decltype(sb)::Minus,
                        decltype(sb)::Plus,
                        decltype(sb)::Plus,
                        decltype(sb)::Minus);
        sb.trigger();

        REQUIRE(sb.o<0>() == Approx(-2.4 + 3 + 3.2));
    }

    SECTION("Set subset of operators") {
        sb.setOperators(decltype(sb)::Plus,
                        decltype(sb)::Minus);
        sb.trigger();

        REQUIRE(sb.o<0>() == Approx(2.4 - 3 + 3.2));
    }

}