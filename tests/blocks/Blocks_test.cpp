//
// Created by Hamza El-Kebir on 12/23/21.
//

#include "catchOnce.hpp"
#include "blocks/std/ConstantBlock.hpp"
#include "blocks/std/GainBlock.hpp"
#include "blocks/std/SignumBlock.hpp"
#include "blocks/std/SumBlock.hpp"
#include "blocks/BlockUtilities.hpp"
#include <vector>

TEST_CASE("Blocks", "[blocks][block]")
{
    ls::blocks::std::ConstantBlock<double> blk0{3};
    ls::blocks::std::GainBlock<double> blk1{6};
    ls::blocks::std::SignumBlock<double, double> blk2;
    ls::blocks::std::SumBlock<double, 2> blk3;

    connect(blk0.o<0>(), blk1.i<0>());
    connect(blk1.o<0>(), blk2.i<0>());
    connect(blk1.o<0>(), blk3.i<0>());
    connect(blk2.o<0>(), blk3.i<1>());

    std::vector<ls::blocks::BlockProto*> blks{&blk0, &blk1, &blk2, &blk3};

    for (auto &blk : blks)
        blk->trigger();

    REQUIRE(blk3.o<0>() == Approx(18 + 1));

    blk0.constant() = 4;
    blk1.gain() = -5;

    for (auto &blk : blks)
        blk->trigger();

    REQUIRE(blk3.o<0>() == Approx(-20 - 1));
}