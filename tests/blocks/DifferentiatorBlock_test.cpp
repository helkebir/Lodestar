//
// Created by Hamza El-Kebir on 2/24/22.
//

#include "catchOnce.hpp"
#include <Lodestar/blocks/std/DifferentiatorBlock.hpp>
#include <cmath>

//TEST_CASE("DifferentiatorBlock", "[blocks][std]")
//{
//    ls::blocks::std::DifferentiatorBlock<float, 7> diffBlock;
//
//    diffBlock.clear(0);
//    diffBlock.samplingPeriod() = 1;
//
//    diffBlock.i<0>() = 0;
//    diffBlock.trigger();
//    diffBlock.i<0>() = 1.f/7.f;
//    diffBlock.trigger();
//
//    REQUIRE(diffBlock.o<0>().object == Approx(1.0/7.0));
//
//    diffBlock.clear(0);
//    diffBlock.samplingPeriod() = 1;
//
//    diffBlock.i<0>() = 0;
//    diffBlock.trigger();
//    diffBlock.i<0>() = 1;
//    diffBlock.trigger();
//    diffBlock.i<0>() = 4;
//    diffBlock.trigger();
//
//    REQUIRE(diffBlock.o<0>().object == Approx(2));
//
//    diffBlock.clear(0);
//    diffBlock.samplingPeriod() = 1;
//
//    diffBlock.i<0>() = 0;
//    diffBlock.trigger();
//    diffBlock.i<0>() = 1;
//    diffBlock.trigger();
//    diffBlock.i<0>() = 8;
//    diffBlock.trigger();
//    diffBlock.i<0>() = 27;
//    diffBlock.trigger();
//
//    REQUIRE(diffBlock.o<0>().object == Approx(6));
//
//    diffBlock.clear(0);
//    diffBlock.samplingPeriod() = 0.5;
//
//    diffBlock.i<0>() = pow(-2.0, 6.0) / 7.0;
//    diffBlock.trigger();
//    diffBlock.i<0>() = pow(-1.5, 6.0) / 7.0;
//    diffBlock.trigger();
//    diffBlock.i<0>() = pow(-1.0, 6.0) / 7.0;
//    diffBlock.trigger();
//    diffBlock.i<0>() = pow(-0.5, 6.0) / 7.0;
//    diffBlock.trigger();
//    diffBlock.i<0>() = pow(0.0, 6.0) / 7.0;
//    diffBlock.trigger();
//    diffBlock.i<0>() = pow(0.5, 6.0) / 7.0;
//    diffBlock.trigger();
//    diffBlock.i<0>() = pow(1.0, 6.0) / 7.0;
//    diffBlock.trigger();
//
//    REQUIRE(diffBlock.o<0>().object == Approx(6.0/7.0));
//}