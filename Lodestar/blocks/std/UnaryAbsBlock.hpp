//
// Created by Hamza El-Kebir on 2/19/22.
//

#ifndef LODESTAR_UNARYABSBLOCK_HPP
#define LODESTAR_UNARYABSBLOCK_HPP


#include <Lodestar/blocks/Block.hpp>
#include <Lodestar/aux/TemplateTools.hpp>

namespace ls {
    namespace blocks {
        namespace std {
            template<typename TInput>
            class UnaryAbsBlock
                    : public Block<
                            ::std::tuple<TInput>,
                            ::std::tuple<TInput>,
                            BlockProto::empty
                    > {
            public:
                using Base =
                Block<
                        ::std::tuple<TInput>,
                        ::std::tuple<TInput>,
                        BlockProto::empty
                >;

                using InputTrait = ls::aux::TemplateTraits::BinaryOperators::parseMatrixLike<TInput>;

                UnaryAbsBlock()
                {
                    bindFunction();
                }


            protected:
                template<typename TTInput = TInput, typename ::std::enable_if<ls::aux::TemplateTraits::BinaryOperators::parseMatrixLike<TTInput>::value>::type * = nullptr>
                void bindFunction()
                {
                    this->equation = [](Base &b) -> void {
                        b.template o<0>().object = b.template i<0>().object;
                        b.template o<0>().object = b.template o<0>().object.unaryExpr([] (typename InputTrait::scalar s) -> typename InputTrait::scalar {
                            return abs(s);
                        });
                        b.template o<0>().propagate();
                    };
                }

                template<typename TTInput = TInput, typename ::std::enable_if<::std::is_same<TTInput, typename ls::aux::TemplateTraits::BinaryOperators::parseMatrixLike<TTInput>::scalar>::value>::type * = nullptr>
                void bindFunction()
                {
                    this->equation = [](Base &b) -> void {
                        b.template o<0>() = (b.template i<0>().object < 0) ? (-b.template i<0>().object) : b.template i<0>().object;
                    };
                }
            };
        }

        template<typename TInput>
        class BlockTraits<std::UnaryAbsBlock<TInput>> {
        public:
            static constexpr const BlockType blockType = BlockType::UnaryAbsBlock;
            enum {
                directFeedthrough = true
            };

            using type = std::UnaryAbsBlock<TInput>;
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
        const ::std::array<::std::string, BlockTraits<std::UnaryAbsBlock<TInput>>::kIns> BlockTraits<std::UnaryAbsBlock<TInput>>::inTypes =
                {demangle(typeid(TInput).name())};

        template<typename TInput>
        const ::std::array<::std::string, BlockTraits<std::UnaryAbsBlock<TInput>>::kOuts> BlockTraits<std::UnaryAbsBlock<TInput>>::outTypes =
                {demangle(typeid(TInput).name())};

        template<typename TInput>
        const ::std::array<::std::string, BlockTraits<std::UnaryAbsBlock<TInput>>::kPars> BlockTraits<std::UnaryAbsBlock<TInput>>::parTypes =
                {};

        template<typename TInput>
        const ::std::array<::std::string, 1> BlockTraits<std::UnaryAbsBlock<TInput>>::templateTypes =
                {demangle(typeid(TInput).name())};
    }
}


#endif //LODESTAR_UNARYABSBLOCK_HPP
