//
// Created by Hamza El-Kebir on 12/23/21.
//

#ifndef LODESTAR_SIGNUMBLOCK_HPP
#define LODESTAR_SIGNUMBLOCK_HPP

#include "blocks/Block.hpp"

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
    }
}


#endif //LODESTAR_SIGNUMBLOCK_HPP
