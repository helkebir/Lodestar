//
// Created by Hamza El-Kebir on 12/23/21.
//

#ifndef LODESTAR_SUMBLOCK_HPP
#define LODESTAR_SUMBLOCK_HPP


#include "Lodestar/blocks/Block.hpp"
#include "Lodestar/aux/TemplateTools.hpp"

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
                            ::std::tuple<::std::array<SumBlockOperator, N>, TType>
                    > {
            public:
                using Base =
                Block<
                        typename ls::aux::TemplateTools::repeat<TType, N, ::std::tuple>::type,
                        ::std::tuple<TType>,
                        ::std::tuple<::std::array<SumBlockOperator, N>, TType>
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
                    (this->template p<0>()).fill(SumBlockOperator::Plus);
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
                    (this->template p<0>()).fill(SumBlockOperator::Plus);
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

                    (this->template p<0>())[TIdx] = op;

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
                    (this->template p<0>())[TIdx] = op;
                }

                template<int TIdx = 0, typename ::std::enable_if<
                        TIdx >= N, bool>::type * = nullptr>
                void setOperators(Ops op)
                {
                    return;
                }

                template<int TIdx = 0, typename ::std::enable_if<((TIdx == 0) && (TIdx != N))>::type * = nullptr>
                void getOperators(::std::vector<SumBlockOperator> &v)
                {
                    v.clear();
                    v.push_back(this->template p<0>()[0]);

                    return getOperators<TIdx+1>(v);
                }

                template<int TIdx = 0, typename ::std::enable_if<((TIdx > 0) && (TIdx < N))>::type * = nullptr>
                void getOperators(::std::vector<SumBlockOperator> &v)
                {
                    v.push_back(this->template p<0>()[TIdx]);

                    return getOperators<TIdx+1>(v);
                }

                template<int TIdx = 0, typename ::std::enable_if<((TIdx < 0) || (TIdx >= N))>::type * = nullptr>
                void getOperators(::std::vector<SumBlockOperator> &v)
                {
                    return;
                }

                TType &
                zero()
                {
                    return this->template p<1>();
                }

#ifdef LS_USE_GINAC

                const ::std::array<GiNaC::ex, Base::kIns> &inputSymbols()
                {
                    if (!this->isInitInput_) {
                        for (int i = 0; i < Base::kIns; i++) {
                            if (ls::aux::TemplateTraits::BinaryOperators::parseMatrixLike<TType>::value) {
                                GiNaC::lst input;
                                for (int ii = 0; ii <
                                                 ls::aux::TemplateTraits::BinaryOperators::parseMatrixLike<TType>::rows; ii++) {
                                    GiNaC::lst row;
                                    for (int jj = 0; jj <
                                                     ls::aux::TemplateTraits::BinaryOperators::parseMatrixLike<TType>::cols; jj++) {
                                        GiNaC::symbol entry{
                                                "blk" + ::std::to_string(this->id) + "_i_" + ::std::to_string(i) +
                                                "_r_" + ::std::to_string(ii) + "_c_" + ::std::to_string(jj),
                                                "\\text{BLK}^{i, " + ::std::to_string(i) + ", " + ::std::to_string(ii) +
                                                ", " + ::std::to_string(jj) + "}_{" + ::std::to_string(this->id) + "}"};

                                        row.append(entry);
                                    }
                                    input.append(row);
                                }

                                this->inputSymbols_[i] = GiNaC::lst_to_matrix(input);
                            } else {
                                this->inputSymbols_[i] = GiNaC::symbol{"blk" + ::std::to_string(this->id) + "_i_" + ::std::to_string(i),
                                                       "\\text{BLK}^{i, " + ::std::to_string(i) + "}_{" +
                                                       ::std::to_string(this->id) +
                                                       "}"};
                            }
                        }

                        this->isInitInput_ = true;
                    }

                    return this->inputSymbols_;
                }

                const ::std::array<GiNaC::ex, Base::kOuts> &outputSymbols()
                {
                    if (!this->isInitOutput_) {
                        for (int i = 0; i < Base::kOuts; i++) {
                            if (ls::aux::TemplateTraits::BinaryOperators::parseMatrixLike<TType>::value) {
                                GiNaC::lst output;
                                for (int ii = 0; ii <
                                                 ls::aux::TemplateTraits::BinaryOperators::parseMatrixLike<TType>::rows; ii++) {
                                    GiNaC::lst row;
                                    for (int jj = 0; jj <
                                                     ls::aux::TemplateTraits::BinaryOperators::parseMatrixLike<TType>::cols; jj++) {
                                        GiNaC::symbol entry{
                                                "blk" + ::std::to_string(this->id) + "_o_" + ::std::to_string(i) +
                                                "_r_" + ::std::to_string(ii) + "_c_" + ::std::to_string(jj),
                                                "\\text{BLK}^{i, " + ::std::to_string(i) + ", " + ::std::to_string(ii) +
                                                ", " + ::std::to_string(jj) + "}_{" + ::std::to_string(this->id) + "}"};

                                        row.append(entry);
                                    }
                                    output.append(row);
                                }

                                this->outputSymbols_[i] = GiNaC::lst_to_matrix(output);
                            } else {
                                this->outputSymbols_[i] = GiNaC::symbol{"blk" + ::std::to_string(this->id) + "_o_" + ::std::to_string(i),
                                                       "\\text{BLK}^{i, " + ::std::to_string(i) + "}_{" +
                                                       ::std::to_string(this->id) +
                                                       "}"};
                            }
                        }

                        this->isInitOutput_ = true;
                    }

                    return this->outputSymbols_;
                }

                const ::std::array<GiNaC::ex, 1> &parameterSymbols()
                {
                    if (!this->isInitParameter_) {

                        int i = 0;

                        if (ls::aux::TemplateTraits::BinaryOperators::parseMatrixLike<TType>::value) {
                            GiNaC::lst output;
                            for (int ii = 0;
                                 ii < ls::aux::TemplateTraits::BinaryOperators::parseMatrixLike<TType>::rows; ii++) {
                                GiNaC::lst row;
                                for (int jj = 0; jj <
                                                 ls::aux::TemplateTraits::BinaryOperators::parseMatrixLike<TType>::cols; jj++) {
                                    GiNaC::symbol entry{
                                            "blk" + ::std::to_string(this->id) + "_p_" + ::std::to_string(i) + "_r_" +
                                            ::std::to_string(ii) + "_c_" + ::std::to_string(jj),
                                            "\\text{BLK}^{i, " + ::std::to_string(i) + ", " + ::std::to_string(ii) +
                                            ", " + ::std::to_string(jj) + "}_{" + ::std::to_string(this->id) + "}"};

                                    row.append(entry);
                                }
                                output.append(row);
                            }

                            this->parameterSymbols_[i] = GiNaC::lst_to_matrix(output);
                        } else {
                            this->parameterSymbols_[i] = GiNaC::symbol{"blk" + ::std::to_string(this->id) + "_p_" + ::std::to_string(i),
                                                   "\\text{BLK}^{i, " + ::std::to_string(i) + "}_{" +
                                                   ::std::to_string(this->id) +
                                                   "}"};
                        }

                        Base::isInitParameter_ = true;
                    }

                    return this->parameterSymbols_;
                }

#endif

            protected:
#ifdef LS_USE_GINAC
                ::std::array<GiNaC::ex, 1> parameterSymbols_;
#endif

                void bindEquation()
                {
                    this->equation = ::std::bind(
                            &SumBlock<TType, N>::triggerFunction,
                            this,
                            ::std::placeholders::_1);

#ifdef LS_USE_GINAC
                    GiNaC::function_options fops("blkf" + ::std::to_string(this->id) + "__", this->blkFunc_NPARAMS);
                    ls::blocks::symbolicEvalFunctionMap[this->id] = [&](const ::std::vector<GiNaC::ex> &exvec) -> GiNaC::ex {
                        // GiNaC::ex res = this->parameterSymbols()[0];
                        GiNaC::ex res = 0;
                        int i = 0;

                        for (auto & ex : exvec) {
                            res += SumBlockOperatorHelper::interpret(this->template p<0>()[i]) * ex;

                            i++;
                        }

                        return res;
                    };

                    fops.eval_func(ls::blocks::symbolicEval);


                    this->serial = GiNaC::function::register_new(
                            fops
                    );
#endif
                }

                void triggerFunction(Base &b)
                {
                    b.template o<0>().object = zero();
                    sum(b.template o<0>().object);
                    b.template o<0>().propagate();
                }

                template<unsigned int TIdx = Base::kIns - 1>
                typename ::std::enable_if<(TIdx > 0), void>::type
                sum(TType &res)
                {
                    res = res +
                            SumBlockOperatorHelper::interpret(
                                    (this->template p<0>())[TIdx]) *
                            this->template i<TIdx>();
                    return sum<TIdx - 1>(res);
                }

                template<unsigned int TIdx = Base::kIns - 1>
                typename ::std::enable_if<(TIdx == 0), void>::type
                sum(TType &res)
                {
                    res = res +
                    SumBlockOperatorHelper::interpret((this->template p<0>())[TIdx]) * this->template i<TIdx>();
                }

                template<unsigned int TIdx = Base::kIns - 1>
                typename ::std::enable_if<(TIdx < 0), void>::type
                sum(TType &res)
                {
                    return;
                }
            };
        }

        template<typename TType, unsigned int N>
        class BlockTraits<std::SumBlock<TType, N>> {
        public:
            static constexpr const BlockType blockType = BlockType::SumBlock;
            enum {
                directFeedthrough = true
            };

            using type = std::SumBlock<TType, N>;
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

        template<typename TType, unsigned int N>
        const ::std::array<::std::string, BlockTraits<std::SumBlock<TType, N>>::kIns> BlockTraits<std::SumBlock<TType, N>>::inTypes =
                ls::aux::TemplateTools::create_array<BlockTraits<std::SumBlock<TType, N>>::kIns>(
                        demangle(typeid(TType).name())
                );

        template<typename TType, unsigned int N>
        const ::std::array<::std::string, BlockTraits<std::SumBlock<TType, N>>::kOuts> BlockTraits<std::SumBlock<TType, N>>::outTypes =
                {demangle(typeid(TType).name())};

        template<typename TType, unsigned int N>
        const ::std::array<::std::string, BlockTraits<std::SumBlock<TType, N>>::kPars> BlockTraits<std::SumBlock<TType, N>>::parTypes =
                {demangle(
                        typeid(::std::array<std::SumBlockOperator, N>).name()
                ),
                 demangle(typeid(TType).name())};

        template<typename TType, unsigned int N>
        const ::std::array<::std::string, 2> BlockTraits<std::SumBlock<TType, N>>::templateTypes =
                {demangle(typeid(TType).name()), "unsigned int"};
    }
}


#endif //LODESTAR_SUMBLOCK_HPP
