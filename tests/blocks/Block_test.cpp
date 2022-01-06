//
// Created by Hamza El-Kebir on 12/23/21.
//

#include "catchOnce.hpp"
#include "Lodestar/blocks/Block.hpp"

using namespace ls::blocks;
using namespace ls::aux;

TEST_CASE("Block", "[blocks][block]")
{
    typedef Block<std::tuple<int, bool, Signal<char>, Signal<DynamicData>>, std::tuple<bool, int>, BlockProto::empty> CustomBlock;

    SECTION("Automatic Signal<T> wrapping") {
        REQUIRE(std::is_same<typename std::tuple_element<0, CustomBlock::Inputs>::type, Signal<int>>::value);
        REQUIRE(std::is_same<typename std::tuple_element<1, CustomBlock::Inputs>::type, Signal<bool>>::value);
        REQUIRE(std::is_same<typename std::tuple_element<2, CustomBlock::Inputs>::type, Signal<char>>::value);
        REQUIRE(std::is_same<typename std::tuple_element<3, CustomBlock::Inputs>::type, Signal<DynamicData>>::value);

        REQUIRE(std::is_same<typename std::tuple_element<0, CustomBlock::Outputs>::type, Signal<bool>>::value);
        REQUIRE(std::is_same<typename std::tuple_element<1, CustomBlock::Outputs>::type, Signal<int>>::value);
    }

    SECTION("CustomBlock definition") {
        CustomBlock b{};

        REQUIRE(!b.i<0>().isDynamicData());
        REQUIRE(b.i<0>().isType<int>());

        REQUIRE(!b.i<1>().isDynamicData());
        REQUIRE(b.i<1>().isType<bool>());

        REQUIRE(!b.i<2>().isDynamicData());
        REQUIRE(b.i<2>().isType<char>());

        REQUIRE(b.i<3>().isDynamicData());
        REQUIRE(!b.i<3>().isType<long>());

        REQUIRE(decltype(b)::kIns == 4);
        REQUIRE(decltype(b)::kOuts == 2);
        REQUIRE(decltype(b)::kPars == 0);

        b.equation = [](CustomBlock & b) {
            b.o<0>() = b.i<1>();
            b.o<1>() = b.i<0>();
        };

        b.i<0>() = 42;
        b.i<1>() = false;

        b.trigger();

        REQUIRE(b.o<0>().object == b.i<1>().object);
        REQUIRE(b.o<1>().object == b.i<0>().object);
    }
}