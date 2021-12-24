//
// Created by Hamza El-Kebir on 12/23/21.
//

#include "catchOnce.hpp"
#include "blocks/std/ReImToComplexBlock.hpp"


TEST_CASE("ReImToComplexBlock", "[blocks][std]")
{
    ls::blocks::std::ReImToComplexBlock<double> ricb;

    SECTION("Standard accessors") {
        ricb.i<0>() = 5;
        ricb.i<1>() = 7;

        ricb.trigger();

        REQUIRE(ricb.o<0>().object.real() == Approx(5));
        REQUIRE(ricb.o<0>().object.imag() == Approx(7));
    }

    SECTION("Alias accessors") {
        ricb.real(5);
        ricb.imag(7);

        ricb.trigger();

        REQUIRE(ricb.o<0>().object.real() == Approx(5));
        REQUIRE(ricb.o<0>().object.imag() == Approx(7));
    }
}

TEST_CASE("ReImToComplexBlock vector", "[blocks][std]")
{
    ls::blocks::std::ReImToComplexBlock<Eigen::Vector2d> ricb;

    Eigen::Vector2d v1, v2;
    v1 << 1, 2;
    v2 << 3, 4;

    SECTION("Standard accessors") {
        ricb.i<0>() = v1;
        ricb.i<1>() = v2;

        ricb.trigger();

        REQUIRE((ricb.o<0>().object.real() - v1).isZero());
        REQUIRE((ricb.o<0>().object.imag() - v2).isZero());
    }

    SECTION("Alias accessors") {
        ricb.real(v1);
        ricb.imag(v2);

        ricb.trigger();

        REQUIRE((ricb.o<0>().object.real() - v1).isZero());
        REQUIRE((ricb.o<0>().object.imag() - v2).isZero());
    }
}