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
            enum {
                directFeedthrough = true
            };

            using type = std::ConverterBlock<TInput, TOutput>;
            using Base = typename type::Base;

            enum {
                kIns = Base::kIns,
                kOuts = Base::kOuts,
                kPars = Base::kPars
            };

            static const ::std::array<::std::string, kIns> inTypes;
            static const ::std::array<::std::string, kOuts> outTypes;
            static const ::std::array<::std::string, kPars> parTypes;

            static const ::std::array<::std::string, 2> templateTypes;
        };

        template<typename TInput, typename TOutput>
        const ::std::array<::std::string, BlockTraits<std::ConverterBlock<TInput, TOutput>>::kIns> BlockTraits<std::ConverterBlock<TInput, TOutput>>::inTypes =
                {demangle(typeid(TInput).name())};

        template<typename TInput, typename TOutput>
        const ::std::array<::std::string, BlockTraits<std::ConverterBlock<TInput, TOutput>>::kOuts> BlockTraits<std::ConverterBlock<TInput, TOutput>>::outTypes =
                {demangle(typeid(TOutput).name())};

        template<typename TInput, typename TOutput>
        const ::std::array<::std::string, BlockTraits<std::ConverterBlock<TInput, TOutput>>::kPars> BlockTraits<std::ConverterBlock<TInput, TOutput>>::parTypes =
                {};

        template<typename TInput, typename TOutput>
        const ::std::array<::std::string, 2> BlockTraits<std::ConverterBlock<TInput, TOutput>>::templateTypes =
                {demangle(typeid(TInput).name()), demangle(typeid(TOutput).name())};
    }
}


#endif //LODESTAR_CONVERTERBLOCK_HPP
