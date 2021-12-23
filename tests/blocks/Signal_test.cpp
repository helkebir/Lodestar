//
// Created by Hamza El-Kebir on 12/23/21.
//

#include "catchOnce.hpp"
#include "blocks/Signal.hpp"

TEST_CASE("Signal", "[blocks][signal]") {
    ls::blocks::Signal<int> s1{2};
    ls::blocks::Signal<double> s2{3.1415};
    ls::blocks::Signal<std::string> s3{"abc"};
    ls::blocks::Signal<char> s4{'a'};

    REQUIRE(ls::blocks::Signal<>::isSignal<ls::blocks::Signal<float>>());
    REQUIRE(!ls::blocks::Signal<>::isSignal<float>());
    REQUIRE(s1.id() < s2.id());
    REQUIRE(s2.id() < s3.id());
    REQUIRE(s3.id() < s4.id());

    std::string abc = "abcdef";
    ls::blocks::Signal<ls::aux::DynamicData> s5{ls::aux::DynamicData{abc}};
    REQUIRE(s5.isDynamicData());
    REQUIRE(s5.isType<std::string>());
    REQUIRE(!s5.isType<float>());
    REQUIRE(s4.id() < s5.id());

    // TODO: Add arithmetic and assignment unit tests.
}