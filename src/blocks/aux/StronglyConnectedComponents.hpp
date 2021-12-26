//
// Created by Hamza El-Kebir on 12/25/21.
//

#ifndef LODESTAR_STRONGLYCONNECTEDCOMPONENTS_HPP
#define LODESTAR_STRONGLYCONNECTEDCOMPONENTS_HPP

#include "DirectedGraph.hpp"
#include <stack>

namespace ls {
    namespace blocks {
        namespace aux {
            class StronglyConnectedComponents {
            public:
                static ::std::vector<::std::vector<int>>
                findComponents(const DirectedGraph &graph,
                               bool allowSingletons = false)
                {
                    ::std::vector<int> disc, low;
                    disc.reserve(graph.getSize());
                    low.reserve(graph.getSize());

                    ::std::stack<int> stack;
                    ::std::vector<bool> stackItem;
                    stackItem.reserve(graph.getSize());

                    ::std::vector<::std::vector<int>> components;

                    for (int i = 0; i <
                                    graph.getSize(); i++) {    //initialize all elements
                        disc[i] = low[i] = -1;
                        stackItem[i] = false;
                    }

                    for (int i = 0;
                         i < graph.getSize(); i++)    //initialize all elements
                        if (disc[i] == -1)
                            findComponentsImpl(graph, i, disc, low, stack,
                                               stackItem, components,
                                               allowSingletons);

                    return components;
                }

            protected:
                // https://www.tutorialspoint.com/Tarjan-s-Algorithm-for-Strongly-Connected-Components
                static void
                findComponentsImpl(const DirectedGraph &graph, int u,
                                   ::std::vector<int> &disc,
                                   ::std::vector<int> &low,
                                   ::std::stack<int> &stack,
                                   ::std::vector<bool> &stackItem,
                                   ::std::vector<::std::vector<int>> &components,
                                   bool allowSingletons)
                {
                    static int time = 0;
                    disc[u] = low[u] = ++time;    //inilially discovery time and low value is 1
                    stack.push(u);
                    stackItem[u] = true;    //flag as u in the stack

                    for (int v = 0; v < graph.getSize(); v++) {
                        if (graph.hasConnection(u, v)) {
                            if (disc[v] == -1) {   //when v is not visited
                                findComponentsImpl(graph, v, disc, low, stack,
                                                   stackItem, components,
                                                   allowSingletons);
                                low[u] = ::std::min(low[u], low[v]);
                            } else if (stackItem[v])    //when v is in the stack, update low for u
                                low[u] = ::std::min(low[u], disc[v]);
                        }
                    }

                    int poppedItem = 0;
                    if (low[u] == disc[u]) {
                        ::std::vector<int> chain;

                        while (stack.top() != u) {
                            poppedItem = stack.top();
                            chain.push_back(poppedItem);
                            stackItem[poppedItem] = false;    //mark as item is popped
                            stack.pop();
                        }

                        poppedItem = stack.top();
                        chain.push_back(poppedItem);
                        stackItem[poppedItem] = false;
                        stack.pop();

                        if (allowSingletons || (chain.size() > 1))
                            components.push_back(chain);
                    }
                }
            };
        }
    }
}


#endif //LODESTAR_STRONGLYCONNECTEDCOMPONENTS_HPP
