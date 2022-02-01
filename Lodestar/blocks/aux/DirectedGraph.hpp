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
                fromBlocks(const ::std::vector<BlockProto *> &blocks);

                static DirectedGraph
                fromBlocks(const ::std::vector<const BlockProto *> &blocks);

                template <int N>
                static DirectedGraph
                fromBlocks(const ::std::array<BlockProto *, N> &blocks);

                template <int N>
                static DirectedGraph
                fromBlocks(const ::std::array<const BlockProto *, N> &blocks);

                int &get(int src, int dst);

                int get(int src, int dst) const;

                bool hasConnection(int src, int dst) const;

                int getSize() const;

                bool resize(int n);

                void connect(int src, int dst, int conn = 1);

                const Eigen::SparseMatrix<int> &adj() const;

            protected:
                Eigen::SparseMatrix<int> adj_;
                int size_;
            };
        }
    }
}


#endif //LODESTAR_DIRECTEDGRAPH_HPP
