//
// Created by Hamza El-Kebir on 12/25/21.
//

#ifndef LODESTAR_BLOCKPACK_HPP
#define LODESTAR_BLOCKPACK_HPP

#include "blocks/Block.hpp"
#include "aux/TemplateTraits.hpp"
#include <vector>

namespace ls {
    namespace blocks {
        struct BlockPack {
        public:
            struct BlockTraits {
                ls::blocks::BlockType blockType;
                bool directFeedthrough;
                int ins;
                int outs;
                int pars;
            };

            template<typename... TTypes>
            explicit BlockPack(TTypes &...blocks)
            {
                append(blocks...);
            }

            template<typename TType, typename... TTypes>
            void append(TType &block, TTypes &...blocks)
            {
                append(block);
                append(blocks...);
            }

            template<typename TType>
            void append(TType &block)
            {
                static_assert(
                        ::std::is_base_of<BlockProto, typename ::std::decay<TType>::type>::value,
                        "All elements in BlockPack must be derived from BlockProto."
                );

                blocks.push_back(&block);
                typedef ls::blocks::BlockTraits<typename ::std::decay<TType>::type> TDBlockTraits;
                blockTraits.push_back(BlockTraits{
                        TDBlockTraits::blockType,
                        TDBlockTraits::directFeedthrough,
                        TDBlockTraits::kIns,
                        TDBlockTraits::kOuts,
                        TDBlockTraits::kPars
                });
            }

            void append()
            {
                return;
            }

            ::std::vector<BlockProto *> blocks;
            ::std::vector<BlockTraits> blockTraits;

        };
    }
}


#endif //LODESTAR_BLOCKPACK_HPP
