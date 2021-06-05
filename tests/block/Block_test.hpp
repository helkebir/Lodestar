//
// Created by Hamza El-Kebir on 5/27/21.
//

#ifndef LODESTAR_BLOCK_TEST_HPP
#define LODESTAR_BLOCK_TEST_HPP

#include "catchOnce.hpp"
#include "block/Block.hpp"

TEST_CASE("Block connection", "[block][static]") {
    typedef ls::block::Block<std::tuple<double, int, char>, std::tuple<bool, char>, 10> TDCustomBlock;
    typedef ls::block::Block<std::tuple<bool, char>, std::tuple<double, int, char>, 10> TDCustomBlockReverse;

    TDCustomBlock block{};
    TDCustomBlockReverse block1{};

    SECTION("Set input") {
        block.setInput<0>(2.2);
        REQUIRE(block.getInput<0>() == Approx(2.2));
    }

    SECTION("Set output") {
        block.setOutput<0>(true);
        REQUIRE(block.getOutput<0>() == true);
    }

    SECTION("Callback") {
        std::function<LS_CB_RETURN_TYPE(int)> cbI1_0 = [&block] (int i1) {
            if (i1 > 0) {
                block.setOutput<0>(true);
                block.setOutput<1>('p');
            } else if (i1 == 0) {
                block.setOutput<0>(true);
                block.setOutput<1>('z');
            } else {
                block.setOutput<0>(false);
                block.setOutput<1>('n');
            }

            return true;
        };

        block.setInputCallback<1, 0>(cbI1_0);

        block.setInput<1>(2);
        REQUIRE(block.getOutput<0>() == true);
        REQUIRE(block.getOutput<1>() == 'p');

        block.setInput<1>(0);
        REQUIRE(block.getOutput<0>() == true);
        REQUIRE(block.getOutput<1>() == 'z');

        block.setInput<1>(-3);
        REQUIRE(block.getOutput<0>() == false);
        REQUIRE(block.getOutput<1>() == 'n');

        block.setInputCallback<1, 0>(decltype(cbI1_0){});
        block.setInput<1>(0);
        REQUIRE(block.getOutput<0>() == false);
        REQUIRE(block.getOutput<1>() == 'n');
    }

    SECTION("Callback alternative signature") {
        std::function<LS_CB_RETURN_TYPE(int)> cbI1_0 = [&block] (int i1) {
            if (i1 > 0) {
                block.setOutput<0>(true);
                block.setOutput<1>('p');
            } else if (i1 == 0) {
                block.setOutput<0>(true);
                block.setOutput<1>('z');
            } else {
                block.setOutput<0>(false);
                block.setOutput<1>('n');
            }

            return true;
        };

        block.setInputCallback<1>(cbI1_0, 0);

        block.setInput<1>(2);
        REQUIRE(block.getOutput<0>() == true);
        REQUIRE(block.getOutput<1>() == 'p');

        block.setInput<1>(0);
        REQUIRE(block.getOutput<0>() == true);
        REQUIRE(block.getOutput<1>() == 'z');

        block.setInput<1>(-3);
        REQUIRE(block.getOutput<0>() == false);
        REQUIRE(block.getOutput<1>() == 'n');

        block.setInputCallback<1>(decltype(cbI1_0){}, 0);
        block.setInput<1>(0);
        REQUIRE(block.getOutput<0>() == false);
        REQUIRE(block.getOutput<1>() == 'n');
    }

    SECTION("Disconnect") {
        block.connect(block1);
        block.setOutput<1>('a');
        block.disconnect(block1);
        block.setOutput<1>('b');

        REQUIRE(block1.getInput<1>() == 'a');
    }
}

#endif //LODESTAR_BLOCK_TEST_HPP
