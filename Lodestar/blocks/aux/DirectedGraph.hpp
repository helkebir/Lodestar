//
// Created by Hamza El-Kebir on 12/25/21.
//

#ifndef LODESTAR_DIRECTEDGRAPH_HPP
#define LODESTAR_DIRECTEDGRAPH_HPP

#include "Lodestar/GlobalConstants.hpp"
#include "Lodestar/blocks/BlockProto.hpp"
#include <vector>
#include <array>
#include "Eigen/Sparse"

namespace ls {
    namespace blocks {
        namespace aux {
            class DirectedGraph {
            public:

                DirectedGraph() : adj_{LS_MAX_CONNECTIONS, LS_MAX_CONNECTIONS},
                                  size_(LS_MAX_CONNECTIONS)
                {}

                DirectedGraph(int n) : adj_{n, n}, size_(n)
                {}

                DirectedGraph(const Eigen::SparseMatrix<int> &adj) : adj_(adj),
                                                                     size_(adj.rows())
                {}

                static DirectedGraph
                fromBlocks(const ::std::vector<BlockProto *> &blocks)
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

                template <int N>
                static DirectedGraph
                fromBlocks(const ::std::array<BlockProto *, N> &blocks)
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

                int &get(int src, int dst)
                {
                    return adj_.coeffRef(src, dst);
                }

                int get(int src, int dst) const
                {
                    return adj_.coeff(src, dst);
                }

                bool hasConnection(int src, int dst) const
                {
                    return (get(src, dst) != 0);
                }

                int getSize() const
                {
                    return size_;
                }

                bool resize(int n)
                {
                    if (n <= getSize())
                        return false;

                    size_ = n;
                    adj_.reserve(n * n);

                    return true;
                }

                void connect(int src, int dst, int conn = 1)
                {
                    get(src, dst) = conn;
                }

                const Eigen::SparseMatrix<int> &adj() const
                {
                    return adj_;
                }

            protected:
                Eigen::SparseMatrix<int> adj_;
                int size_;
            };
        }
    }
}


#endif //LODESTAR_DIRECTEDGRAPH_HPP
