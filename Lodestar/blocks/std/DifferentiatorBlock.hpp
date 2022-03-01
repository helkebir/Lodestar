//
// Created by Hamza El-Kebir on 2/24/22.
//

#ifndef LODESTAR_DIFFERENTIATORBLOCK_HPP
#define LODESTAR_DIFFERENTIATORBLOCK_HPP


#include "Lodestar/blocks/Block.hpp"
#include "Lodestar/aux/ArrayStack.hpp"
#include "Lodestar/primitives/differentiators/AdaptiveBackwardDifference.hpp"

namespace ls {
    namespace blocks {
        namespace std {
            template<typename TInput, unsigned int NHorizon=1, typename TScalar = float>
            class DifferentiatorBlock
                    : public Block<
                            ::std::tuple<TInput>,
                            ::std::tuple<TInput>,
                            ::std::tuple<TScalar>
                    > {
            public:
                using Base =
                Block<
                        ::std::tuple<TInput>,
                        ::std::tuple<TInput>,
                        ::std::tuple<TScalar>
                >;

                DifferentiatorBlock()
                {
                    bindFunction();
                }

                void clear(TInput value)
                {
                    fifoStack_.fill(value);
                    this->template o<0>() = value;
                    fifoStack_.clear();
                }

                void clear(TInput &value)
                {
                    fifoStack_.fill(value);
                    this->template o<0>() = value;
                    fifoStack_.clear();
                }

                TScalar &samplingPeriod()
                {
                    return this->template p<0>();
                }

                TScalar &samplingPeriod(const TScalar t)
                {
                    this->template p<0>() = t;
                    return this->template p<0>();
                }

                TScalar samplingPeriod() const
                {
                    return this->template p<0>();
                }


            protected:
                ls::aux::ArrayStack<TInput, NHorizon+1> fifoStack_;

                void bindFunction()
                {
                    this->equation = ::std::bind(
                            &DifferentiatorBlock<TInput, NHorizon, TScalar>::triggerFunction,
                            this,
                            ::std::placeholders::_1
                    );
                }

                void triggerFunction(Base &b)
                {
                    fifoStack_.push(b.template i<0>().object);
                    if (fifoStack_.size() > 1) {
                        b.template o<0>() = ls::primitives::AdaptiveBackwardDifference<TInput, 1, TScalar>::compute(samplingPeriod(), fifoStack_.array(), fifoStack_.size());
                    }
                }
            };
        }

        template<typename TInput, unsigned int NDelay, typename TScalar>
        class BlockTraits<std::DifferentiatorBlock<TInput, NDelay, TScalar>> {
        public:
            static constexpr const BlockType blockType = BlockType::DifferentiatorBlock;
            enum {
                directFeedthrough = (NDelay > 0)
            };

            using type = std::DifferentiatorBlock<TInput, NDelay, TScalar>;
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

        template<typename TInput, unsigned int NDelay, typename TScalar>
        const ::std::array<::std::string, BlockTraits<std::DifferentiatorBlock<TInput, NDelay, TScalar>>::kIns> BlockTraits<std::DifferentiatorBlock<TInput, NDelay, TScalar>>::inTypes =
                {demangle(typeid(TInput).name())};

        template<typename TInput, unsigned int NDelay, typename TScalar>
        const ::std::array<::std::string, BlockTraits<std::DifferentiatorBlock<TInput, NDelay, TScalar>>::kOuts> BlockTraits<std::DifferentiatorBlock<TInput, NDelay, TScalar>>::outTypes =
                {demangle(typeid(TInput).name())};

        template<typename TInput, unsigned int NDelay, typename TScalar>
        const ::std::array<::std::string, BlockTraits<std::DifferentiatorBlock<TInput, NDelay, TScalar>>::kPars> BlockTraits<std::DifferentiatorBlock<TInput, NDelay, TScalar>>::parTypes =
                {demangle(typeid(TScalar).name())};

        template<typename TInput, unsigned int NDelay, typename TScalar>
        const ::std::array<::std::string, 2> BlockTraits<std::DifferentiatorBlock<TInput, NDelay, TScalar>>::templateTypes =
                {demangle(typeid(TInput).name()), "unsigned int"};
    }
}


#endif //LODESTAR_DIFFERENTIATORBLOCK_HPP
