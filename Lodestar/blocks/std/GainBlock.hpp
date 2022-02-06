//
// Created by Hamza El-Kebir on 12/23/21.
//

#ifndef LODESTAR_GAINBLOCK_HPP
#define LODESTAR_GAINBLOCK_HPP

#include "Lodestar/blocks/Block.hpp"
#include "Lodestar/aux/TemplateTools.hpp"

namespace ls {
    namespace blocks {
        namespace std {
            /**
             * @enum ls::blocks::std::GainBlockOperator
             * @brief Operation types for @c GainBlock.
             *
             */
            enum class GainBlockOperator {
                /// Left multiplication.
                Left,
                /// Right multiplication.
                Right,
                /// Linear convolution.
                Convolution,
                /// Elementwise multiplication.
                ElementWise
            };

            /**
             * @brief Multiplies input by a value (gain).
             * @ingroup blocks_module
             *
             * @details The output type is derived from @c TInput and @c TGain,
             * as well as the type of multiplication through @c TOps.
             *
             * The following operation types are available:
             * - @link GainBlockOperator::Left Left @endlink
             * - @link GainBlockOperator::Right Right @endlink
             * - @link GainBlockOperator::Convolution Convolution @endlink
             * - @link GainBlockOperator::ElementWise Elementwise @endlink
             *
             * This class raises `static_assert`s if the gain and input are
             * not multiplicable.
             *
             * @note This class is derived from
             * @ref Block_implementation "Block implementation".
             *
             * @tparam TInput Input type.
             * @tparam TGain Gain type.
             * @tparam TOps Multiplication type.
             */
            template<typename TInput, typename TGain = TInput, GainBlockOperator TOps = GainBlockOperator::Left>
            class GainBlock :
                    public Block<
                            ::std::tuple<TInput>,
                            ::std::tuple<typename ls::aux::TemplateTraits::BinaryOperators::sanitizeTypeMultiplicable<typename ls::aux::TemplateTraits::BinaryOperators::isMultiplicable<TGain, TInput>::returnType>::returnType>,
                            ::std::tuple<TGain>
                    > {
            public:
                /// Output type trait.
                using OutputTrait = typename ::std::conditional<TOps != GainBlockOperator::Right, ls::aux::TemplateTraits::BinaryOperators::isMultiplicable<TGain, TInput>, ls::aux::TemplateTraits::BinaryOperators::isMultiplicable<TInput, TGain>>::type;
                static_assert(OutputTrait::value, "Gain is not multiplicable with input.");
                /// Sanitized output type trait.
                using SanitizedOutputTrait = typename ls::aux::TemplateTraits::BinaryOperators::sanitizeTypeMultiplicable<typename ls::aux::TemplateTraits::BinaryOperators::isMultiplicable<TGain, TInput>::returnType>;

                /// Output type.
                using OutputType = typename SanitizedOutputTrait::returnType;

                /// Base @c Block class type alias.
                using Base =
                Block<
                        ::std::tuple<TInput>,
                        ::std::tuple<OutputType>,
                        ::std::tuple<TGain>
                >;

                /// Utility type alias for @c GainBlockOperator.
                using Ops = GainBlockOperator;

                /// Utility type alias for left multiplication.
                static constexpr GainBlockOperator Left = Ops::Left;
                /// Utility type alias for right multiplication.
                static constexpr GainBlockOperator Right = Ops::Right;
                /// Utility type alias for convolution.
                static constexpr GainBlockOperator Convolution = Ops::Convolution;
                /// Utility type alias for elementwise multiplication.
                static constexpr GainBlockOperator ElementWise = Ops::ElementWise;

                // TODO: Find way to potentially make operator compile-time
                //  settable.
//                GainBlock(const Ops op = Left)
//                {
//                    setOperator(op);
//                    bindEquation();
//                }
//
//                GainBlock(const TGain &gain, const Ops op = Left)
//                {
//                    setOperator(op);
//                    this->template p<0>() = gain;
//                    bindEquation();
//                }

                /**
                 * Default constructor.
                 */
                GainBlock()
                {
                    bindEquation();
                }

                /**
                 * Constructor with gain parameter setting.
                 *
                 * @param gain Gain to be set.
                 */
                GainBlock(const TGain &gain)
                {
                    this->template p<0>() = gain;
                    bindEquation();
                }

                /**
                 * Sets gain.
                 *
                 * @param gain Gain to be set.
                 */
                void setGain(const TGain &gain)
                {
                    this->template p<0>() = gain;
                }

                /**
                 * Returns const reference to gain.
                 *
                 * @return Const reference to gain.
                 */
                const TGain &getGain() const
                {
                    return this->template p<0>();
                }

//                void setOperator(Ops op)
//                {
//                    this->template p<1>() = op;
//                }
//
//                Ops getOperator()
//                {
//                    return this->template p<1>();
//                }

                /**
                 * Returns reference to gain.
                 *
                 * @return Reference to gain.
                 */
                typename ::std::tuple_element<0, typename Base::Params>::type &
                gain()
                {
                    return this->template p<0>();
                }

                /**
                 * Returns const reference to gain.
                 *
                 * @return Const reference to gain.
                 */
                const typename ::std::tuple_element<0, typename Base::Params>::type &
                gain() const
                {
                    return this->template p<0>();
                }

#ifdef LS_USE_GINAC

                const ::std::array<GiNaC::ex, Base::kIns> &inputSymbols()
                {
                    if (!this->isInitInput_) {
                        for (int i = 0; i < Base::kIns; i++) {
                            if (ls::aux::TemplateTraits::BinaryOperators::parseMatrixLike<TInput>::value) {
                                GiNaC::lst input;
                                for (int ii = 0; ii <
                                                 ls::aux::TemplateTraits::BinaryOperators::parseMatrixLike<TInput>::rows; ii++) {
                                    GiNaC::lst row;
                                    for (int jj = 0; jj <
                                                     ls::aux::TemplateTraits::BinaryOperators::parseMatrixLike<TInput>::cols; jj++) {
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
                            if (ls::aux::TemplateTraits::BinaryOperators::parseMatrixLike<OutputType>::value) {
                                GiNaC::lst output;
                                for (int ii = 0; ii <
                                                 ls::aux::TemplateTraits::BinaryOperators::parseMatrixLike<OutputType>::rows; ii++) {
                                    GiNaC::lst row;
                                    for (int jj = 0; jj <
                                                     ls::aux::TemplateTraits::BinaryOperators::parseMatrixLike<OutputType>::cols; jj++) {
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

                const ::std::array<GiNaC::ex, Base::kPars> &parameterSymbols()
                {
                    if (!this->isInitParameter_) {
                        for (int i = 0; i < Base::kPars; i++) {
                            if (ls::aux::TemplateTraits::BinaryOperators::parseMatrixLike<TGain>::value) {
                                GiNaC::lst par;
                                for (int ii = 0; ii <
                                                 ls::aux::TemplateTraits::BinaryOperators::parseMatrixLike<TGain>::rows; ii++) {
                                    GiNaC::lst row;
                                    for (int jj = 0; jj <
                                                     ls::aux::TemplateTraits::BinaryOperators::parseMatrixLike<TGain>::cols; jj++) {
                                        GiNaC::symbol entry{
                                                "blk" + ::std::to_string(this->id) + "_p_" + ::std::to_string(i) +
                                                "_r_" + ::std::to_string(ii) + "_c_" + ::std::to_string(jj),
                                                "\\text{BLK}^{i, " + ::std::to_string(i) + ", " + ::std::to_string(ii) +
                                                ", " + ::std::to_string(jj) + "}_{" + ::std::to_string(this->id) + "}"};

                                        row.append(entry);
                                    }
                                    par.append(row);
                                }

                                this->parameterSymbols_[i] = GiNaC::lst_to_matrix(par);
                            } else {
                                this->parameterSymbols_[i] = GiNaC::symbol{"blk" + ::std::to_string(this->id) + "_p_" + ::std::to_string(i),
                                                       "\\text{BLK}^{i, " + ::std::to_string(i) + "}_{" +
                                                       ::std::to_string(this->id) +
                                                       "}"};
                            }
                        }

                        this->isInitParameter_ = true;
                    }

                    return this->parameterSymbols_;
                }

#endif

            protected:
                /**
                 * @brief Sets trigger function for non-right multiplication @c
                 * TOps.
                 *
                 * @tparam TTOps Shadows @c TOps.
                 * @return @c void if active.
                 */
                template<GainBlockOperator TTOps = TOps, typename ::std::enable_if<TTOps != Right>::type* = nullptr>
                typename ::std::enable_if<TOps != Right>::type bindEquation()
                {
                    this->equation = [](Base &b) -> void
                    {
                        b.template o<0>().object =
                                b.template p<0>() * b.template i<0>().object;
                        b.template o<0>().propagate();
                    };

#ifdef LS_USE_GINAC
                    GiNaC::function_options fops("blkf" + ::std::to_string(this->id) + "__", this->blkFunc_NPARAMS);

                    ls::blocks::symbolicEvalFunctionMap[this->id] = [&](const ::std::vector<GiNaC::ex> &exvec) -> GiNaC::ex {
                        GiNaC::ex res = 0;
                        int i = 0;

                        for (auto & ex : exvec) {
                            res += this->parameterSymbols()[0] * ex;

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

                /**
                 * @brief Sets trigger function for right multiplication @c TOps.
                 *
                 * @tparam TTOps Shadows @c TOps.
                 * @return @c void if active.
                 */
                template<GainBlockOperator TTOps = TOps, typename ::std::enable_if<TTOps == Right>::type* = nullptr>
                void bindEquation()
                {
                    this->equation = [](Base &b) -> void
                    {
                        b.template o<0>().object =
                                b.template i<0>().object * b.template p<0>();
                        b.template o<0>().propagate();
                    };

#ifdef LS_USE_GINAC
                    GiNaC::function_options fops("blkf" + ::std::to_string(this->id) + "__", this->blkFunc_NPARAMS);

                    ls::blocks::symbolicEvalFunctionMap[this->id] = [&](const ::std::vector<GiNaC::ex> &exvec) -> GiNaC::ex {
                        GiNaC::ex res = 0;
                        int i = 0;

                        for (auto & ex : exvec) {
                            res += ex * this->parameterSymbols()[0];

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

                // TODO: Implement convolution and elementwise multiplication.
            };
        }

        /**
         * @brief BlockTraits specialization for GainBlock.
         *
         * @tparam TInput Input type.
         * @tparam TGain Gain type.
         */
        template<typename TInput, typename TGain, std::GainBlockOperator TOps>
        class BlockTraits<std::GainBlock<TInput, TGain, TOps>> {
        public:
            static constexpr const BlockType blockType = BlockType::GainBlock;
            enum {
                directFeedthrough = true
            };

            using type = std::GainBlock<TInput, TGain, TOps>;
            using Base = typename type::Base;

            enum {
                kIns = Base::kIns,
                kOuts = Base::kOuts,
                kPars = Base::kPars
            };

            static const ::std::array<::std::string, kIns> inTypes;
            static const ::std::array<::std::string, kOuts> outTypes;
            static const ::std::array<::std::string, kPars> parTypes;

            static const ::std::array<::std::string, 3> templateTypes;
        };

        template<typename TInput, typename TGain, std::GainBlockOperator TOps>
        const ::std::array<::std::string, BlockTraits<std::GainBlock<TInput, TGain, TOps>>::kIns> BlockTraits<std::GainBlock<TInput, TGain, TOps>>::inTypes =
                {demangle(typeid(TInput).name())};

        template<typename TInput, typename TGain, std::GainBlockOperator TOps>
        const ::std::array<::std::string, BlockTraits<std::GainBlock<TInput, TGain, TOps>>::kOuts> BlockTraits<std::GainBlock<TInput, TGain, TOps>>::outTypes =
                {demangle(typeid(typename std::GainBlock<TInput, TGain, TOps>::OutputType).name())};

        template<typename TInput, typename TGain, std::GainBlockOperator TOps>
        const ::std::array<::std::string, BlockTraits<std::GainBlock<TInput, TGain, TOps>>::kPars> BlockTraits<std::GainBlock<TInput, TGain, TOps>>::parTypes =
                {demangle(typeid(TGain).name())};

        template<typename TInput, typename TGain, std::GainBlockOperator TOps>
        const ::std::array<::std::string, 3> BlockTraits<std::GainBlock<TInput, TGain, TOps>>::templateTypes =
                {demangle(typeid(TInput).name()), demangle(typeid(TGain).name()), demangle(typeid(TOps).name())};
    }
}


#endif //LODESTAR_GAINBLOCK_HPP
