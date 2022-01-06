//
// Created by Hamza El-Kebir on 6/15/21.
//

#include "catchOnce.hpp"
#include "Lodestar/filter/SimpleMovingAverage.hpp"

TEST_CASE("SimpleMovingAverage", "[filter][static]") {
    ls::filter::SimpleMovingAverage<double, 5> sma;

    REQUIRE(sma.average() == 0);
    sma.push(1);
    REQUIRE(sma.average() == 1);
    sma.push(3);
    REQUIRE(sma.average() == 2);
    sma.push(4);
    REQUIRE(sma.average() == Approx(8.0/3));
    REQUIRE(sma.size() == 3);

    sma.clear();
    REQUIRE(sma.size() == 0);
    REQUIRE(sma.average() == 0);
}