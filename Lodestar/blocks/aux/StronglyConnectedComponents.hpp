//
// Created by Hamza El-Kebir on 12/25/21.
//

#ifndef LODESTAR_STRONGLYCONNECTEDCOMPONENTS_HPP
#define LODESTAR_STRONGLYCONNECTEDCOMPONENTS_HPP

#include "DirectedGraph.hpp"
#include "Lodestar/blocks/BlockPack.hpp"
#include <stack>
#include <algorithm>

namespace ls {
    namespace blocks {
        namespace aux {
            class StronglyConnectedComponents {
            public:
                struct SCCResult {
                    struct FullConnection {
                        const bool isInput;
                        const BlockProto *src;
                        const int srcSlot;
                        const BlockProto *dst;
                        const int dstSlot;
                    };

                    ::std::vector<::std::vector<int>> components;

                    // External input connections, output connections
                    ::std::pair<
                            ::std::vector<FullConnection>,
                            ::std::vector<FullConnection>
                    >
                    getExternalIO(const BlockPack &bp,
                                  int componentIdx = 0) const;

                    // Internal input connections, output connections
                    ::std::vector<FullConnection>
                    getInternalIO(const BlockPack &bp,
                                  int componentIdx = 0) const;

                    bool isSubset(int sup, int sub) const;

                    bool intersects(int idx1, int idx2) const;

                    bool isAlgebraicLoop(const BlockPack &bp, int componentIdx = 0) const;

                    bool containsAlgebraicLoops(const BlockPack &bp) const;

                    ::std::vector<const BlockProto *> extractBlocks(const ::std::vector<FullConnection> &connections) const;
                };

                static SCCResult
                findComponents(const DirectedGraph &graph,
                               bool allowSingletons = false);

            protected:
                // https://www.tutorialspoint.com/Tarjan-s-Algorithm-for-Strongly-Connected-Components
                static void
                findComponentsImpl(const DirectedGraph &graph, int u,
                                   ::std::vector<int> &disc,
                                   ::std::vector<int> &low,
                                   ::std::stack<int> &stack,
                                   ::std::vector<bool> &stackItem,
                                   ::std::vector<::std::vector<int>> &components,
                                   int &time,
                                   bool allowSingletons);
            };
        }
    }
}


#endif //LODESTAR_STRONGLYCONNECTEDCOMPONENTS_HPP
