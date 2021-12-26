//
// Created by Hamza El-Kebir on 12/25/21.
//

#ifndef LODESTAR_EXECUTOR_HPP
#define LODESTAR_EXECUTOR_HPP

#include "blocks/BlockPack.hpp"

#include <utility>
#include <algorithm>

namespace ls {
    namespace blocks {
        namespace aux {
            class Executor {
            public:
                Executor() = default;

                Executor(ls::blocks::BlockPack bp) : blockPack(::std::move(bp))
                {}

                void computeExecutionOrder()
                {
                    executionOrder = blockPack.blocks;

                    ::std::sort(executionOrder.begin(),
                                executionOrder.end(),
                                [&](
                                        BlockProto *a,
                                        BlockProto *b) {
                                    return order(a, b);
                                });

                    ::std::reverse(executionOrder.begin(),
                                   executionOrder.end());
                }


                void applyExecutionOrder()
                {
                    int i = 0;
                    for (auto &blk: executionOrder) {
                        blk->setPriority(i);
                        i++;
                    }
                }

                // TODO: Closely reconsider ordering rules, i.e., do not rely
                //  on reversing the final order.
                bool order(BlockProto *blk1, BlockProto *blk2) const
                {
                    bool res = false;
                    if (blockPack.isDriving(blk1, blk2)) {
                        if (blockPack.hasDirectFeedthrough(blk2))
                            res = true;
                    }

                    //                    if (blockPack.hasDirectFeedthrough(blk2)) {
                    //                        if (blockPack.isDriving(blk1, blk2))
                    //                            res = true;
                    //                        else
                    //                            res = false;
                    //                    }

                    //                    else if (blockPack.hasDirectFeedthrough(blk1)) {
                    //                        if (blockPack.isDriving(blk2, blk1))
                    //                            res = false;
                    //                        else
                    //                            res = true;
                    //                    }

                    return !res;
                }

                void trigger()
                {
                    for (auto blk: executionOrder)
                        blk->trigger();
                }

                ls::blocks::BlockPack blockPack;
                ::std::vector<BlockProto *> executionOrder;
            };
        }
    }
}


#endif //LODESTAR_EXECUTOR_HPP
