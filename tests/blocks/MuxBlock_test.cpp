//
// Created by Hamza El-Kebir on 12/23/21.
//

#include "catchOnce.hpp"
#include "blocks/std/MuxBlock.hpp"


TEST_CASE("MuxBlock", "[blocks][std]")
{
    SECTION("Matrix") {
        ls::blocks::std::MuxBlock<Eigen::Matrix<double, 2, 2>> cb;

        cb.i<0>() = 1;
        cb.i<1>() = 2;
        cb.i<2>() = 3;
        cb.i<3>() = 4;
        cb.trigger();

        REQUIRE(cb.o<0>().object(0, 0) == 1);
        REQUIRE(cb.o<0>().object(1, 0) == 2);
        REQUIRE(cb.o<0>().object(0, 1) == 3);
        REQUIRE(cb.o<0>().object(1, 1) == 4);
    }

    SECTION("Vector") {
        ls::blocks::std::MuxBlock<Eigen::Vector2d> cb;

        cb.i<0>() = 1;
        cb.i<1>() = 2;
        cb.trigger();

        REQUIRE(cb.o<0>().object(0) == 1);
        REQUIRE(cb.o<0>().object(1) == 2);
    }

    SECTION("Tuple") {
        ls::blocks::std::MuxBlock<::std::tuple<int, bool, char>> cb;

        cb.i<0>() = 1;
        cb.i<1>() = true;
        cb.i<2>() = 'a';
        cb.trigger();

        REQUIRE(::std::get<0>(cb.o<0>().object) == 1);
        REQUIRE(::std::get<1>(cb.o<0>().object));
        REQUIRE(::std::get<2>(cb.o<0>().object) == 'a');
    }
}