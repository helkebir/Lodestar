//
// Created by Hamza El-Kebir on 12/23/21.
//

#ifndef LODESTAR_SIGNUMBLOCK_HPP
#define LODESTAR_SIGNUMBLOCK_HPP

#include "Lodestar/blocks/Block.hpp"

namespace ls {
    namespace blocks {
        namespace std {
            template<typename TType, typename TOutput = int>
            class SignumBlock
                    : public Block<
                            ::std::tuple<TType>,
                            ::std::tuple<TOutput>,
                            BlockProto::empty
                    > {
            public:
                using Base =
                Block<
                        ::std::tuple<TType>,
                        ::std::tuple<TOutput>,
                        BlockProto::empty
                >;

                SignumBlock()
                {
                    bindFunction();
                }

                bool isPositive() const
                {
                    return (this->template o<0>() > 0);
                }

                bool isNegative() const
                {
                    return (this->template o<0>() < 0);
                }

                bool isZero() const
                {
                    return (this->template o<0>() == 0);
                }

                bool isNonNegative() const
                {
                    return (this->template o<0>() >= 0);
                }

                bool isNonPositive() const
                {
                    return (this->template o<0>() <= 0);
                }

            protected:
                void bindFunction()
                {
                    this->equation = ::std::bind(
                            &SignumBlock<TType, TOutput>::triggerFunction, this,
                            ::std::placeholders::_1);
                }

                void triggerFunction(Base &b)
                {
                    b.template o<0>() = (b.template i<0>() == 0 ? 0 : (
                            b.template i<0>() < 0 ? -1 : 1));
                }
            };
        }

        template<typename TType, typename TOutput>
        class BlockTraits<std::SignumBlock<TType, TOutput>> {
        public:
            static constexpr const BlockType blockType = BlockType::SignumBlock;
            enum {
                directFeedthrough = true
            };

            using type = std::SignumBlock<TType, TOutput>;
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

        template<typename TType, typename TOutput>
        const ::std::array<::std::string, BlockTraits<std::SignumBlock<TType, TOutput>>::kIns> BlockTraits<std::SignumBlock<TType, TOutput>>::inTypes =
                {demangle(typeid(TType).name())};

        template<typename TType, typename TOutput>
        const ::std::array<::std::string, BlockTraits<std::SignumBlock<TType, TOutput>>::kOuts> BlockTraits<std::SignumBlock<TType, TOutput>>::outTypes =
                {demangle(typeid(TOutput).name())};

        template<typename TType, typename TOutput>
        const ::std::array<::std::string, BlockTraits<std::SignumBlock<TType, TOutput>>::kPars> BlockTraits<std::SignumBlock<TType, TOutput>>::parTypes =
                {};

        template<typename TType, typename TOutput>
        const ::std::array<::std::string, 2> BlockTraits<std::SignumBlock<TType, TOutput>>::templateTypes =
                {demangle(typeid(TType).name()), demangle(typeid(TOutput).name())};
    }
}


#endif //LODESTAR_SIGNUMBLOCK_HPP
