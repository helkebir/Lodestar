//
// Created by Hamza El-Kebir on 12/23/21.
//

#include "catchOnce.hpp"
#include "blocks/std/DemuxBlock.hpp"
#include <iostream>


TEST_CASE("DemuxBlock", "[blocks][std]")
{
    SECTION("Matrix row major") {
        ls::blocks::std::DemuxBlock<Eigen::Matrix<double, 2, 2>> db;

        Eigen::Matrix<double, 2, 2> m;
        m << 1, 2, 3, 4;

        db.i<0>() = m;
        db.trigger();

        REQUIRE(db.o<0>() == 1);
        REQUIRE(db.o<1>() == 2);
        REQUIRE(db.o<2>() == 3);
        REQUIRE(db.o<3>() == 4);
    }

    SECTION("Matrix col major") {
        ls::blocks::std::DemuxBlock<Eigen::Matrix<double, 2, 2>, ls::blocks::std::DemuxBlockOperator::ColMajor> db;

        Eigen::Matrix<double, 2, 2> m;
        m << 1, 2, 3, 4;

        db.i<0>() = m;
        db.trigger();

        REQUIRE(db.o<0>() == 1);
        REQUIRE(db.o<1>() == 3);
        REQUIRE(db.o<2>() == 2);
        REQUIRE(db.o<3>() == 4);
    }

    SECTION("Vector") {
        ls::blocks::std::DemuxBlock<Eigen::Vector2d> db;

        Eigen::Vector2d v;
        v << 1, 2;

        db.i<0>() = v;
        db.trigger();

        REQUIRE(db.o<0>() == 1);
        REQUIRE(db.o<1>() == 2);
    }

    SECTION("Tuple") {
        ls::blocks::std::DemuxBlock<::std::tuple<int, bool, char>> db;

        auto t = std::make_tuple(1, true, 'a');
        db.i<0>() = t;
        db.trigger();

        REQUIRE(db.o<0>() == 1);
        REQUIRE(db.o<1>().object);
        REQUIRE(db.o<2>() == 'a');
    }
}