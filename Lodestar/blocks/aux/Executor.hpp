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
                Executor() = default;

                Executor(ls::blocks::BlockPack bp) : blockPack(::std::move(bp))
                {}

                void computeExecutionOrder();

                void applyExecutionOrder();

                bool order(BlockProto *blk1, BlockProto *blk2) const;

                void trigger();

                ls::blocks::BlockPack blockPack;
                ::std::vector<BlockProto *> executionOrder;
            };
        }
    }
}


#endif //LODESTAR_EXECUTOR_HPP
