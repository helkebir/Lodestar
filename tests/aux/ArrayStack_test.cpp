//
// Created by Hamza El-Kebir on 6/15/21.
//

#include "catchOnce.hpp"
#include "Lodestar/aux/ArrayStack.hpp"

TEST_CASE("ArrayStack init", "[aux][static]") {
    auto a = ls::aux::ArrayStack<double, 5>{};

    REQUIRE(a.size() == 0);
    REQUIRE(a.max_size() == 5);

    auto aZero = ls::aux::ArrayStack<double, 5>::zero();

    REQUIRE(aZero.size() == 5);
    REQUIRE(aZero.max_size() == 5);
    REQUIRE(aZero.front() == 0);
    REQUIRE(aZero.back() == 0);

    aZero[0] = 1;
    aZero[1] = 2;
    aZero[2] = 3;

    REQUIRE(aZero.front() == 1);

    aZero.pop_front();
    REQUIRE(aZero.size() == 4);
    REQUIRE(aZero[0] == 2);
    REQUIRE(aZero[1] == 3);
}