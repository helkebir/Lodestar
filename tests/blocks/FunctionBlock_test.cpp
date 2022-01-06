//
// Created by Hamza El-Kebir on 12/23/21.
//

#include "catchOnce.hpp"
#include "Lodestar/blocks/std/FunctionBlock.hpp"


TEST_CASE("FunctionBlock", "[blocks][std]")
{
    std::function<std::string(bool, bool)> f = [](bool a, bool upper) -> std::string {
        if (upper) {
            if (a) return "TRUE";
            else return "FALSE";
        }

        if (a) return "true";
        else return "false";
    };

    auto fb = ls::blocks::std::FunctionBlock<>::make(f);

    REQUIRE(decltype(fb)::kIns == 2);
    REQUIRE(decltype(fb)::kOuts == 1);
    REQUIRE(decltype(fb)::kPars == 1);

    fb.i<0>() = true;
    fb.i<1>() = false;
    fb.trigger();
    REQUIRE(fb.o<0>().object == "true");

    fb.i<0>() = false;
    fb.trigger();
    REQUIRE(fb.o<0>().object == "false");

    fb.i<0>() = true;
    fb.i<1>() = true;
    fb.trigger();
    REQUIRE(fb.o<0>().object == "TRUE");

    fb.i<0>() = false;
    fb.trigger();
    REQUIRE(fb.o<0>().object == "FALSE");
}