//
// Created by Hamza El-Kebir on 12/23/21.
//

#ifndef LODESTAR_SUMBLOCK_HPP
#define LODESTAR_SUMBLOCK_HPP


#include "Lodestar/blocks/Block.hpp"
#include "Lodestar/aux/TemplateTools.hpp"

namespace Eigen {
    template<typename T>
    class EigenBase;
}

namespace ls {
    namespace blocks {
        namespace std {
            enum class SumBlockOperator {
                Plus,
                Minus
            };

            struct SumBlockOperatorHelper {
                template<unsigned int N>
                static typename ls::aux::TemplateTools::repeat<SumBlockOperator, N, ::std::tuple>::type
                repeatTuple(SumBlockOperator value = SumBlockOperator::Plus)
                {
                    typename ls::aux::TemplateTools::repeat<SumBlockOperator, N, ::std::tuple>::type tuple{};
                    repeatTupleImpl<N, N - 1>(tuple, value);

                    return tuple;
                }

                template<unsigned int N, int TIdx = N - 1,
                        typename ::std::enable_if<(TIdx >
                                                   0), bool>::type * = nullptr>
                static void repeatTupleImpl(
                        typename ls::aux::TemplateTools::repeat<SumBlockOperator, N, ::std::tuple>::type &tuple,
                        SumBlockOperator value)
                {
                    ::std::get<TIdx>(tuple) = value;
                    return repeatTupleImpl<N, TIdx - 1>(tuple, value);
                }

                template<unsigned int N, int TIdx = N - 1,
                        typename ::std::enable_if<(TIdx ==
                                                   0), bool>::type * = nullptr>
                static void repeatTupleImpl(
                        typename ls::aux::TemplateTools::repeat<SumBlockOperator, N, ::std::tuple>::type &tuple,
                        SumBlockOperator value)
                {
                    ::std::get<0>(tuple) = value;
                }

                template<unsigned int N, int TIdx = N -
                                                    1, typename ::std::enable_if<(
                        TIdx <
                        0), bool>::type * = nullptr>
                static void repeatTupleImpl(
                        typename ls::aux::TemplateTools::repeat<SumBlockOperator, N, ::std::tuple>::type &tuple,
                        SumBlockOperator value)
                {
                    return;
                }

                static inline int interpret(SumBlockOperator value)
                {
                    switch (value) {
                        default:
                        case SumBlockOperator::Plus:
                            return 1;
                        case SumBlockOperator::Minus:
                            return -1;
                    }
                }
            };

            template<typename TType, unsigned int N>
            class SumBlock :
                    public Block<
                            typename ls::aux::TemplateTools::repeat<TType, N, ::std::tuple>::type,
                            ::std::tuple<TType>,
                            ::std::tuple<typename ls::aux::TemplateTools::repeat<SumBlockOperator, N, ::std::tuple>::type, TType>
                    > {
            public:
                using Base =
                Block<
                        typename ls::aux::TemplateTools::repeat<TType, N, ::std::tuple>::type,
                        ::std::tuple<TType>,
                        ::std::tuple<typename ls::aux::TemplateTools::repeat<SumBlockOperator, N, ::std::tuple>::type, TType>
                >;

                using Ops = SumBlockOperator;

                static constexpr const SumBlockOperator Plus = SumBlockOperator::Plus;
                static constexpr const SumBlockOperator Minus = SumBlockOperator::Minus;
                //    template <int TIdx>
                //    using Base::template o<TIdx>;

                //    using Base::getInput;

                //    template <size_t TIdx>
                //    auto i() const
                //    {
                //        auto i_impl = Base::template i<size_t>();
                //
                //        i_impl();
                //    }

                SumBlock()
                {
                    ::std::get<0>(this->params) = SumBlockOperatorHelper::repeatTuple<N>(
                            SumBlockOperator::Plus);
                    bindEquation();
                    //        getInput<0>();
                    //        getInput<0>();
                    //        Base::template i<0>();
                    //        this->equation = [&](Base & b) {
                    //            b.template o<0>() = sum();
                    //        };
                }

                template<typename... TOperators>
                SumBlock(Ops op, TOperators... ops)
                {
                    this->params = SumBlockOperatorHelper::repeatTuple<N>(
                            SumBlockOperator::Plus);
                    setOperators(op, ops...);
                    bindEquation();
                }

                template<int TIdx = 0, typename... TOperators, typename ::std::enable_if<
                        TIdx < N, bool>::type * = nullptr>
                void setOperators(Ops op, TOperators... ops)
                {
                    static_assert(
                            ls::aux::TemplateTraits::allSame<SumBlockOperator, TOperators...>::value,
                            "Operators must all be SumBlockOperator values."
                    );

                    ::std::get<TIdx>(::std::get<0>(this->params)) = op;

                    return setOperators<TIdx + 1>(ops...);
                }

                template<int TIdx = 0, typename... TOperators,
                        typename ::std::enable_if<
                                TIdx >= N, bool>::type * = nullptr>
                void setOperators(Ops op, TOperators... ops)
                {
                    return;
                }

                template<int TIdx = 0,
                        typename ::std::enable_if<
                                TIdx < N, bool>::type * = nullptr>
                void setOperators(Ops op)
                {
                    ::std::get<TIdx>(::std::get<0>(this->params)) = op;
                }

                template<int TIdx = 0, typename ::std::enable_if<
                        TIdx >= N, bool>::type * = nullptr>
                void setOperators(Ops op)
                {
                    return;
                }

                TType &
                zero()
                {
                    return this->template p<1>();
                }

            protected:
                void bindEquation()
                {
                    this->equation = ::std::bind(
                            &SumBlock<TType, N>::triggerFunction,
                            this,
                            ::std::placeholders::_1);
                }

                void triggerFunction(Base &b)
                {
                    b.template o<0>() = sum(zero());
                }

                template<unsigned int TIdx = Base::kIns - 1>
                typename ::std::enable_if<(TIdx > 0), TType>::type
                sum(TType value)
                {
                    return sum<TIdx - 1>(
                            value +
                            SumBlockOperatorHelper::interpret(
                                    ::std::get<TIdx>(this->template p<0>())) *
                            this->template i<TIdx>());
                }

                template<unsigned int TIdx = Base::kIns - 1>
                typename ::std::enable_if<(TIdx == 0), TType>::type
                sum(TType value)
                {
                    return value +
                           SumBlockOperatorHelper::interpret(
                                   ::std::get<TIdx>(this->template p<0>())) *
                           this->template i<TIdx>();
                }

                template<unsigned int TIdx = Base::kIns - 1>
                typename ::std::enable_if<(TIdx < 0), TType>::type
                sum(TType value)
                {
                    return value;
                }
            };
        }

        template<typename TType, unsigned int N>
        class BlockTraits<std::SumBlock<TType, N>> {
        public:
            static constexpr const BlockType blockType = BlockType::SumBlock;
            static constexpr const bool directFeedthrough = true;

            using type = std::SumBlock<TType, N>;
            using Base = typename type::Base;

            static const constexpr int kIns = type::Base::kIns;
            static const constexpr int kOuts = type::Base::kOuts;
            static const constexpr int kPars = type::Base::kPars;
        };
    }
}


#endif //LODESTAR_SUMBLOCK_HPP