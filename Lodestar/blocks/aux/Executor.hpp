//
// Created by Hamza El-Kebir on 12/25/21.
//

#ifndef LODESTAR_EXECUTOR_HPP
#define LODESTAR_EXECUTOR_HPP

#include "Lodestar/blocks/BlockPack.hpp"

#include <utility>
#include <algorithm>

namespace ls {
    namespace blocks {
        namespace aux {
            class Executor {
            public:
                Executor() : blockPack(), executionOrder(1)
                {}

                Executor(ls::blocks::BlockPack bp) : blockPack(::std::move(bp)), executionOrder(bp.blocks)
                {}

                // FIXME: For some reason, these two functions cannot be put in the source file, since the copy
                //  assignment will not work otherwise. Segfault with __memmove_avx_unaligned_erms is thrown in both GCC
                //  and Clang in that case.
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

                bool order(BlockProto *blk1, BlockProto *blk2) const;

                void trigger();

                ls::blocks::BlockPack blockPack;
                ::std::vector<BlockProto *> executionOrder{};
            };
        }
    }
}


#endif //LODESTAR_EXECUTOR_HPP
