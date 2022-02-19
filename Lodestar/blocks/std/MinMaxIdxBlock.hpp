//
// Created by Hamza El-Kebir on 2/19/22.
//

#ifndef LODESTAR_MINMAXIDXBLOCK_HPP
#define LODESTAR_MINMAXIDXBLOCK_HPP

#include <Lodestar/blocks/Block.hpp>
#include <Lodestar/aux/TemplateTools.hpp>

#include <Eigen/Dense>

namespace ls {
    namespace blocks {
        namespace std {
            /**
             * @enum ls::blocks::std::MinMaxIdxBlockOperator
             * @brief Operation types for @c MinMaxIdxBlock.
             */
            enum class MinMaxIdxBlockOperator {
                /// Minimum.
                Min,
                /// Maximum
                Max
            };

#define OUTPUT_MINMAXIDXBLOCK() \
    typename ::std::conditional<ls::aux::TemplateTraits::BinaryOperators::parseMatrixLike<TInput>::value, typename ls::aux::TemplateTraits::BinaryOperators::parseMatrixLike<TInput>::scalar, TInput>::type

            template<typename TInput, MinMaxIdxBlockOperator TOps>
            class MinMaxIdxBlock
                    : public Block<
                            ::std::tuple<TInput>,
                            ::std::tuple<int, int, OUTPUT_MINMAXIDXBLOCK()>,
                            BlockProto::empty
                    > {
            public:
                using Base =
                Block<
                        ::std::tuple<TInput>,
                        ::std::tuple<int, int, OUTPUT_MINMAXIDXBLOCK()>,
                        BlockProto::empty
                >;

                using InputTrait = ls::aux::TemplateTraits::BinaryOperators::parseMatrixLike<TInput>;
                static_assert(InputTrait::value, "Input must be matrix-like; otherwise same value would be returned.");

                /// Utility type alias for @c MinMaxIdxBlockOperator.
                using Ops = MinMaxIdxBlockOperator;

                /// Utility alias for minimum.
                static constexpr Ops Min = Ops::Min;

                /// Utility alias for maximum.
                static constexpr Ops Max = Ops::Max;

                using OutputType = OUTPUT_MINMAXIDXBLOCK();

                MinMaxIdxBlock()
                {
                    bindFunction();
                }


            protected:
                template<MinMaxIdxBlockOperator TTOps = TOps,
                        typename ::std::enable_if<TTOps == Min>::type * = nullptr>
                void bindFunction()
                {
                    this->equation = [](Base &b) -> void {
                        static Eigen::Index minRow, minCol;

                        b.template o<2>() = b.template i<0>().object.minCoeff(&minRow, &minCol);
                        b.template o<0>() = minRow;
                        b.template o<1>() = minCol;
                    };
                }

                template<MinMaxIdxBlockOperator TTOps = TOps,
                        typename ::std::enable_if<TTOps == Max>::type * = nullptr>
                void bindFunction()
                {
                    this->equation = [](Base &b) -> void {
                        static Eigen::Index maxRow, maxCol;

                        b.template o<2>() = b.template i<0>().object.maxCoeff(&maxRow, &maxCol);
                        b.template o<0>() = maxRow;
                        b.template o<1>() = maxCol;
                    };
                }
            };
        }

        template<typename TInput, std::MinMaxIdxBlockOperator TOps>
        class BlockTraits<std::MinMaxIdxBlock<TInput, TOps>> {
        public:
            static constexpr const BlockType blockType = BlockType::MinMaxIdxBlock;
            enum {
                directFeedthrough = true
            };

            using type = std::MinMaxIdxBlock<TInput, TOps>;
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

        template<typename TInput, std::MinMaxIdxBlockOperator TOps>
        const ::std::array<::std::string, BlockTraits<std::MinMaxIdxBlock<TInput, TOps>>::kIns> BlockTraits<std::MinMaxIdxBlock<TInput, TOps>>::inTypes =
                {demangle(typeid(TInput).name())};

        template<typename TInput, std::MinMaxIdxBlockOperator TOps>
        const ::std::array<::std::string, BlockTraits<std::MinMaxIdxBlock<TInput, TOps>>::kOuts> BlockTraits<std::MinMaxIdxBlock<TInput, TOps>>::outTypes =
                {"int", "int", demangle(typeid(std::MinMaxIdxBlock<TInput, TOps>::OutputType).name())};

        template<typename TInput, std::MinMaxIdxBlockOperator TOps>
        const ::std::array<::std::string, BlockTraits<std::MinMaxIdxBlock<TInput, TOps>>::kPars> BlockTraits<std::MinMaxIdxBlock<TInput, TOps>>::parTypes =
                {};

        template<typename TInput, std::MinMaxIdxBlockOperator TOps>
        const ::std::array<::std::string, 2> BlockTraits<std::MinMaxIdxBlock<TInput, TOps>>::templateTypes =
                {demangle(typeid(TInput).name()), demangle(typeid(TOps).name())};
    }
}


#endif //LODESTAR_MINMAXIDXBLOCK_HPP
