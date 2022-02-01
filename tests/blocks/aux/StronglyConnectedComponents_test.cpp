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

    auto components =
            ls::blocks::aux::StronglyConnectedComponents::findComponents(graph);

    bool has1 = false;
    bool has2 = false;
    bool has4 = false;

    for (auto &component: components.components) {
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

    REQUIRE(components.components.size() == 1);
    REQUIRE(components.isAlgebraicLoop(bp, 0));
    REQUIRE(components.containsAlgebraicLoops(bp));

    bool hasSum = false;
    bool hasGain = false;

    for (auto &component: components.components) {
        for (auto id: component) {
            if (id == blkSum.id) hasSum = true;
            if (id == blkGain.id) hasGain = true;
        }
    }

    bool verdict = (hasSum && hasGain);

    REQUIRE(verdict);

    auto externalIO = components.getExternalIO(bp, 0);

    REQUIRE(externalIO.first.size() == 2);
    REQUIRE(((externalIO.first[0].src->id == blkConst.id && externalIO.first[1].src->id == blkConst2.id) ||
             (externalIO.first[1].src->id == blkConst.id && externalIO.first[2].src->id == blkConst2.id)));

    REQUIRE(externalIO.second.size() == 1);
    REQUIRE(externalIO.second[0].dst->id == blkGain2.id);

    auto internalIO = components.getInternalIO(bp, 0);

    REQUIRE(internalIO.size() == 2);
    REQUIRE(((internalIO[0].src->id == blkSum.id && internalIO[1].src->id == blkGain.id) ||
             (internalIO[1].src->id == blkSum.id && internalIO[0].src->id == blkGain.id)));
}

TEST_CASE("StronglyConnectedComponents applied 2", "[blocks][aux]")
{
    auto blkConst = ls::blocks::std::ConstantBlock<double>{3};
    auto blkConst2 = ls::blocks::std::ConstantBlock<double>{1};
    auto blkSum = ls::blocks::std::SumBlock<double, 3>{};
    auto blkSum2 = ls::blocks::std::SumBlock<double, 2>{};
    auto blkGain = ls::blocks::std::GainBlock<double>{2};
    auto blkGain2 = ls::blocks::std::GainBlock<double>{4};

    connect(blkConst.o<0>(), blkSum.i<0>());
    connect(blkConst2.o<0>(), blkSum.i<1>());
    connect(blkSum.o<0>(), blkSum2.i<0>());
    connect(blkSum2.o<0>(), blkGain.i<0>());
    connect(blkGain.o<0>(), blkSum.i<2>());
    connect(blkGain.o<0>(), blkSum2.i<1>());
    connect(blkGain.o<0>(), blkGain2.i<0>());
    /*
     *          c2
     *          |
     * c1       v s1  s2    g1     g2
     * * -----> * --->*---> * ---->*
     *          ^     ^     |
     *          +-----+-----+
     */

    ls::blocks::BlockPack bp(blkConst, blkConst2, blkSum, blkSum2, blkGain, blkGain2);

    auto graph = ls::blocks::aux::DirectedGraph::fromBlocks(bp.blocks);

    auto components =
            ls::blocks::aux::StronglyConnectedComponents::findComponents(graph);

    REQUIRE(components.components.size() == 1);
    REQUIRE(components.isAlgebraicLoop(bp, 0));
    REQUIRE(components.containsAlgebraicLoops(bp));

    bool hasSum = false;
    bool hasGain = false;

    for (auto &component: components.components) {
        for (auto id: component) {
            if (id == blkSum.id) hasSum = true;
            if (id == blkGain.id) hasGain = true;
        }
    }

    bool verdict = (hasSum && hasGain);

    REQUIRE(verdict);

    auto externalIO = components.getExternalIO(bp, 0);

    REQUIRE(externalIO.first.size() == 2);
    REQUIRE(((externalIO.first[0].src->id == blkConst.id && externalIO.first[1].src->id == blkConst2.id) ||
             (externalIO.first[1].src->id == blkConst.id && externalIO.first[2].src->id == blkConst2.id)));

    REQUIRE(externalIO.second.size() == 1);
    REQUIRE(externalIO.second[0].dst->id == blkGain2.id);

    auto internalIO = components.getInternalIO(bp, 0);

    REQUIRE(internalIO.size() == 4);

    for (const auto &input : internalIO) {
        if (input.src->id == blkSum.id)
            REQUIRE(((input.dst->id == blkSum2.id) && (input.dstSlot == 0)));
        if (input.src->id == blkSum2.id)
            REQUIRE(((input.dst->id == blkGain.id) && (input.dstSlot == 0)));
        if (input.src->id == blkGain.id) {
            if (input.dst->id == blkSum2.id)
                REQUIRE(input.dstSlot == 1);
            else if (input.dst->id == blkSum.id)
                REQUIRE(input.dstSlot == 2);
        }
    }

//    REQUIRE(components.components.size() == 2);

//    REQUIRE(components.intersects(0, 1));
//    REQUIRE(components.isSubset(0, 1));
}

TEST_CASE("StronglyConnectedComponents applied 3", "[blocks][aux]")
{
    auto blkConst = ls::blocks::std::ConstantBlock<double>{3};
    auto blkConst2 = ls::blocks::std::ConstantBlock<double>{1};
    auto blkSum = ls::blocks::std::SumBlock<double, 3>{};
    auto blkSum2 = ls::blocks::std::SumBlock<double, 2>{};
    auto blkGain = ls::blocks::std::GainBlock<double>{2};
    auto blkGain2 = ls::blocks::std::GainBlock<double>{4};

    connect(blkConst.o<0>(), blkSum.i<0>());
    connect(blkConst2.o<0>(), blkSum.i<1>());
    connect(blkSum.o<0>(), blkSum2.i<0>());
    connect(blkSum2.o<0>(), blkGain.i<0>());
    connect(blkGain.o<0>(), blkSum2.i<1>());
    connect(blkGain.o<0>(), blkGain2.i<0>());
    connect(blkGain2.o<0>(), blkSum.i<2>());
    /*
     *          c2
     *          |
     * c1       v s1  s2    g1     g2
     * * -----> * --->*---> * ---->*
     *          ^     ^     |      |
     *          |     +-----+      |
     *          +------------------+
     */

    ls::blocks::BlockPack bp(blkConst, blkConst2, blkSum, blkSum2, blkGain, blkGain2);

    auto graph = ls::blocks::aux::DirectedGraph::fromBlocks(bp.blocks);

//    ::std::cout << graph.adj() << ::std::endl;

    auto components =
            ls::blocks::aux::StronglyConnectedComponents::findComponents(graph);

    REQUIRE(components.components.size() == 1);

    REQUIRE(components.isAlgebraicLoop(bp, 0));
    REQUIRE(components.containsAlgebraicLoops(bp));

    bool hasSum = false;
    bool hasGain = false;

    for (auto &component: components.components) {
        for (auto id: component) {
            if (id == blkSum.id) hasSum = true;
            if (id == blkGain.id) hasGain = true;
        }
    }

    bool verdict = (hasSum && hasGain);

    REQUIRE(verdict);

    auto externalIO = components.getExternalIO(bp, 0);

    REQUIRE(externalIO.first.size() == 2);
    REQUIRE(((externalIO.first[0].src->id == blkConst.id && externalIO.first[1].src->id == blkConst2.id) ||
             (externalIO.first[1].src->id == blkConst.id && externalIO.first[2].src->id == blkConst2.id)));

    REQUIRE(externalIO.second.empty());

    auto internalIO = components.getInternalIO(bp, 0);

    REQUIRE(internalIO.size() == 5);

    for (const auto &input : internalIO) {
        if (input.src->id == blkSum.id)
            REQUIRE(((input.dst->id == blkSum2.id) && (input.dstSlot == 0)));
        if (input.src->id == blkSum2.id)
            REQUIRE(((input.dst->id == blkGain.id) && (input.dstSlot == 0)));
        if (input.src->id == blkGain.id) {
            if (input.dst->id == blkSum2.id)
                REQUIRE(input.dstSlot == 1);
            else if (input.dst->id == blkGain2.id)
                REQUIRE(input.dstSlot == 0);
        } if (input.src->id == blkGain2.id)
            REQUIRE(((input.dst->id == blkSum.id) && (input.dstSlot == 2)));
    }

//    REQUIRE(components.components.size() == 2);

    auto subgraph = ls::blocks::aux::DirectedGraph::fromBlocks(components.extractBlocks(internalIO));

    auto subcomponents =
            ls::blocks::aux::StronglyConnectedComponents::findComponents(subgraph);

    REQUIRE(subcomponents.components.size() == 1);

//    ::std::cout << subgraph.adj() << ::std::endl;

//    ::std::cout << subcomponents.components[0].size() << ::std::endl;

    //    REQUIRE(components.intersects(0, 1));
    //    REQUIRE(components.isSubset(0, 1));
}