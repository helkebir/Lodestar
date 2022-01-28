//
// Created by Hamza El-Kebir on 12/25/21.
//

#include "catchOnce.hpp"
#include "Lodestar/blocks/aux/StronglyConnectedComponents.hpp"
#include "Lodestar/blocks/std/ConstantBlock.hpp"
#include "Lodestar/blocks/std/GainBlock.hpp"
#include "Lodestar/blocks/std/SumBlock.hpp"
#include "Lodestar/blocks/BlockUtilities.hpp"
#include "Lodestar/blocks/BlockPack.hpp"

TEST_CASE("StronglyConnectedComponents", "[blocks][aux]")
{
    ls::blocks::aux::DirectedGraph graph(7);
    graph.connect(0, 1);
    graph.connect(1, 2);
    graph.connect(2, 4);
    graph.connect(4, 1);
    graph.connect(2, 6);
    graph.connect(6, 5);
    graph.connect(5, 3);
    /*
     *                      +---6--v
     * 0 -----> 1 ----> 2 --+----->5-----> 3
     *          ^       |
     *          +---4<--+
     */

    auto components = ls::blocks::aux::StronglyConnectedComponents::findComponents(
            graph);

    bool has1 = false;
    bool has2 = false;
    bool has4 = false;

    for (auto &component: components) {
        for (auto id: component) {
            if (id == 1) has1 = true;
            if (id == 2) has2 = true;
            if (id == 4) has4 = true;
        }
    }

    bool verdict = (has1 && has2 && has4);

    REQUIRE(verdict);
}

TEST_CASE("StronglyConnectedComponents applied", "[blocks][aux]")
{
    auto blkConst = ls::blocks::std::ConstantBlock<double>{3};
    auto blkConst2 = ls::blocks::std::ConstantBlock<double>{1};
    auto blkSum = ls::blocks::std::SumBlock<double, 3>{};
    auto blkGain = ls::blocks::std::GainBlock<double>{2};
    auto blkGain2 = ls::blocks::std::GainBlock<double>{4};

    connect(blkConst.o<0>(), blkSum.i<0>());
    connect(blkConst2.o<0>(), blkSum.i<1>());
    connect(blkSum.o<0>(), blkGain.i<0>());
    connect(blkGain.o<0>(), blkSum.i<2>());
    connect(blkGain.o<0>(), blkGain2.i<0>());
    /*
     *          c2
     *          |
     * c1       v s     g1     g2
     * 0 -----> 2 ----> 3 ---->4
     *          ^       |
     *          +-------+
     */

    ls::blocks::BlockPack bp(blkConst, blkConst2, blkSum, blkGain, blkGain2);

    auto graph = ls::blocks::aux::DirectedGraph::fromBlocks(bp.blocks);

    auto components =
            ls::blocks::aux::StronglyConnectedComponents::findComponents(graph);

    bool hasSum = false;
    bool hasGain = false;

    for (auto &component: components) {
        for (auto id: component) {
            if (id == blkSum.id) hasSum = true;
            if (id == blkGain.id) hasGain = true;
        }
    }

    bool verdict = (hasSum && hasGain);

    REQUIRE(verdict);

    auto contains = [](const ::std::vector<int> &v, int val) -> bool {
        return (std::find(v.begin(), v.end(), val) != v.end());
    };

    auto containsBlock = [](const ::std::vector<ls::blocks::BlockProto *> &v, ls::blocks::BlockProto * val) -> bool {
        return (std::find(v.begin(), v.end(), val) != v.end());
    };

    ::std::vector<ls::blocks::BlockProto *> externalInputs, externalOutputs;

    for (auto id: components[0]) {
        for (auto inputs : bp.blockById[id]->inputPointers)
            for (auto inputSlot : inputs->connectionPtrs)
                if (contains(components[0], inputSlot->blockId))
                    continue;
                else if (bp.getBlockById(inputSlot->blockId) != nullptr)
                    if (!containsBlock(externalInputs, bp.getBlockById(inputSlot->blockId)))
                        externalInputs.push_back(bp.getBlockById(inputSlot->blockId));

        for (auto outputs : bp.blockById[id]->outputPointers)
            for (auto outputSlot : outputs->connectionPtrs)
                if (contains(components[0], outputSlot->blockId))
                    continue;
                else if (bp.getBlockById(outputSlot->blockId) != nullptr)
                    if (!containsBlock(externalOutputs, bp.getBlockById(outputSlot->blockId)))
                        externalOutputs.push_back(bp.getBlockById(outputSlot->blockId));
    }

    REQUIRE(externalInputs.size() == 2);
    REQUIRE(externalInputs[0]->id == blkConst.id);
    REQUIRE(externalInputs[1]->id == blkConst2.id);

    REQUIRE(externalOutputs.size() == 1);
    REQUIRE(externalOutputs[0]->id == blkGain2.id);
}