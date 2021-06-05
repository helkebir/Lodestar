//
// Created by Hamza El-Kebir on 5/27/21.
//

#ifndef LODESTAR_BLOCK_TEST_HPP
#define LODESTAR_BLOCK_TEST_HPP

#include "catchOnce.hpp"
#include "block/Block.hpp"

TEST_CASE("Block connection", "[block][static]") {
    typedef Block<std::tuple<double, int, char>, std::tuple<bool, char>, 10> TDCustomBlock;
    typedef Block<std::tuple<bool, char>, std::tuple<double, int, char>, 10> TDCustomBlockReverse;

    TDCustomBlock block{};
    TDCustomBlockReverse block1{};

    block.connect(block1);
}

#endif //LODESTAR_BLOCK_TEST_HPP
