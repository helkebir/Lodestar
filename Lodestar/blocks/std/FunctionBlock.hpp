//
// Created by Hamza El-Kebir on 12/23/21.
//

#ifndef LODESTAR_FUNCTIONBLOCK_HPP
#define LODESTAR_FUNCTIONBLOCK_HPP


#include "Lodestar/blocks/Block.hpp"
#include "Lodestar/aux/TemplateTools.hpp"

namespace ls {
    namespace blocks {
        namespace std {
            template<typename TOutput = int, typename... TInputs>
            class FunctionBlock :
                    public Block<
                            ::std::tuple<TInputs...>,
                            ::std::tuple<TOutput>,
                            ::std::tuple<::std::function<TOutput(TInputs...)>>
                    > {
            public:
                using Base =
                Block<
                        ::std::tuple<TInputs...>,
                        ::std::tuple<TOutput>,
                        ::std::tuple<::std::function<TOutput(TInputs...)>>
                >;
                // TODO: Decide whether additional TInput parameters should be TParameters or not.
                using Function = ::std::function<TOutput(TInputs...)>;

                FunctionBlock()
                {
                    bindEquation();
                }

                FunctionBlock(const Function &fun)
                {
                    this->template p<0>() = fun;
                    bindEquation();
                }

                template<typename TTOutput, typename... TTInputs>
                static FunctionBlock<TTOutput, TTInputs...>
                make(const ::std::function<TTOutput(TTInputs...)> &fun)
                {
                    return FunctionBlock<TTOutput, TTInputs...>{fun};
                }

            protected:
                void bindEquation()
                {
                    this->equation = ::std::bind(
                            &FunctionBlock<TOutput, TInputs...>::triggerFunction,
                            this,
                            ::std::placeholders::_1
                    );
                }

                void triggerFunction(Base &b)
                {
                    b.template o<0>() = ls::aux::TemplateTools::Executors::applyWrapped(
                            b.template p<0>(),
                            b.inputs);
                }
            };
        }

        template<typename TOutput, typename... TInputs>
        class BlockTraits<std::FunctionBlock<TOutput, TInputs...>> {
        public:
            static constexpr const BlockType blockType = BlockType::FunctionBlock;
            static constexpr const bool directFeedthrough = true;

            using type = std::FunctionBlock<TOutput, TInputs...>;
            using Base = typename type::Base;

            static const constexpr int kIns = type::Base::kIns;
            static const constexpr int kOuts = type::Base::kOuts;
            static const constexpr int kPars = type::Base::kPars;
        };
    }
}


#endif //LODESTAR_FUNCTIONBLOCK_HPP
