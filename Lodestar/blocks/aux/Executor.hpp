//
// Created by Hamza El-Kebir on 12/25/21.
//

#ifndef LODESTAR_EXECUTOR_HPP
#define LODESTAR_EXECUTOR_HPP

#include "Lodestar/blocks/BlockPack.hpp"
#include "Lodestar/blocks/aux/StronglyConnectedComponents.hpp"

#include <utility>
#include <algorithm>

#define FMT_HEADER_ONLY

#include <fmt/format.h>

namespace ls {
    namespace blocks {
        namespace aux {
            class Executor {
            public:
                Executor() : blockPack(), executionOrder(1)
                {}

                Executor(ls::blocks::BlockPack bp) : blockPack(::std::move(bp)),
                                                     executionOrder(bp.blocks)
                {}

                // FIXME: For some reason, these two functions cannot be put in the source file, since the copy
                //  assignment will not work otherwise. Segfault with __memmove_avx_unaligned_erms is thrown in both GCC
                //  and Clang in that case.
                void computeExecutionOrder()
                {
                    executionOrder = blockPack.blocks;
                    components = StronglyConnectedComponents::findComponents(blockPack.graph);

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

                // NOTE: Yet another segfault here if this were defined in the source file.
                void trigger()
                {
                    for (auto blk: executionOrder)
                        blk->trigger();
                }

                ls::blocks::BlockPack blockPack;
                ::std::vector<BlockProto *> executionOrder{};
                ls::blocks::aux::StronglyConnectedComponents::SCCResult components;

                void
                makeDotFile(::std::stringstream &ss, bool lineLabels = true,
                            bool slotLabels = false, float rankSep = 2,
                            float nodeSep = 2);

            protected:
                static bool
                replace(::std::string &str, const ::std::string &from,
                        const ::std::string &to)
                {
                    size_t start_pos = str.find(from);
                    if (start_pos == ::std::string::npos)
                        return false;
                    str.replace(start_pos, from.length(), to);
                    return true;
                }

            };
        }
    }
}


#endif //LODESTAR_EXECUTOR_HPP
