//
// Created by Hamza El-Kebir on 12/23/21.
//

#ifndef LODESTAR_CONVERTERBLOCK_HPP
#define LODESTAR_CONVERTERBLOCK_HPP

#include "Lodestar/blocks/Block.hpp"

namespace ls {
    namespace blocks {
        namespace std {
            template<typename TInput, typename TOutput>
            class ConverterBlock :
                    public Block<
                            ::std::tuple<TInput>,
                            ::std::tuple<TOutput>,
                            BlockProto::empty
                    > {
                static_assert(::std::is_convertible<TInput, TOutput>::value,
                              "Input and output types must be convertible.");

            public:
                using Base =
                Block<
                        ::std::tuple<TInput>,
                        ::std::tuple<TOutput>,
                        BlockProto::empty
                >;

                ConverterBlock()
                {
                    bindEquation();
                }

            protected:
                void bindEquation()
                {
                    this->equation = ::std::bind(
                            &ConverterBlock<TInput, TOutput>::triggerFunction,
                            this,
                            ::std::placeholders::_1
                    );
                }

                void triggerFunction(Base &b)
                {
                    b.template o<0>() = b.template i<0>();
                }

            };
        }

        template<typename TInput, typename TOutput>
        class BlockTraits<std::ConverterBlock<TInput, TOutput>> {
        public:
            static constexpr const BlockType blockType = BlockType::ConverterBlock;
            static constexpr const bool directFeedthrough = true;

            using type = std::ConverterBlock<TInput, TOutput>;
            using Base = typename type::Base;

            static const constexpr int kIns = type::Base::kIns;
            static const constexpr int kOuts = type::Base::kOuts;
            static const constexpr int kPars = type::Base::kPars;
        };
    }
}


#endif //LODESTAR_CONVERTERBLOCK_HPP
