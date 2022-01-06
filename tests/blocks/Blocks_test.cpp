//
// Created by Hamza El-Kebir on 12/23/21.
//

#include "catchOnce.hpp"
#include "Lodestar/blocks/std/ConstantBlock.hpp"
#include "Lodestar/blocks/std/ConverterBlock.hpp"
#include "Lodestar/blocks/std/GainBlock.hpp"
#include "Lodestar/blocks/std/SignumBlock.hpp"
#include "Lodestar/blocks/std/SumBlock.hpp"
#include "Lodestar/blocks/BlockUtilities.hpp"
#include <vector>

TEST_CASE("Blocks", "[blocks][block]")
{
    ls::blocks::std::ConstantBlock<double> blk0{3};
    ls::blocks::std::GainBlock<double> blk1{6};
    ls::blocks::std::SignumBlock<double> blk2;
    ls::blocks::std::ConverterBlock<int, double> blk3;
    ls::blocks::std::SumBlock<double, 2> blk4;

    REQUIRE(blk0.id < blk1.id);
    REQUIRE(blk1.id < blk2.id);
    REQUIRE(blk2.id < blk3.id);
    REQUIRE(blk3.id < blk4.id);

    connect(blk0.o<0>(), blk1.i<0>());
    connect(blk1.o<0>(), blk2.i<0>());
    connect(blk1.o<0>(), blk4.i<0>());
    connect(blk2.o<0>(), blk3.i<0>());
    connect(blk3.o<0>(), blk4.i<1>());

    std::vector<ls::blocks::BlockProto*> blks{&blk0, &blk1, &blk2, &blk3, &blk4};

    for (auto &blk : blks)
        blk->trigger();

    REQUIRE(blk4.o<0>() == Approx(18 + 1));

    blk0.constant() = 4;
    blk1.gain() = -5;

    for (auto &blk : blks)
        blk->trigger();

    REQUIRE(blk4.o<0>() == Approx(-20 - 1));
}