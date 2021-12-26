//
// Created by Hamza El-Kebir on 12/25/21.
//

#include "catchOnce.hpp"
#include "blocks/aux/StronglyConnectedComponents.hpp"
#include "blocks/std/ConstantBlock.hpp"
#include "blocks/std/GainBlock.hpp"
#include "blocks/std/SumBlock.hpp"
#include "blocks/BlockUtilities.hpp"

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
    auto blkSum = ls::blocks::std::SumBlock<double, 2>{};
    auto blkGain = ls::blocks::std::GainBlock<double>{2};
    auto blkGain2 = ls::blocks::std::GainBlock<double>{4};

    connect(blkConst.o<0>(), blkSum.i<0>());
    connect(blkSum.o<0>(), blkGain.i<0>());
    connect(blkGain.o<0>(), blkSum.i<1>());
    connect(blkGain.o<0>(), blkGain2.i<0>());
    /*
     * c        s       g1     g2
     * 0 -----> 1 ----> 2 ---->3
     *          ^       |
     *          +-------+
     */

    std::vector<ls::blocks::BlockProto *> blks = {&blkConst, &blkSum, &blkGain,
                                                  &blkGain2};

    auto graph = ls::blocks::aux::DirectedGraph::fromBlocks(blks);

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
}