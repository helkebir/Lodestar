//
// Created by Hamza El-Kebir on 12/25/21.
//

#include "catchOnce.hpp"
#include "blocks/std/ConstantBlock.hpp"
#include "blocks/std/ConverterBlock.hpp"
#include "blocks/std/GainBlock.hpp"
#include "blocks/std/SignumBlock.hpp"
#include "blocks/std/SumBlock.hpp"
#include "blocks/BlockUtilities.hpp"
#include "blocks/BlockPack.hpp"

TEST_CASE("BlockPack", "[blocks]")
{
    ls::blocks::std::ConstantBlock<double> blk0{3};
    ls::blocks::std::GainBlock<double> blk1{6};
    ls::blocks::std::SignumBlock<double> blk2;
    ls::blocks::std::ConverterBlock<int, double> blk3;
    ls::blocks::std::SumBlock<double, 2> blk4;

    ls::blocks::BlockPack bp(blk0, blk1, blk2, blk3, blk4);

    REQUIRE(bp.blocks.size() == 5);
    REQUIRE(bp.blockTraits.size() == 5);

    REQUIRE((bp.blockTraits[0].blockType == ls::blocks::BlockType::ConstantBlock));
    REQUIRE((bp.blockTraits[1].blockType == ls::blocks::BlockType::GainBlock));
    REQUIRE((bp.blockTraits[2].blockType == ls::blocks::BlockType::SignumBlock));
    REQUIRE((bp.blockTraits[3].blockType == ls::blocks::BlockType::ConverterBlock));
    REQUIRE((bp.blockTraits[4].blockType == ls::blocks::BlockType::SumBlock));
}