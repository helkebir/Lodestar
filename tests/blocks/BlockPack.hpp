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

            // TODO: Check if SFINAE is still possible here; if not, delegate
            //  to append.
            template <typename... TTypes>
            BlockPack(TTypes& ...blocks)
            {
                append(blocks...);
            }

//            template <typename... TTypes, typename ::std::enable_if<!ls::aux::TemplateTraits::allBasedOf<BlockProto, typename ::std::decay<TTypes>::type ...>::value>::type>
//            BlockPack(TTypes& ...blks)
//            {
//                static_assert(ls::aux::TemplateTraits::allBasedOf<BlockProto, typename ::std::decay<TTypes>::type ...>::value, "All elements of a BlockPack must be derived from BlockProto.");
//            }

            template<typename TType, typename... TTypes>
            void append(TType& block, TTypes& ...blocks)
            {
                append(block);
                append(blocks...);
            }

            template<typename TType>
            void append(TType& block)
            {
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

            ::std::vector<BlockProto*> blocks;
            ::std::vector<BlockTraits> blockTraits;

        };
    }
}


#endif //LODESTAR_BLOCKPACK_HPP
