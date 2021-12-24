//
// Created by Hamza El-Kebir on 12/23/21.
//

#include "catchOnce.hpp"
#include "blocks/std/SwitchBlock.hpp"

TEST_CASE("SwitchBlocks", "[blocks][std]")
{
    SECTION("Parameteric input") {
        ls::blocks::std::SwitchBlock<double> sb;

        sb.i<0>() = 3;
        sb.i<1>() = 7;
        sb.trigger();

        REQUIRE(sb.o<0>() == Approx(3));

        sb.toggle();
        sb.trigger();

        REQUIRE(sb.o<0>() == Approx(7));
    }

    SECTION("Additional input") {
        ls::blocks::std::SwitchBlock<double, ls::blocks::std::SwitchBlockParameter::AdditionalInput> sb;

        sb.i<0>() = 3;
        sb.i<1>() = 7;
        sb.trigger();

        REQUIRE(sb.o<0>() == Approx(3));

        sb.i<2>() = true;
        sb.trigger();

        REQUIRE(sb.o<0>() == Approx(7));
    }
}