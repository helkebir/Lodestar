//
// Created by Hamza El-Kebir on 12/23/21.
//

#ifndef LODESTAR_CONSTANTBLOCK_HPP
#define LODESTAR_CONSTANTBLOCK_HPP

#include "blocks/Block.hpp"

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

//            static const constexpr int kIns = type::Base::kIns;
//            static const constexpr int kOuts = type::Base::kOuts;
//            static const constexpr int kPars = type::Base::kPars;
        };
    }
}


#endif //LODESTAR_CONSTANTBLOCK_HPP
