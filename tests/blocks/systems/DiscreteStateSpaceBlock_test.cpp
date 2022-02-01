//
// Created by Hamza El-Kebir on 12/30/2021.
//

#include "catchOnce.hpp"
#include "Lodestar/blocks/std/systems/DiscreteStateSpaceBlock.hpp"
#include "Lodestar/blocks/std/ConstantBlock.hpp"
#include "Lodestar/blocks/aux/StronglyConnectedComponents.hpp"
#include "Lodestar/blocks/aux/Executor.hpp"
#include "Lodestar/blocks/std/GainBlock.hpp"
#include "Lodestar/blocks/std/SumBlock.hpp"
#include "Lodestar/blocks/std/MuxBlock.hpp"
#include "Lodestar/blocks/BlockPack.hpp"
#include "Lodestar/blocks/BlockUtilities.hpp"

TEST_CASE("DiscreteStateSpaceBlock", "[blocks][std][systems]")
{
    ls::systems::DiscreteStateSpace<double, 2, 2, 2> dss;
    decltype(dss)::TDStateMatrix A;
    decltype(dss)::TDInputMatrix B;
    decltype(dss)::TDOutputMatrix C;
    decltype(dss)::TDFeedforwardMatrix D;

    A << 0, 1,
         1, 0;

    B << 0, 0,
         1, 1;

    C << 1, 0,
         0, 1;

    dss.setA(A);
    dss.setB(B);
    dss.setC(C);

    Eigen::Vector2d u;
    u << 2, 2;

    ls::blocks::std::DiscreteStateSpaceBlock<decltype(dss)> dssBlock(dss);

    REQUIRE((dssBlock.getSystem().getA() - A).isZero());
    REQUIRE((dssBlock.getSystem().getB() - B).isZero());
    REQUIRE((dssBlock.getSystem().getC() - C).isZero());
    REQUIRE(dssBlock.getSystem().getD().isZero());

    ls::blocks::std::ConstantBlock<decltype(u)> constantBlock(u);

    connect(constantBlock.o<0>(), dssBlock.i<0>());

    ::std::vector<ls::blocks::BlockProto*> blks = {&constantBlock, &dssBlock};

    for (auto blk: blks)
        blk->trigger();

    REQUIRE(dssBlock.o<0>().object.isZero());

    for (auto blk: blks)
        blk->trigger();

    REQUIRE(dssBlock.o<0>().object(0) + 0.1 == Approx(0.1));
    REQUIRE(dssBlock.o<0>().object(1) == Approx(4));

    for (auto blk: blks)
        blk->trigger();

    REQUIRE(dssBlock.o<0>().object(0) == Approx(4));
    REQUIRE(dssBlock.o<0>().object(1) == Approx(4));

    for (auto blk: blks)
        blk->trigger();

    REQUIRE(dssBlock.o<0>().object(0) == Approx(4));
    REQUIRE(dssBlock.o<0>().object(1) == Approx(8));

    for (auto blk: blks)
        blk->trigger();

    REQUIRE(dssBlock.o<0>().object(0) == Approx(8));
    REQUIRE(dssBlock.o<0>().object(1) == Approx(8));
}

TEST_CASE("DiscreteStateSpaceBlock loop w/o feedthrough", "[blocks][std][systems]")
{
    ls::systems::DiscreteStateSpace<double, 2, 2, 2> dss;
    decltype(dss)::TDStateMatrix A;
    decltype(dss)::TDInputMatrix B;
    decltype(dss)::TDOutputMatrix C;
    decltype(dss)::TDFeedforwardMatrix D;

    A << 0, 1,
            1, 0;

    B << 0, 0,
            1, 1;

    C << 1, 0,
         0, 1;

    dss.setA(A);
    dss.setB(B);
    dss.setC(C);

    Eigen::Vector2d u;
    u << 2, 2;

    ls::blocks::std::DiscreteStateSpaceBlock<decltype(dss)> blkDss{dss};

    auto blkConst = ls::blocks::std::ConstantBlock<double>{3};
    auto blkConst2 = ls::blocks::std::ConstantBlock<double>{1};
    auto blkMux = ls::blocks::std::MuxBlock<Eigen::Vector2d>{};
    auto blkSum = ls::blocks::std::SumBlock<Eigen::Vector2d, 2>{};
    auto blkGain = ls::blocks::std::GainBlock<Eigen::Vector2d, Eigen::Matrix2d>{0.5 * Eigen::Matrix2d::Ones()};
    auto blkGain2 = ls::blocks::std::GainBlock<Eigen::Vector2d, Eigen::Matrix2d>{4 * Eigen::Matrix2d::Ones()};

    /*
     *     c2
     *     |
     * c1  v m  s   g1  dss  g2
     * 0 ->|--> * --*-->*----*---->
     *          ^       |
     *          +-------+
     */

    connect(blkConst.o<0>(), blkMux.i<0>());
    connect(blkConst2.o<0>(), blkMux.i<1>());

    connect(blkMux.o<0>(), blkSum.i<0>());
    connect(blkDss.o<0>(), blkSum.i<1>());

    connect(blkSum.o<0>(), blkGain.i<0>());
    connect(blkGain.o<0>(), blkDss.i<0>());

    connect(blkDss.o<0>(), blkGain2.i<0>());

    ls::blocks::BlockPack bp{blkConst, blkConst2, blkMux, blkSum, blkGain, blkGain2, blkDss};

    bp.makeGraph();

    auto components =
            ls::blocks::aux::StronglyConnectedComponents::findComponents(bp.graph);

    REQUIRE(components.components.size() == 1);
    REQUIRE(components.components[0].size() == 3);
    REQUIRE(!components.isAlgebraicLoop(bp, 0));
    REQUIRE(!components.containsAlgebraicLoops(bp));

    ls::blocks::aux::Executor ex(bp);
    ex.computeExecutionOrder();
    ex.applyExecutionOrder();

    REQUIRE((blkConst.getPriority() < blkMux.getPriority()));
    REQUIRE((blkConst2.getPriority() < blkMux.getPriority()));
    REQUIRE((blkDss.getPriority() < blkGain2.getPriority()));

    ex.trigger();

    REQUIRE((blkMux.o<0>().object - Eigen::Vector2d{3, 1}).isZero());
}

TEST_CASE("DiscreteStateSpaceBlock BlockTraits", "[blocks][std][systems]")
{
    using trait = ls::blocks::BlockTraits<ls::blocks::std::DiscreteStateSpaceBlock<ls::systems::DiscreteStateSpace<double, 1, 2, 3>>>;

    REQUIRE((trait::blockType == ls::blocks::BlockType::DiscreteStateSpaceBlock));

    REQUIRE((trait::kIns == 1));

    REQUIRE((trait::kOuts == 1));

    REQUIRE((trait::kPars == 1));

    REQUIRE((trait::kNState == 1));

    REQUIRE((trait::kNInput == 2));

    REQUIRE((trait::kNOutput == 3));
}