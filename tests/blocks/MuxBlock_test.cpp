//
// Created by Hamza El-Kebir on 12/23/21.
//

#include "catchOnce.hpp"
#include "blocks/std/MuxBlock.hpp"


TEST_CASE("MuxBlock", "[blocks][std]")
{
    SECTION("Matrix row major") {
        ls::blocks::std::MuxBlock<Eigen::Matrix<double, 2, 2>> mb;

        mb.i<0>() = 1;
        mb.i<1>() = 2;
        mb.i<2>() = 3;
        mb.i<3>() = 4;
        mb.trigger();

        REQUIRE(mb.o<0>().object(0, 0) == 1);
        REQUIRE(mb.o<0>().object(0, 1) == 2);
        REQUIRE(mb.o<0>().object(1, 0) == 3);
        REQUIRE(mb.o<0>().object(1, 1) == 4);
    }

    SECTION("Matrix col major") {
        ls::blocks::std::MuxBlock<Eigen::Matrix<double, 2, 2>, ls::blocks::std::MuxBlockOperator::ColMajor> mb;

        mb.i<0>() = 1;
        mb.i<1>() = 2;
        mb.i<2>() = 3;
        mb.i<3>() = 4;
        mb.trigger();

        REQUIRE(mb.o<0>().object(0, 0) == 1);
        REQUIRE(mb.o<0>().object(1, 0) == 2);
        REQUIRE(mb.o<0>().object(0, 1) == 3);
        REQUIRE(mb.o<0>().object(1, 1) == 4);
    }

    SECTION("Vector standard accessors") {
        ls::blocks::std::MuxBlock<Eigen::Vector2d> mb;

        mb.i<0>() = 1;
        mb.i<1>() = 2;
        mb.trigger();

        REQUIRE(mb.o<0>().object(0) == 1);
        REQUIRE(mb.o<0>().object(1) == 2);
    }

    SECTION("Vector alias accessors") {
        ls::blocks::std::MuxBlock<Eigen::Vector2d> mb;

        mb.x() = 1;
        mb.y() = 2;
        mb.trigger();

        REQUIRE(mb.o<0>().object(0) == 1);
        REQUIRE(mb.o<0>().object(1) == 2);
    }

    SECTION("Tuple") {
        ls::blocks::std::MuxBlock<::std::tuple<int, bool, char>> mb;

        mb.i<0>() = 1;
        mb.i<1>() = true;
        mb.i<2>() = 'a';
        mb.trigger();

        REQUIRE(::std::get<0>(mb.o<0>().object) == 1);
        REQUIRE(::std::get<1>(mb.o<0>().object));
        REQUIRE(::std::get<2>(mb.o<0>().object) == 'a');
    }
}