//
// Created by Hamza El-Kebir on 12/30/2021.
//

#include "catchOnce.hpp"
#include "blocks/std/systems/DiscreteStateSpaceBlock.hpp"
#include "blocks/std/ConstantBlock.hpp"
#include "blocks/BlockUtilities.hpp"

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

TEST_CASE("DiscreteStateSpaceBlock BlockTraits", "[blocks][std][systems]")
{
    using trait = ls::blocks::BlockTraits<ls::blocks::std::DiscreteStateSpaceBlock<ls::systems::DiscreteStateSpace<double, 1, 2, 3>>>;

    bool res;

    // Catch doesn't like type aliases :(
    res = trait::blockType == ls::blocks::BlockType::DiscreteStateSpaceBlock;
    REQUIRE(("trait::blockType == ls::blocks::BlockType::DiscreteStateSpaceBlock" && res));

    res = trait::kIns == 1;
    REQUIRE(("trait::kIns == 1" && res));

    res = trait::kOuts == 1;
    REQUIRE(("trait::kOuts == 1" && res));

    res = trait::kPars == 1;
    REQUIRE(("trait::kPars == 1" && res));

    res = trait::kNState == 1;
    REQUIRE(("trait::kNState == 1" && res));

    res = trait::kNInput == 2;
    REQUIRE(("trait::kNInput == 2" && res));

    res = trait::kNOutput == 3;
    REQUIRE(("trait::kNOutput == 3" && res));
}