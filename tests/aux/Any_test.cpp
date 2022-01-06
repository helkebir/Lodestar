//
// Created by Hamza El-Kebir on 12/23/21.
//

#include "catchOnce.hpp"
#include "Lodestar/aux/Any.hpp"


TEST_CASE("Any", "[aux]") {
    std::string abc = "abcdef";
    ls::aux::Any<int, double, char, std::string> any(abc);

    REQUIRE(any.is<std::string>());
    REQUIRE(!any.is<int>());
}