//
// Created by Hamza El-Kebir on 12/23/21.
//

#ifndef LODESTAR_CONSTANTBLOCK_HPP
#define LODESTAR_CONSTANTBLOCK_HPP

#include "Lodestar/blocks/Block.hpp"

namespace ls {
    namespace blocks {
        namespace std {
            template<typename TType>
            class ConstantBlock :
                    public Block<
                            BlockProto::empty,
                            ::std::tuple<TType>,
                            ::std::tuple<TType>
                    > {
            public:
                using Base =
                Block<
                        BlockProto::empty,
                        ::std::tuple<TType>,
                        ::std::tuple<TType>
                >;

                ConstantBlock()
                {
                    bindEquation();
                }

                ConstantBlock(const TType &constant)
                {
                    this->template p<0>() = constant;
                    bindEquation();
                }

                typename ::std::tuple_element<0, typename Base::Params>::type &
                constant()
                {
                    return this->template p<0>();
                }

                const typename ::std::tuple_element<0, typename Base::Params>::type &
                constant() const
                {
                    return this->template p<0>();
                }

            protected:
                void bindEquation()
                {
                    this->equation = ::std::bind(
                            &ConstantBlock<TType>::triggerFunction,
                            this,
                            ::std::placeholders::_1
                    );
                }

                void triggerFunction(Base &b)
                {
                    b.template o<0>() = b.template p<0>();
                }
            };
        }

        template<typename TType>
        class BlockTraits<std::ConstantBlock<TType>> {
        public:
            static constexpr const BlockType blockType = BlockType::ConstantBlock;
            enum {
                directFeedthrough = true
            };

            using type = std::ConstantBlock<TType>;
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

        template<typename TType>
        const ::std::array<::std::string, BlockTraits<std::ConstantBlock<TType>>::kIns> BlockTraits<std::ConstantBlock<TType>>::inTypes =
                {};

        template<typename TType>
        const ::std::array<::std::string, BlockTraits<std::ConstantBlock<TType>>::kOuts> BlockTraits<std::ConstantBlock<TType>>::outTypes =
                {demangle(typeid(TType).name())};

        template<typename TType>
        const ::std::array<::std::string, BlockTraits<std::ConstantBlock<TType>>::kPars> BlockTraits<std::ConstantBlock<TType>>::parTypes =
                {demangle(typeid(TType).name())};

        template<typename TType>
        const ::std::array<::std::string, 1> BlockTraits<std::ConstantBlock<TType>>::templateTypes =
                {demangle(typeid(TType).name())};
    }
}


#endif //LODESTAR_CONSTANTBLOCK_HPP
