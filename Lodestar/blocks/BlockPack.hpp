//
// Created by Hamza El-Kebir on 12/25/21.
//

#ifndef LODESTAR_BLOCKPACK_HPP
#define LODESTAR_BLOCKPACK_HPP

#include "Lodestar/blocks/Block.hpp"
#include "Lodestar/blocks/aux/DirectedGraph.hpp"
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
                ::std::vector<::std::string> inTypes;
                ::std::vector<::std::string> outTypes;
                ::std::vector<::std::string> parTypes;
                ::std::vector<::std::string> templateTypes;
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
                using blockType = typename ::std::decay<TType>::type;
//                typedef ls::blocks::BlockTraits<typename ::std::decay<TType>::type> TDBlockTraits;
                auto bt = ::std::make_shared<BlockTraits>(BlockTraits{
                        ls::blocks::BlockTraits<blockType>::blockType,
                        ls::blocks::BlockTraits<blockType>::directFeedthrough,
                        ls::blocks::BlockTraits<blockType>::kIns,
                        ls::blocks::BlockTraits<blockType>::kOuts,
                        ls::blocks::BlockTraits<blockType>::kPars,
                        ::std::vector<::std::string>{ls::blocks::BlockTraits<blockType>::inTypes.begin(),
                                                     ls::blocks::BlockTraits<blockType>::inTypes.end()},
                        ::std::vector<::std::string>{ls::blocks::BlockTraits<blockType>::outTypes.begin(),
                                                     ls::blocks::BlockTraits<blockType>::outTypes.end()},
                        ::std::vector<::std::string>{ls::blocks::BlockTraits<blockType>::parTypes.begin(),
                                                     ls::blocks::BlockTraits<blockType>::parTypes.end()},
                        ::std::vector<::std::string>{ls::blocks::BlockTraits<blockType>::templateTypes.begin(),
                                                     ls::blocks::BlockTraits<blockType>::templateTypes.end()}
                });
                blockTraits.push_back(bt);

#ifdef LS_USE_GINAC
                auto iSymbs = ::std::make_shared<::std::vector<GiNaC::ex>>(block.inputSymbols().begin(),
                                                                           block.inputSymbols().end());
                auto oSymbs = ::std::make_shared<::std::vector<GiNaC::ex>>(block.outputSymbols().begin(),
                                                                           block.outputSymbols().end());
                auto pSymbs = ::std::make_shared<::std::vector<GiNaC::ex>>(block.parameterSymbols().begin(),
                                                                           block.parameterSymbols().end());

                inputSymbols.push_back(iSymbs);
                outputSymbols.push_back(iSymbs);
                parameterSymbols.push_back(iSymbs);

                inputSymbolsByPtr[&block] = iSymbs;
                outputSymbolsByPtr[&block] = oSymbs;
                parameterSymbolsByPtr[&block] = pSymbs;

                auto f = ::std::make_shared<::std::function<const GiNaC::function(const ::std::vector<GiNaC::ex> &exvec)>>(::std::bind(
                        &BlockProto::blkf, &block, ::std::placeholders::_1, true));

                symbolicFunctions.push_back(f);
                symbolicFunctionByPtr[&block] = f;
#endif

                traitsByPtr[&block] = bt;
                blockById[static_cast<BlockProto *>(&block)->id] = &block;
            }

            void append()
            {
                return;
            }

            void makeGraph();

            bool contains(BlockProto *blk) const;

            bool contains(unsigned int idx) const;

            bool hasDirectFeedthrough(BlockProto *blk) const;

            bool hasDirectFeedthrough(BlockProto &blk) const;

            bool isDriving(BlockProto *blk1, BlockProto *blk2) const;

            bool isDriving(BlockProto &blk1, BlockProto &blk2) const;

            ::std::shared_ptr<BlockTraits> getTraitsByPtr(const BlockProto *ptr) const;

            ::std::shared_ptr<BlockTraits> getTraitsById(unsigned int id) const;

            BlockProto *getBlockById(unsigned int id);

            const BlockProto *getBlockById(unsigned int id) const;

            ::std::vector<BlockProto *> blocks;
            ::std::vector<::std::shared_ptr<BlockTraits>> blockTraits;
            ::std::unordered_map<const BlockProto *, ::std::shared_ptr<BlockTraits>> traitsByPtr;
            ::std::unordered_map<unsigned int, BlockProto *> blockById;
            ls::blocks::aux::DirectedGraph graph;

#ifdef LS_USE_GINAC

            ::std::shared_ptr<::std::vector<GiNaC::ex>> getInputSymbolsByPtr(const BlockProto *ptr) const;

            ::std::shared_ptr<::std::vector<GiNaC::ex>> getOutputSymbolsByPtr(const BlockProto *ptr) const;

            ::std::shared_ptr<::std::vector<GiNaC::ex>> getParameterSymbolsByPtr(const BlockProto *ptr) const;

            ::std::shared_ptr<::std::vector<GiNaC::ex>> getInputSymbolsById(unsigned int id) const;

            ::std::shared_ptr<::std::vector<GiNaC::ex>> getOutputSymbolsById(unsigned int id) const;

            ::std::shared_ptr<::std::vector<GiNaC::ex>> getParameterSymbolsById(unsigned int id) const;

            ::std::shared_ptr<::std::function<const GiNaC::function(const ::std::vector<GiNaC::ex> &exvec)>> getSymbolicFunctionByPtr(const BlockProto *ptr) const;

            ::std::shared_ptr<::std::function<const GiNaC::function(const ::std::vector<GiNaC::ex> &exvec)>> getSymbolicFunctionById(unsigned int id) const;

            ::std::vector<::std::shared_ptr<::std::vector<GiNaC::ex>>> inputSymbols, outputSymbols, parameterSymbols;
            ::std::unordered_map<const BlockProto *, ::std::shared_ptr<::std::vector<GiNaC::ex>>> inputSymbolsByPtr, outputSymbolsByPtr, parameterSymbolsByPtr;

            ::std::vector<::std::shared_ptr<::std::function<const GiNaC::function(const ::std::vector<GiNaC::ex> &exvec)>>> symbolicFunctions;

            ::std::unordered_map<const BlockProto *, ::std::shared_ptr<::std::function<const GiNaC::function(const ::std::vector<GiNaC::ex> &exvec)>>> symbolicFunctionByPtr;
#endif
        };
    }
}


#endif //LODESTAR_BLOCKPACK_HPP
