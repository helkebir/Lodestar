//
// Created by Hamza El-Kebir on 12/25/21.
//

#ifndef LODESTAR_BLOCKPACK_HPP
#define LODESTAR_BLOCKPACK_HPP

#include "blocks/Block.hpp"
#include "blocks/aux/DirectedGraph.hpp"
#include <type_traits>
#include <vector>
#include <unordered_map>
#include <memory>

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
//                typedef ls::blocks::BlockTraits<typename ::std::decay<TType>::type> TDBlockTraits;
                auto bt = ::std::make_shared<BlockTraits>(BlockTraits{
                        ls::blocks::BlockTraits<typename ::std::decay<TType>::type>::blockType,
                        ls::blocks::BlockTraits<typename ::std::decay<TType>::type>::directFeedthrough,
                        ls::blocks::BlockTraits<typename ::std::decay<TType>::type>::kIns,
                        ls::blocks::BlockTraits<typename ::std::decay<TType>::type>::kOuts,
                        ls::blocks::BlockTraits<typename ::std::decay<TType>::type>::kPars
                });
                blockTraits.push_back(bt);

                traitsByPtr[&block] = bt;
            }

            void append()
            {
                return;
            }

            void makeGraph()
            {
                graph = ls::blocks::aux::DirectedGraph::fromBlocks(blocks);
            }

            bool contains(BlockProto * blk) const
            {
                return (traitsByPtr.find(blk) != traitsByPtr.end());
            }

            bool hasDirectFeedthrough(BlockProto * blk) const
            {
                if (contains(blk))
                    return traitsByPtr.at(blk)->directFeedthrough;
                else
                    return false;
            }

            bool isDriving(BlockProto * blk1, BlockProto * blk2) const
            {
                if (contains(blk1) && contains(blk2))
                    return graph.hasConnection(blk1->id, blk2->id);
                else
                    return false;
            }

            ::std::vector<BlockProto *> blocks;
            ::std::vector<::std::shared_ptr<BlockTraits>> blockTraits;
            ::std::unordered_map<BlockProto *, ::std::shared_ptr<BlockTraits>> traitsByPtr;
            ls::blocks::aux::DirectedGraph graph;
        };
    }
}


#endif //LODESTAR_BLOCKPACK_HPP
