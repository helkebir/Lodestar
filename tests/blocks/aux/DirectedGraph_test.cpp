//
// Created by Hamza El-Kebir on 12/25/21.
//

#include "catchOnce.hpp"
#include "Lodestar/blocks/aux/DirectedGraph.hpp"
#include "Lodestar/blocks/std/ConstantBlock.hpp"
#include "Lodestar/blocks/std/ConverterBlock.hpp"
#include "Lodestar/blocks/std/GainBlock.hpp"
#include "Lodestar/blocks/std/SignumBlock.hpp"
#include "Lodestar/blocks/std/SumBlock.hpp"
#include "Lodestar/blocks/BlockUtilities.hpp"

TEST_CASE("DirectedGraph", "[blocks][aux]")
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

    std::vector<ls::blocks::BlockProto *> blks{&blk0, &blk1, &blk2, &blk3,
                                               &blk4};

    auto graph = ls::blocks::aux::DirectedGraph::fromBlocks(blks);

    const Eigen::SparseMatrix<int> &adj = graph.adj();

    bool hasBlk0 = false;
    bool hasBlk1 = false;
    bool hasBlk2 = false;
    bool hasBlk3 = false;
    bool hasBlk4 = false;

    for (int k = 0; k < adj.outerSize(); ++k) {
        for (Eigen::SparseMatrix<int>::InnerIterator it(adj, k); it; ++it) {
            if (it.row() == blk0.id || it.col() == blk0.id)
                hasBlk0 = true;

            if (it.row() == blk1.id || it.col() == blk1.id)
                hasBlk1 = true;

            if (it.row() == blk2.id || it.col() == blk2.id)
                hasBlk2 = true;

            if (it.row() == blk3.id || it.col() == blk3.id)
                hasBlk3 = true;

            if (it.row() == blk4.id || it.col() == blk4.id)
                hasBlk4 = true;
        }
    }

    bool verdict = (hasBlk0 && hasBlk1 && hasBlk2 && hasBlk3 && hasBlk4);

    REQUIRE(verdict);
}