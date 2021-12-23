//
// Created by Hamza El-Kebir on 12/23/21.
//

#include "catchOnce.hpp"
#include "aux/DynamicData.hpp"


TEST_CASE("DynamicData", "[aux]") {
    std::string abc = "abcdef";
    ls::aux::DynamicData dd{abc};

    REQUIRE(dd.data.is<std::string>());
    REQUIRE(dd.data.as<std::string>() == abc);
}