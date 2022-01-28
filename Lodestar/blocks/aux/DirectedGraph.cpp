//
// Created by Hamza El-Kebir on 12/25/21.
//

#include "DirectedGraph.hpp"

ls::blocks::aux::DirectedGraph ls::blocks::aux::DirectedGraph::fromBlocks(const std::vector<BlockProto *> &blocks)
{
    ::std::vector<Eigen::Triplet<int>> triplets;

    int n = 0;

    for (auto &block: blocks) {
        if (block->id >= n)
            n = (block->id + 1);

        // Input connections can be disregarded.
        for (auto &output: block->outputPointers) {
            for (int i=0; i < output->connectionNumber; i++) {
                SignalBase* connection = output->getConnection(i);

                if (connection == nullptr)
                    continue;

                if (connection->blockId >= n)
                    n = (connection->blockId + 1);

                triplets.emplace_back(block->id,
                                      connection->blockId, 1);
            }
        }
    }

    Eigen::SparseMatrix<int> adj(n, n);
    adj.setFromTriplets(triplets.begin(), triplets.end());
    DirectedGraph graph(adj);

    return graph;
}

template<int N>
ls::blocks::aux::DirectedGraph ls::blocks::aux::DirectedGraph::fromBlocks(const std::array<BlockProto *, N> &blocks)
{
    ::std::vector<Eigen::Triplet<int>> triplets;

    int n = 0;

    for (auto &block: blocks) {
        if (block->id >= n)
            n = (block->id + 1);

        // Input connections can be disregarded.
        for (auto &output: block->outputPointers) {
            for (auto &connection: output->connectionPointers) {
                if (connection->blockId >= n)
                    n = (connection->blockId + 1);

                triplets.emplace_back(block->id,
                                      connection->blockId, 1);
            }
        }
    }

    Eigen::SparseMatrix<int> adj(n, n);
    adj.setFromTriplets(triplets.begin(), triplets.end());
    DirectedGraph graph(adj);

    return graph;
}

int &ls::blocks::aux::DirectedGraph::get(int src, int dst)
{
    return adj_.coeffRef(src, dst);
}

int ls::blocks::aux::DirectedGraph::get(int src, int dst) const
{
    return adj_.coeff(src, dst);
}

bool ls::blocks::aux::DirectedGraph::hasConnection(int src, int dst) const
{
    return (get(src, dst) != 0);
}

int ls::blocks::aux::DirectedGraph::getSize() const
{
    return size_;
}

bool ls::blocks::aux::DirectedGraph::resize(int n)
{
    if (n <= getSize())
        return false;

    size_ = n;
    adj_.reserve(n * n);

    return true;
}

void ls::blocks::aux::DirectedGraph::connect(int src, int dst, int conn)
{
    get(src, dst) = conn;
}

const Eigen::SparseMatrix<int> &ls::blocks::aux::DirectedGraph::adj() const
{
    return adj_;
}
