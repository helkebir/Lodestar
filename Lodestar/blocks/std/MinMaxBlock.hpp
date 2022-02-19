//
// Created by Hamza El-Kebir on 2/19/22.
//

#ifndef LODESTAR_MINMAXBLOCK_HPP
#define LODESTAR_MINMAXBLOCK_HPP

#include <Lodestar/blocks/Block.hpp>
#include <Lodestar/aux/TemplateTools.hpp>

namespace ls {
    namespace blocks {
        namespace std {
            /**
             * @enum ls::blocks::std::MinMaxBlockOperator
             * @brief Operation types for @c MinMaxBlock.
             */
            enum class MinMaxBlockOperator {
                /// Minimum.
                Min,
                /// Maximum
                Max
            };

#define OUTPUT_MINMAXBLOCK() \
    typename ::std::conditional<ls::aux::TemplateTraits::BinaryOperators::parseMatrixLike<TInput>::value, typename ls::aux::TemplateTraits::BinaryOperators::parseMatrixLike<TInput>::scalar, TInput>::type

            template<typename TInput, MinMaxBlockOperator TOps>
            class MinMaxBlock
                    : public Block<
                            ::std::tuple<TInput>,
                            ::std::tuple<OUTPUT_MINMAXBLOCK()>,
                            BlockProto::empty
                    > {
            public:
                using Base =
                Block<
                        ::std::tuple<TInput>,
                        ::std::tuple<OUTPUT_MINMAXBLOCK()>,
                        BlockProto::empty
                >;

                using InputTrait = ls::aux::TemplateTraits::BinaryOperators::parseMatrixLike<TInput>;
                static_assert(InputTrait::value, "Input must be matrix-like; otherwise same value would be returned.");

                /// Utility type alias for @c MinMaxBlockOperator.
                using Ops = MinMaxBlockOperator;

                /// Utility alias for minimum.
                static constexpr Ops Min = Ops::Min;

                /// Utility alias for maximum.
                static constexpr Ops Max = Ops::Max;

                using OutputType = OUTPUT_MINMAXBLOCK();

                MinMaxBlock()
                {
                    bindFunction();
                }


            protected:
                template<MinMaxBlockOperator TTOps = TOps,
                        typename ::std::enable_if<TTOps == Min>::type * = nullptr>
                void bindFunction()
                {
                    this->equation = [](Base &b) -> void {
                        b.template o<0>() = b.template i<0>().object.minCoeff();
                    };
                }

                template<MinMaxBlockOperator TTOps = TOps,
                        typename ::std::enable_if<TTOps == Max>::type * = nullptr>
                void bindFunction()
                {
                    this->equation = [](Base &b) -> void {
                        b.template o<0>() = b.template i<0>().object.maxCoeff();
                    };
                }
            };
        }

        template<typename TInput, std::MinMaxBlockOperator TOps>
        class BlockTraits<std::MinMaxBlock<TInput, TOps>> {
        public:
            static constexpr const BlockType blockType = BlockType::MinMaxBlock;
            enum {
                directFeedthrough = true
            };

            using type = std::MinMaxBlock<TInput, TOps>;
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

        template<typename TInput, std::MinMaxBlockOperator TOps>
        const ::std::array<::std::string, BlockTraits<std::MinMaxBlock<TInput, TOps>>::kIns> BlockTraits<std::MinMaxBlock<TInput, TOps>>::inTypes =
                {demangle(typeid(TInput).name())};

        template<typename TInput, std::MinMaxBlockOperator TOps>
        const ::std::array<::std::string, BlockTraits<std::MinMaxBlock<TInput, TOps>>::kOuts> BlockTraits<std::MinMaxBlock<TInput, TOps>>::outTypes =
                {demangle(typeid(typename std::MinMaxBlock<TInput, TOps>::OutputType).name())};

        template<typename TInput, std::MinMaxBlockOperator TOps>
        const ::std::array<::std::string, BlockTraits<std::MinMaxBlock<TInput, TOps>>::kPars> BlockTraits<std::MinMaxBlock<TInput, TOps>>::parTypes =
                {};

        template<typename TInput, std::MinMaxBlockOperator TOps>
        const ::std::array<::std::string, 2> BlockTraits<std::MinMaxBlock<TInput, TOps>>::templateTypes =
                {demangle(typeid(TInput).name()), demangle(typeid(TOps).name())};
    }
}

#undef OUTPUT_MINMAXBLOCK


#endif //LODESTAR_MINMAXBLOCK_HPP
