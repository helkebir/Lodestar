//
// Created by Hamza El-Kebir on 12/23/21.
//

#include "catchOnce.hpp"
#include "blocks/std/ConverterBlock.hpp"


TEST_CASE("ConverterBlock", "[blocks][std]")
{
    ls::blocks::std::ConverterBlock<char, int> cb;

    cb.i<0>() = 'a';
    cb.trigger();

    REQUIRE(cb.o<0>() == 97);
}