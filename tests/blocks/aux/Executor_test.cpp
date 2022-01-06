//
// Created by Hamza El-Kebir on 12/25/21.
//

#include "catchOnce.hpp"

#include "Lodestar/blocks/std/ConstantBlock.hpp"
#include "Lodestar/blocks/std/ConverterBlock.hpp"
#include "Lodestar/blocks/std/GainBlock.hpp"
#include "Lodestar/blocks/std/SignumBlock.hpp"
#include "Lodestar/blocks/std/SumBlock.hpp"
#include "Lodestar/blocks/BlockUtilities.hpp"

#include "Lodestar/blocks/aux/Executor.hpp"
#include "Lodestar/blocks/aux/StronglyConnectedComponents.hpp"

TEST_CASE("Executor", "[blocks][aux]")
{
    ls::blocks::std::ConstantBlock<double> blk0{3};
    ls::blocks::std::GainBlock<double> blk1{-6};
    ls::blocks::std::SignumBlock<double> blk2;
    ls::blocks::std::ConverterBlock<int, double> blk3;

    connect(blk0.o<0>(), blk1.i<0>());
    connect(blk1.o<0>(), blk2.i<0>());
    connect(blk2.o<0>(), blk3.i<0>());

    //    ls::blocks::BlockPack bp(blk0, blk1, blk2, blk3);
    ls::blocks::BlockPack bp(blk1, blk0, blk3, blk2);
    //    ls::blocks::BlockPack bp(blk3, blk2, blk1, blk0);
    bp.makeGraph();

    REQUIRE(bp.hasDirectFeedthrough(&blk0));
    REQUIRE(bp.hasDirectFeedthrough(&blk1));
    REQUIRE(bp.hasDirectFeedthrough(&blk2));
    REQUIRE(bp.hasDirectFeedthrough(&blk3));

    REQUIRE((bp.traitsByPtr[&blk0]->blockType ==
             ls::blocks::BlockType::ConstantBlock));
    REQUIRE((bp.traitsByPtr[&blk1]->blockType ==
             ls::blocks::BlockType::GainBlock));
    REQUIRE((bp.traitsByPtr[&blk2]->blockType ==
             ls::blocks::BlockType::SignumBlock));
    REQUIRE((bp.traitsByPtr[&blk3]->blockType ==
             ls::blocks::BlockType::ConverterBlock));

    ls::blocks::aux::Executor ex(bp);
    ex.computeExecutionOrder();
    ex.applyExecutionOrder();

    REQUIRE(!ex.blockPack.isDriving(&blk0, &blk3));
    REQUIRE(ex.blockPack.isDriving(&blk0, &blk1));
    REQUIRE(ex.blockPack.isDriving(&blk1, &blk2));
    REQUIRE(ex.blockPack.isDriving(&blk2, &blk3));

    REQUIRE(ex.blockPack.hasDirectFeedthrough(&blk0));
    REQUIRE(ex.blockPack.hasDirectFeedthrough(&blk1));
    REQUIRE(ex.blockPack.hasDirectFeedthrough(&blk2));
    REQUIRE(ex.blockPack.hasDirectFeedthrough(&blk3));

    REQUIRE(ex.blockPack.contains(&blk0));
    REQUIRE(ex.blockPack.contains(&blk1));
    REQUIRE(ex.blockPack.contains(&blk2));
    REQUIRE(ex.blockPack.contains(&blk3));
    REQUIRE(!ex.blockPack.contains(nullptr));

    REQUIRE(ex.executionOrder[0] == &blk0);
    REQUIRE(ex.executionOrder[1] == &blk1);
    REQUIRE(ex.executionOrder[2] == &blk2);
    REQUIRE(ex.executionOrder[3] == &blk3);

//    std::cout << "blk0.id = " << blk0.id << std::endl;
//    std::cout << "blk1.id = " << blk1.id << std::endl;
//    std::cout << "blk2.id = " << blk2.id << std::endl;
//    std::cout << "blk3.id = " << blk3.id << std::endl;
//
//    for (auto &blk: ex.executionOrder) {
//        std::cout << "#" << blk->id << " (" << blk->getPriority() << ")"
//                  << " -> ";
//    }

    std::cout << std::endl;

    ex.trigger();

    REQUIRE(blk3.o<0>() == Approx(-1));
}

TEST_CASE("Executor with double connection", "[blocks][aux]")
{
    ls::blocks::std::ConstantBlock<double> blk0{3};
    ls::blocks::std::GainBlock<double> blk1{6};
    ls::blocks::std::SignumBlock<double> blk2;
    ls::blocks::std::ConverterBlock<int, double> blk3;
    ls::blocks::std::SumBlock<double, 2> blk4;

    connect(blk0.o<0>(), blk1.i<0>());
    connect(blk1.o<0>(), blk2.i<0>());
    connect(blk1.o<0>(), blk4.i<0>());
    connect(blk2.o<0>(), blk3.i<0>());
    connect(blk3.o<0>(), blk4.i<1>());

    //    ls::blocks::BlockPack bp(blk0, blk1, blk2, blk3);
    ls::blocks::BlockPack bp(blk1, blk0, blk3, blk2, blk4);
    //    ls::blocks::BlockPack bp(blk3, blk2, blk1, blk0);
    bp.makeGraph();

    REQUIRE(bp.hasDirectFeedthrough(&blk0));
    REQUIRE(bp.hasDirectFeedthrough(&blk1));
    REQUIRE(bp.hasDirectFeedthrough(&blk2));
    REQUIRE(bp.hasDirectFeedthrough(&blk3));
    REQUIRE(bp.hasDirectFeedthrough(&blk4));

    REQUIRE((bp.traitsByPtr[&blk0]->blockType ==
             ls::blocks::BlockType::ConstantBlock));
    REQUIRE((bp.traitsByPtr[&blk1]->blockType ==
             ls::blocks::BlockType::GainBlock));
    REQUIRE((bp.traitsByPtr[&blk2]->blockType ==
             ls::blocks::BlockType::SignumBlock));
    REQUIRE((bp.traitsByPtr[&blk3]->blockType ==
             ls::blocks::BlockType::ConverterBlock));
    REQUIRE((bp.traitsByPtr[&blk4]->blockType ==
             ls::blocks::BlockType::SumBlock));

    ls::blocks::aux::Executor ex(bp);
    ex.computeExecutionOrder();
    ex.applyExecutionOrder();

    REQUIRE(!ex.blockPack.isDriving(&blk0, &blk3));
    REQUIRE(ex.blockPack.isDriving(&blk0, &blk1));
    REQUIRE(ex.blockPack.isDriving(&blk1, &blk2));
    REQUIRE(ex.blockPack.isDriving(&blk2, &blk3));
    REQUIRE(ex.blockPack.isDriving(&blk1, &blk4));
    REQUIRE(ex.blockPack.isDriving(&blk3, &blk4));

    REQUIRE(ex.blockPack.hasDirectFeedthrough(&blk0));
    REQUIRE(ex.blockPack.hasDirectFeedthrough(&blk1));
    REQUIRE(ex.blockPack.hasDirectFeedthrough(&blk2));
    REQUIRE(ex.blockPack.hasDirectFeedthrough(&blk3));
    REQUIRE(ex.blockPack.hasDirectFeedthrough(&blk4));

    REQUIRE(ex.blockPack.contains(&blk0));
    REQUIRE(ex.blockPack.contains(&blk1));
    REQUIRE(ex.blockPack.contains(&blk2));
    REQUIRE(ex.blockPack.contains(&blk3));
    REQUIRE(ex.blockPack.contains(&blk4));
    REQUIRE(!ex.blockPack.contains(nullptr));

    REQUIRE(ex.executionOrder[0] == &blk0);
    REQUIRE(ex.executionOrder[1] == &blk1);
    REQUIRE(ex.executionOrder[2] == &blk2);
    REQUIRE(ex.executionOrder[3] == &blk3);
    REQUIRE(ex.executionOrder[4] == &blk4);

//    std::cout << "blk0.id = " << blk0.id << std::endl;
//    std::cout << "blk1.id = " << blk1.id << std::endl;
//    std::cout << "blk2.id = " << blk2.id << std::endl;
//    std::cout << "blk3.id = " << blk3.id << std::endl;
//    std::cout << "blk4.id = " << blk4.id << std::endl;
//
//    for (auto &blk: ex.executionOrder) {
//        std::cout << "#" << blk->id << " (" << blk->getPriority() << ")"
//                  << " -> ";
//    }

    std::cout << std::endl;

    ex.trigger();

    REQUIRE(blk4.o<0>() == Approx(19));
}

TEST_CASE("Executor with loop", "[blocks][aux]")
{
    auto blkConst = ls::blocks::std::ConstantBlock<double>{3};
    auto blkSum = ls::blocks::std::SumBlock<double, 2>{};
    auto blkGain = ls::blocks::std::GainBlock<double>{2};
    auto blkGain2 = ls::blocks::std::GainBlock<double>{4};

    blkConst.trigger();

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

    ls::blocks::BlockPack bp(blkConst, blkSum, blkGain, blkGain2);
    bp.makeGraph();
    ls::blocks::aux::Executor ex(bp);
    ex.computeExecutionOrder();
    ex.applyExecutionOrder();

    REQUIRE(ex.executionOrder[0] == &blkConst);
    REQUIRE(ex.executionOrder[1] == &blkGain);
    REQUIRE(ex.executionOrder[2] == &blkSum);
    REQUIRE(ex.executionOrder[3] == &blkGain2);

//    std::cout << "blkConst.id = " << blkConst.id << std::endl;
//    std::cout << "blkSum.id = " << blkSum.id << std::endl;
//    std::cout << "blkGain.id = " << blkGain.id << std::endl;
//    std::cout << "blkGain2.id = " << blkGain2.id << std::endl;
//
//    for (auto &blk: ex.executionOrder) {
//        std::cout << "#" << blk->id << " (" << blk->getPriority() << ")"
//                  << " -> ";
//    }
//    std::cout << std::endl;

    auto components = ls::blocks::aux::StronglyConnectedComponents::findComponents(
            ex.blockPack.graph
    );

    // TODO: Resolve algebraic loops.
//    std::cout << "SCC: ";
//    for (auto &component: components) {
//        for (auto id: component) {
//            std::cout << id << " -> ";
//        }
//        std::cout << std::endl;
//    }

    //    ex.trigger();
    //    REQUIRE(blkGain2.o<0>() == -(3 + 3*2)*4);
}