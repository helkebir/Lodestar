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

    for (const auto &input: internalIO) {
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
    REQUIRE(components.getComponentLength(0) == 4);

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

    for (const auto &input: internalIO) {
        if (input.src->id == blkSum.id)
            REQUIRE(((input.dst->id == blkSum2.id) && (input.dstSlot == 0)));
        if (input.src->id == blkSum2.id)
            REQUIRE(((input.dst->id == blkGain.id) && (input.dstSlot == 0)));
        if (input.src->id == blkGain.id) {
            if (input.dst->id == blkSum2.id)
                REQUIRE(input.dstSlot == 1);
            else if (input.dst->id == blkGain2.id)
                REQUIRE(input.dstSlot == 0);
        }
        if (input.src->id == blkGain2.id)
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

#ifdef LS_USE_GINAC

TEST_CASE("StronglyConnectedComponents symbolic", "[blocks][aux]")
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
    REQUIRE(components.getComponentLength(0) == 4);

    ::std::cout << "--------------------------------" << ::std::endl;
    ::std::cout << "blkConst: " << blkConst.id << ::std::endl;
    ::std::cout << "blkConst2: " << blkConst2.id << ::std::endl;
    ::std::cout << "blkSum: " << blkSum.id << ::std::endl;
    ::std::cout << "blkSum2: " << blkSum2.id << ::std::endl;
    ::std::cout << "blkGain: " << blkGain.id << ::std::endl;
    ::std::cout << "blkGain2: " << blkGain2.id << ::std::endl;
    ::std::cout << "--------------------------------" << ::std::endl;

    for (auto iSymb: *bp.inputSymbols[2]) {
        ::std::cout << iSymb << ::std::endl;
    }

    ::std::cout << "------------" << ::std::endl;

    for (auto iSymb: blkSum.inputSymbols()) {
        ::std::cout << iSymb << ::std::endl;
    }

    ::std::cout << "Known symbols:" << ::std::endl;
    ::std::cout << components.getKnownSymbolList(bp, 0) << ::std::endl;

    ::std::cout << "Unknown symbols:" << ::std::endl;
    ::std::cout << components.getUnknownSymbolList(bp, 0) << ::std::endl;

    ::std::cout << "Equations:" << ::std::endl;
    ::std::cout << components.getSymbolicEquationList(bp, 0) << ::std::endl;

    auto eqs = components.getAlgebraicEquations(bp, 0);
    ::std::cout << "Algebraic equations:" << ::std::endl;
    ::std::cout << eqs.first << ::std::endl;
    ::std::cout << "Unknowns:" << ::std::endl;
    ::std::cout << eqs.second << ::std::endl;
    ::std::cout << "Algebraic equations Jacobian:" << ::std::endl;
    auto jac = decltype(components)::getAlgebraicEquationsJacobian(eqs.first, eqs.second);
    ::std::cout << jac << ::std::endl;

    auto nrIteration = decltype(components)::solveAlgebraicEquationsNewtonRaphson(eqs.first, jac, eqs.second);
    ::std::cout << "Newton-Raphson iteration:" << ::std::endl;
    ::std::cout << nrIteration.first << ::std::endl;

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

    for (const auto &input: internalIO) {
        if (input.src->id == blkSum.id)
            REQUIRE(((input.dst->id == blkSum2.id) && (input.dstSlot == 0)));
        if (input.src->id == blkSum2.id)
            REQUIRE(((input.dst->id == blkGain.id) && (input.dstSlot == 0)));
        if (input.src->id == blkGain.id) {
            if (input.dst->id == blkSum2.id)
                REQUIRE(input.dstSlot == 1);
            else if (input.dst->id == blkGain2.id)
                REQUIRE(input.dstSlot == 0);
        }
        if (input.src->id == blkGain2.id)
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

#include <Lodestar/blocks/std/ConstantBlock.hpp>
#include <Lodestar/blocks/std/SumBlock.hpp>
#include <Lodestar/blocks/std/GainBlock.hpp>
#include <Lodestar/blocks/std/SaturationBlock.hpp>
#include <Lodestar/blocks/std/DelayBlock.hpp>

using namespace ls::blocks::std;

#include <Lodestar/blocks/aux/Executor.hpp>

TEST_CASE("StronglyConnectComponents fuzzy PID", "[blocks][aux]")
{
    using TScalar = float;
    using TType = float;
    using TMatrix = float;

    TScalar T = 1e-4;

    ConstantBlock<TScalar> constBlk{0};
    GainBlock<TType, TMatrix> gainK, gainKp, gainKd, gainKi, gainKuPD, gainKuI;
    GainBlock<TType, TScalar> gainTinv1{1.f / T}, gainTinv2{1.f / T};
    DelayBlock<TType> delay1, delay2, delay3, delay4, delay5, process;
    SumBlock<TType, 2> sum1, sum2, sum3, sum4, sum5, sum6, sum7, fuzzyPDSum;

    sum1.setOperators(decltype(sum1)::Plus, decltype(sum1)::Minus);
    sum2.setOperators(decltype(sum2)::Plus, decltype(sum2)::Minus);
    sum5.setOperators(decltype(sum5)::Plus, decltype(sum5)::Minus);

    auto &sp = sum1.i<0>();
    auto &e = sum1.o<0>();
    auto &d = gainTinv2.o<0>();
    auto &r = gainTinv1.o<0>();
    auto &duPD = fuzzyPDSum.o<0>();
    auto &duI = sum4.o<0>();
    auto &uPD = sum5.o<0>();
    auto &uI = sum6.o<0>();
    auto &uPID = sum7.o<0>();

    connect(e, delay1.i<0>());
    connect(delay1.o<0>(), gainKi.i<0>());
    connect(gainKi.o<0>(), sum4.i<0>());

    connect(e, delay2.i<0>());
    connect(delay2.o<0>(), sum3.i<0>());
    connect(e, sum3.i<1>());
    connect(sum3.o<0>(), gainTinv2.i<0>());
    connect(d, gainKp.i<0>());

    connect(e, sum2.i<0>());
    connect(e, delay3.i<0>());
    connect(delay3.o<0>(), sum2.i<1>());
    connect(sum2.o<0>(), gainTinv1.i<0>());

    connect(r, gainK.i<0>());
    connect(r, gainKd.i<0>());
    connect(gainK.o<0>(), sum4.i<1>());

    connect(gainKp.o<0>(), fuzzyPDSum.i<0>());
    connect(gainKd.o<0>(), fuzzyPDSum.i<1>());
    connect(duPD, gainKuPD.i<0>());
    connect(gainKuPD.o<0>(), sum5.i<0>());
    connect(uPD, delay4.i<0>());
    connect(delay4.o<0>(), sum5.i<1>());

    connect(sum4.o<0>(), gainKuI.i<0>());
    connect(gainKuI.o<0>(), sum6.i<0>());
    connect(uI, delay5.i<0>());
    connect(delay5.o<0>(), sum6.i<1>());

    connect(uPD, sum7.i<0>());
    connect(uI, sum7.i<1>());

    connect(constBlk.o<0>(), sp);
    connect(uPID, process.i<0>());
    connect(process.o<0>(), sum1.i<1>());

    gainKp.gain() = 10;
    gainKi.gain() = 0.2;
    gainKd.gain() = 0.1;
    gainKd.gain() *= 0.1;

    gainK.gain() = 1;
    gainKuPD.gain() = 1;
    gainKuI.gain() = 1;

    ls::blocks::BlockPack bp{gainK, gainKp, gainKd, gainKi, gainKuPD, gainKuI, gainTinv1, gainTinv2, delay1,
                             delay2, delay3, delay4, delay5, sum1, sum2, sum3, sum4, sum5, sum6, sum7, fuzzyPDSum, process, constBlk};

    bp.makeGraph();
    ls::blocks::aux::Executor ex(bp);
    ex.resolveExecutionOrder();

    ::std::stringstream ss;
    ex.makeDotFile(ss, true, false);

    ::std::cout << "HERE\n";
    ::std::cout << ss.str() << ::std::endl;
}

#endif