//
// Created by Hamza El-Kebir on 2/19/22.
//

#ifndef LODESTAR_UNARYMEANBLOCK_HPP
#define LODESTAR_UNARYMEANBLOCK_HPP

#include <Lodestar/blocks/Block.hpp>
#include <Lodestar/aux/TemplateTools.hpp>

namespace ls {
    namespace blocks {
        namespace std {
#define OUTPUT_UNARYMEANBLOCK() \
    typename ::std::conditional<ls::aux::TemplateTraits::BinaryOperators::parseMatrixLike<TInput>::value, typename ls::aux::TemplateTraits::BinaryOperators::parseMatrixLike<TInput>::scalar, TInput>::type

            template<typename TInput>
            class UnaryMeanBlock
                    : public Block<
                            ::std::tuple<TInput>,
                            ::std::tuple<OUTPUT_UNARYMEANBLOCK()>,
                            BlockProto::empty
                    > {
            public:
                using Base =
                Block<
                        ::std::tuple<TInput>,
                        ::std::tuple<OUTPUT_UNARYMEANBLOCK()>,
                        BlockProto::empty
                >;

                using InputTrait = ls::aux::TemplateTraits::BinaryOperators::parseMatrixLike<TInput>;
                static_assert(InputTrait::value, "Input must be matrix-like; otherwise same value would be returned.");

                using OutputType = OUTPUT_UNARYMEANBLOCK();

                UnaryMeanBlock()
                {
                    bindFunction();
                }


            protected:
                void bindFunction()
                {
                    this->equation = [](Base &b) -> void {
                        b.template o<0>() = b.template i<0>().object.mean();
                    };
                }
            };
        }

        template<typename TInput>
        class BlockTraits<std::UnaryMeanBlock<TInput>> {
        public:
            static constexpr const BlockType blockType = BlockType::UnaryMeanBlock;
            enum {
                directFeedthrough = true
            };

            using type = std::UnaryMeanBlock<TInput>;
            using Base = typename type::Base;

            enum {
                kIns = Base::kIns,
                kOuts = Base::kOuts,
                kPars = Base::kPars
            };

            static const ::std::array<::std::string, kIns> inTypes;
            static const ::std::array<::std::string, kOuts> outTypes;
            static const ::std::array<::std::string, kPars> parTypes;

            static const ::std::array<::std::string, 1> templateTypes;
        };

        template<typename TInput>
        const ::std::array<::std::string, BlockTraits<std::UnaryMeanBlock<TInput>>::kIns> BlockTraits<std::UnaryMeanBlock<TInput>>::inTypes =
                {demangle(typeid(TInput).name())};

        template<typename TInput>
        const ::std::array<::std::string, BlockTraits<std::UnaryMeanBlock<TInput>>::kOuts> BlockTraits<std::UnaryMeanBlock<TInput>>::outTypes =
                {demangle(typeid(typename std::UnaryMeanBlock<TInput>::OutputType).name())};

        template<typename TInput>
        const ::std::array<::std::string, BlockTraits<std::UnaryMeanBlock<TInput>>::kPars> BlockTraits<std::UnaryMeanBlock<TInput>>::parTypes =
                {};

        template<typename TInput>
        const ::std::array<::std::string, 1> BlockTraits<std::UnaryMeanBlock<TInput>>::templateTypes =
                {demangle(typeid(TInput).name())};
    }
}

#undef OUTPUT_UNARYMEANBLOCK

#endif //LODESTAR_UNARYMEANBLOCK_HPP
