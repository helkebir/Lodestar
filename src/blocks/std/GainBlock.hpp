//
// Created by Hamza El-Kebir on 12/23/21.
//

#ifndef LODESTAR_GAINBLOCK_HPP
#define LODESTAR_GAINBLOCK_HPP

#include "blocks/Block.hpp"
#include "aux/TemplateTools.hpp"

namespace ls {
    namespace blocks {
        namespace std {
            enum class GainBlockOperator {
                Left,
                Right,
                Convolve,
                ElementWise
            };

            template<typename TInput, typename TOutput = TInput, typename TGain = TInput>
            class GainBlock :
                    public Block<
                            ::std::tuple<TInput>,
                            ::std::tuple<TOutput>,
                            ::std::tuple<TGain, GainBlockOperator>
                    > {
            public:
                using Base =
                Block<
                        ::std::tuple<TInput>,
                        ::std::tuple<TOutput>,
                        ::std::tuple<TGain, GainBlockOperator>
                >;

                using Ops = GainBlockOperator;

                static constexpr GainBlockOperator Left = Ops::Left;
                static constexpr GainBlockOperator Right = Ops::Right;
                static constexpr GainBlockOperator Convolve = Ops::Convolve;
                static constexpr GainBlockOperator ElementWise = Ops::ElementWise;

                GainBlock(const Ops op = Left)
                {
                    setOperator(op);
                    bindEquation();
                }

                GainBlock(const TGain &gain, const Ops op = Left)
                {
                    setOperator(op);
                    this->template p<0>() = gain;
                    bindEquation();
                }

                void setGain(const TGain &gain)
                {
                    this->template p<0>() = gain;
                }

                const TGain &getGain() const
                {
                    return this->template p<0>();
                }

                void setOperator(Ops op)
                {
                    this->template p<1>() = op;
                }

                Ops getOperator()
                {
                    return this->template p<1>();
                }

                typename ::std::tuple_element<0, typename Base::Params>::type &
                gain()
                {
                    return this->template p<0>();
                }

                const typename ::std::tuple_element<0, typename Base::Params>::type &
                gain() const
                {
                    return this->template p<0>();
                }

            protected:
                void bindEquation()
                {
                    this->equation = ::std::bind(
                            &GainBlock<TInput, TOutput, TGain>::triggerFunction,
                            this,
                            ::std::placeholders::_1
                    );
                }

                typename ::std::enable_if<true, void>::type
                triggerFunction(Base &b)
                {
                    // TODO: Implement convolution.
                    switch (getOperator()) {
                        default:
                        case Left:
                            b.template o<0>() =
                                    b.template p<0>() * b.template i<0>();
                            break;
                        case Right:
                            b.template o<0>() =
                                    b.template i<0>() * b.template p<0>();
                            break;
                    }
                }

                // Integrity checking

                template<typename TTInput = TInput, typename TTOutput = TOutput, typename TTGain = TGain>
                struct condition_number {
                    static constexpr size_t value = 1;
                };

                template<typename TTInput>
                struct condition_number<TTInput, TTInput, TTInput> {
                    static constexpr size_t value = 0;
                };

                template<size_t TCondition = condition_number<TInput, TOutput, TGain>::value, typename TTInput = TInput, typename TTOutput = TOutput, typename TTGain = TGain>
                struct integrity_check {
                    static constexpr bool value = true;
                };

                template<typename TTInput, typename TTOutput, typename TTGain>
                struct integrity_check<1, TTInput, TTOutput, TTGain> {
                    static_assert(
                            aux::TemplateTraits::allSame<TTInput, TTOutput, TTGain>::value,
                            "Input, output, and gain type should be the same for a GainBlock.");
                    static constexpr bool value = true;
                };

                static_assert(integrity_check<>::value,
                              "Integrity check failed.");
            };

            // TODO: Add Eigen specialization with compile time checking of dimensions.
        }

        template<typename TInput, typename TOutput, typename TGain>
        class BlockTraits<std::GainBlock<TInput, TOutput, TGain>> {
        public:
            static constexpr const BlockType blockType = BlockType::GainBlock;
            static constexpr const bool directFeedthrough = true;

            using type = std::GainBlock<TInput, TOutput, TGain>;
            using Base = typename type::Base;

            static const constexpr int kIns = type::Base::kIns;
            static const constexpr int kOuts = type::Base::kOuts;
            static const constexpr int kPars = type::Base::kPars;
        };
    }
}


#endif //LODESTAR_GAINBLOCK_HPP
