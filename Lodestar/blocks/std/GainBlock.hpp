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
             * @enum ls::blocks::std::GainBlockConvolutionMode
             * @brief Convolution modes for @c GainBlock
             */
            enum class GainBlockConvolutionMode {
                /// Reflect about the edge of the last pixel. Also known as half-sample symmetric.
                Reflect,
                /// Fill all values beyond edges with a constant value.
                Constant,
                /// Extend by replicating last pixel.
                Nearest,
                /// Extend by reflecting about the center of the last pixel. Also known as whole-sample symmetric.
                Mirror,
                /// Wrap around to the opposing edge.
                Wrap
            };

#define OUTPUT_GAINBLOCK() \
    typename ::std::conditional< \
    TOps == GainBlockOperator::Convolution, \
    TInput,                \
    typename ls::aux::TemplateTraits::BinaryOperators::sanitizeTypeMultiplicable<typename ::std::conditional< \
        TOps != GainBlockOperator::Right,                                                                     \
        ls::aux::TemplateTraits::BinaryOperators::isMultiplicable<TGain, TInput>,                             \
        ls::aux::TemplateTraits::BinaryOperators::isMultiplicable<TInput, TGain>                              \
        >::type::returnType>::returnType>::type

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
             * The following convolution modes are available:
             * - @link GainBlockConvolutionMode::Reflect Reflect @endlink
             * - @link GainBlockConvolutionMode::Constant Constant @endlink
             * - @link GainBlockConvolutionMode::Nearest Nearest @endlink
             * - @link GainBlockConvolutionMode::Mirror Mirror @endlink
             * - @link GainBlockConvolutionMode::Wrap Wrap @endlink
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
             * @tparam TConv Convolution mode.
             */
            template<typename TInput, typename TGain = TInput, GainBlockOperator TOps = GainBlockOperator::Left, GainBlockConvolutionMode TConv = GainBlockConvolutionMode::Reflect>
            class GainBlock :
                    public Block<
                            ::std::tuple<TInput>,
                            ::std::tuple<OUTPUT_GAINBLOCK()>,
                            ::std::tuple<TGain, double>
                    > {
            public:
                /// Output type trait.
                using OutputTrait = typename ::std::conditional<
                        TOps != GainBlockOperator::Right,
                        ls::aux::TemplateTraits::BinaryOperators::isMultiplicable<TGain, TInput>,
                        ls::aux::TemplateTraits::BinaryOperators::isMultiplicable<TInput, TGain>
                >::type;
                static_assert(OutputTrait::value || (TOps == GainBlockOperator::Convolution),
                              "Gain is not multiplicable with input.");
                /// Sanitized output type trait.
                using SanitizedOutputTrait = typename ls::aux::TemplateTraits::BinaryOperators::sanitizeTypeMultiplicable<typename OutputTrait::returnType>;

                /// Output type.
                using OutputType = OUTPUT_GAINBLOCK();

                /// Gain type trait.
                using GainTrait = ls::aux::TemplateTraits::BinaryOperators::parseMatrixLike<TGain>;
                /// Input type trait.
                using InputTrait = ls::aux::TemplateTraits::BinaryOperators::parseMatrixLike<TInput>;
                static_assert((TOps != GainBlockOperator::Convolution) || (GainTrait::value && InputTrait ::value),
                              "For convolution, TInput and TGain must be matrix-like.");

                /// Base @c Block class type alias.
                using Base =
                Block<
                        ::std::tuple<TInput>,
                        ::std::tuple<OutputType>,
                        ::std::tuple<TGain, double>
                >;

                /// Utility type alias for @c GainBlockOperator.
                using Ops = GainBlockOperator;

                /// Utility type alias for @c GainBlockOperator.
                using Conv = GainBlockConvolutionMode;

                /// Utility alias for left multiplication.
                static constexpr Ops Left = Ops::Left;
                /// Utility alias for right multiplication.
                static constexpr Ops Right = Ops::Right;
                /// Utility alias for convolution.
                static constexpr Ops Convolution = Ops::Convolution;
                /// Utility alias for elementwise multiplication.
                static constexpr Ops ElementWise = Ops::ElementWise;

                /// Utility alias for reflect convolution mode.
                static constexpr Conv Reflect = Conv::Reflect;
                /// Utility alias for constant convolution mode.
                static constexpr Conv Constant = Conv::Constant;
                /// Utility alias for nearest convolution mode.
                static constexpr Conv Nearest = Conv::Nearest;
                /// Utility alias for mirror convolution mode.
                static constexpr Conv Mirror = Conv::Mirror;
                /// Utility alias for wrap convolution mode.
                static constexpr Conv Wrap = Conv::Wrap;

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

                // TODO: Make constantVal type user-settable.

                /**
                 * Returns reference to constant value (used when GainBlockConvolutionMode is Constant).
                 *
                 * @return Reference to constant value.
                 */
                typename ::std::tuple_element<1, typename Base::Params>::type &
                constantVal()
                {
                    return this->template p<1>();
                }

                /**
                 * Returns const reference to constant value (used when GainBlockConvolutionMode is Constant).
                 *
                 * @return Const reference to constant value.
                 */
                const typename ::std::tuple_element<1, typename Base::Params>::type &
                constantVal() const
                {
                    return this->template p<1>();
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
                                this->inputSymbols_[i] = GiNaC::symbol{
                                        "blk" + ::std::to_string(this->id) + "_i_" + ::std::to_string(i),
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
                                this->outputSymbols_[i] = GiNaC::symbol{
                                        "blk" + ::std::to_string(this->id) + "_o_" + ::std::to_string(i),
                                        "\\text{BLK}^{o, " + ::std::to_string(i) + "}_{" +
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
                        int i = 0;
                        {
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
                                this->parameterSymbols_[i] = GiNaC::symbol{
                                        "blk" + ::std::to_string(this->id) + "_p_" + ::std::to_string(i),
                                        "\\text{BLK}^{p, " + ::std::to_string(i) + "}_{" +
                                        ::std::to_string(this->id) +
                                        "}"};
                            }
                        }

                        // constant value symbol
                        i++;
                        this->parameterSymbols_[i] = GiNaC::symbol{
                                "blk" + ::std::to_string(this->id) + "_p_" + ::std::to_string(i),
                                "\\text{BLK}^{p, " + ::std::to_string(i) + "}_{" +
                                ::std::to_string(this->id) +
                                "}"};

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
                template<GainBlockOperator TTOps = TOps, typename ::std::enable_if<TTOps == Left>::type * = nullptr>
                void bindEquation()
                {
                    this->equation = [](Base &b) -> void {
                        b.template o<0>().object =
                                b.template p<0>() * b.template i<0>().object;
                        b.template o<0>().propagate();
                    };

#ifdef LS_USE_GINAC
                    GiNaC::function_options fops("blkf" + ::std::to_string(this->id) + "__", this->blkFunc_NPARAMS);

                    ls::blocks::symbolicEvalFunctionMap[this->id] = [&](
                            const ::std::vector<GiNaC::ex> &exvec) -> GiNaC::ex {
                        GiNaC::ex res = 0;
                        int i = 0;

                        for (auto &ex: exvec) {
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
                template<GainBlockOperator TTOps = TOps, typename ::std::enable_if<TTOps == Right>::type * = nullptr>
                void bindEquation()
                {
                    this->equation = [](Base &b) -> void {
                        b.template o<0>().object =
                                b.template i<0>().object * b.template p<0>();
                        b.template o<0>().propagate();
                    };

#ifdef LS_USE_GINAC
                    GiNaC::function_options fops("blkf" + ::std::to_string(this->id) + "__", this->blkFunc_NPARAMS);

                    ls::blocks::symbolicEvalFunctionMap[this->id] = [&](
                            const ::std::vector<GiNaC::ex> &exvec) -> GiNaC::ex {
                        GiNaC::ex res = 0;
                        int i = 0;

                        for (auto &ex: exvec) {
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

                template<GainBlockOperator TTOps = TOps, GainBlockConvolutionMode TTConv = TConv,
                        typename ::std::enable_if<((TTOps == Convolution) && (TTConv == Reflect))>::type * = nullptr>
                static void convolve(Base &b)
                {
                    static const auto NRowsKernel = GainTrait::rows;
                    static const auto NColsKernel = GainTrait::cols;
                    static const auto NRowsInput = InputTrait::rows;
                    static const auto NColsInput = InputTrait::cols;

                    auto getInput = [&](int i, int j) {
                        if (i < 0)
                            i = (-i - 1) % NRowsInput;
                        if (i >= NRowsInput)
                            i = (2*NRowsInput - i - 1) % NRowsInput;

                        if (j < 0)
                            j = (-j - 1) % NColsInput;
                        if (j >= NColsInput)
                            j = (2*NColsInput - j - 1) % NColsInput;

                        return b.template i<0>().object(i, j);
                    };

                    b.template o<0>().object.setZero();

                    for (int i=0; i < NRowsInput; i++) {
                        for (int j=0; j < NColsInput; j++) {
                            for (int ii=0; ii < NRowsKernel; ii++) {
                                for (int jj=0; jj < NColsKernel; jj++) {
                                    b.template o<0>().object(i, j) -= b.template p<0>()(ii, jj) * getInput(i - (NRowsKernel-1)/2 + ii, j - (NColsKernel-1)/2 + jj);
                                }
                            }
                        }
                    }

                    b.template o<0>().propagate();
                }

                template<GainBlockOperator TTOps = TOps, GainBlockConvolutionMode TTConv = TConv,
                        typename ::std::enable_if<((TTOps == Convolution) && (TTConv == Constant))>::type * = nullptr>
                static void convolve(Base &b)
                {
                    static const auto NRowsKernel = GainTrait::rows;
                    static const auto NColsKernel = GainTrait::cols;
                    static const auto NRowsInput = InputTrait::rows;
                    static const auto NColsInput = InputTrait::cols;

                    auto getInput = [&](int i, int j) {
                        if (i < 0)
                            return b.template p<1>();
                        if (i >= NRowsInput)
                            return b.template p<1>();

                        if (j < 0)
                            return b.template p<1>();
                        if (j >= NColsInput)
                            return b.template p<1>();

                        return b.template i<0>().object(i, j);
                    };

                    b.template o<0>().object.setZero();

                    for (int i=0; i < NRowsInput; i++) {
                        for (int j=0; j < NColsInput; j++) {
                            for (int ii=0; ii < NRowsKernel; ii++) {
                                for (int jj=0; jj < NColsKernel; jj++) {
                                    b.template o<0>().object(i, j) -= b.template p<0>()(ii, jj) * getInput(i - (NRowsKernel-1)/2 + ii, j - (NColsKernel-1)/2 + jj);
                                }
                            }
                        }
                    }

                    b.template o<0>().propagate();
                }

                template<GainBlockOperator TTOps = TOps, GainBlockConvolutionMode TTConv = TConv,
                        typename ::std::enable_if<((TTOps == Convolution) && (TTConv == Nearest))>::type * = nullptr>
                static void convolve(Base &b)
                {
                    static const auto NRowsKernel = GainTrait::rows;
                    static const auto NColsKernel = GainTrait::cols;
                    static const auto NRowsInput = InputTrait::rows;
                    static const auto NColsInput = InputTrait::cols;

                    auto getInput = [&](int i, int j) {
                        if (i < 0)
                            i = 0;
                        if (i >= NRowsInput)
                            i = NRowsInput - 1;

                        if (j < 0)
                            j = 0;
                        if (j >= NColsInput)
                            j = NColsInput-1;

                        return b.template i<0>().object(i, j);
                    };

                    b.template o<0>().object.setZero();

                    for (int i=0; i < NRowsInput; i++) {
                        for (int j=0; j < NColsInput; j++) {
                            for (int ii=0; ii < NRowsKernel; ii++) {
                                for (int jj=0; jj < NColsKernel; jj++) {
                                    b.template o<0>().object(i, j) -= b.template p<0>()(ii, jj) * getInput(i - (NRowsKernel-1)/2 + ii, j - (NColsKernel-1)/2 + jj);
                                }
                            }
                        }
                    }

                    b.template o<0>().propagate();
                }

                template<GainBlockOperator TTOps = TOps, GainBlockConvolutionMode TTConv = TConv,
                        typename ::std::enable_if<((TTOps == Convolution) && (TTConv == Mirror))>::type * = nullptr>
                static void convolve(Base &b)
                {
                    static const auto NRowsKernel = GainTrait::rows;
                    static const auto NColsKernel = GainTrait::cols;
                    static const auto NRowsInput = InputTrait::rows;
                    static const auto NColsInput = InputTrait::cols;

                    auto getInput = [&](int i, int j) {
                        if (i < 0)
                            i = (-i) % NRowsInput;
                        if (i >= NRowsInput)
                            i = (2*NRowsInput - i - 2) % NRowsInput;

                        if (j < 0)
                            j = (-j) % NColsInput;
                        if (j >= NColsInput)
                            j = (2*NColsInput - j - 2) % NColsInput;

                        return b.template i<0>().object(i, j);
                    };

                    b.template o<0>().object.setZero();

                    for (int i=0; i < NRowsInput; i++) {
                        for (int j=0; j < NColsInput; j++) {
                            for (int ii=0; ii < NRowsKernel; ii++) {
                                for (int jj=0; jj < NColsKernel; jj++) {
                                    b.template o<0>().object(i, j) -= b.template p<0>()(ii, jj) * getInput(i - (NRowsKernel-1)/2 + ii, j - (NColsKernel-1)/2 + jj);
                                }
                            }
                        }
                    }

                    b.template o<0>().propagate();
                }

                template<GainBlockOperator TTOps = TOps, GainBlockConvolutionMode TTConv = TConv,
                        typename ::std::enable_if<((TTOps == Convolution) && (TTConv == Wrap))>::type * = nullptr>
                static void convolve(Base &b)
                {
                    static const auto NRowsKernel = GainTrait::rows;
                    static const auto NColsKernel = GainTrait::cols;
                    static const auto NRowsInput = InputTrait::rows;
                    static const auto NColsInput = InputTrait::cols;

                    auto getInput = [&](int i, int j) {
                        if (i < 0)
                            i = (NRowsInput + i) % NRowsInput;
                        if (i >= NRowsInput)
                            i = i % NRowsInput;

                        if (j < 0)
                            j = (NColsInput + j) % NColsInput;
                        if (j >= NColsInput)
                            j = j % NColsInput;

                        return b.template i<0>().object(i, j);
                    };

                    b.template o<0>().object.setZero();

                    for (int i=0; i < NRowsInput; i++) {
                        for (int j=0; j < NColsInput; j++) {
                            for (int ii=0; ii < NRowsKernel; ii++) {
                                for (int jj=0; jj < NColsKernel; jj++) {
                                    b.template o<0>().object(i, j) -= b.template p<0>()(ii, jj) * getInput(i - (NRowsKernel-1)/2 + ii, j - (NColsKernel-1)/2 + jj);
                                }
                            }
                        }
                    }

                    b.template o<0>().propagate();
                }

                /**
                 * @brief Sets trigger function for convolution @c TOps.
                 *
                 * @tparam TTOps Shadows @c TOps.
                 * @return @c void if active.
                 */
                template<GainBlockOperator TTOps = TOps, typename ::std::enable_if<
                        TTOps == Convolution>::type * = nullptr>
                void bindEquation()
                {
                    this->equation = [](Base &b) -> void {
                        convolve(b);
                    };

//#ifdef LS_USE_GINAC
//                    GiNaC::function_options fops("blkf" + ::std::to_string(this->id) + "__", this->blkFunc_NPARAMS);
//
//                    ls::blocks::symbolicEvalFunctionMap[this->id] = [&](
//                            const ::std::vector<GiNaC::ex> &exvec) -> GiNaC::ex {
//                        GiNaC::ex res = 0;
//                        int i = 0;
//
//                        for (auto &ex: exvec) {
//                            res += ex * this->parameterSymbols()[0];
//
//                            i++;
//                        }
//
//                        return res;
//                    };
//
//                    fops.eval_func(ls::blocks::symbolicEval);
//
//
//                    this->serial = GiNaC::function::register_new(
//                            fops
//                    );
//#endif
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
        template<typename TInput, typename TGain, std::GainBlockOperator TOps, std::GainBlockConvolutionMode TConv>
        class BlockTraits<std::GainBlock<TInput, TGain, TOps, TConv>> {
        public:
            static constexpr const BlockType blockType = BlockType::GainBlock;
            enum {
                directFeedthrough = true
            };

            using type = std::GainBlock<TInput, TGain, TOps, TConv>;
            using Base = typename type::Base;

            enum {
                kIns = Base::kIns,
                kOuts = Base::kOuts,
                kPars = Base::kPars
            };

            static const ::std::array<::std::string, kIns> inTypes;
            static const ::std::array<::std::string, kOuts> outTypes;
            static const ::std::array<::std::string, kPars> parTypes;

            static const ::std::array<::std::string, 4> templateTypes;
        };

        template<typename TInput, typename TGain, std::GainBlockOperator TOps, std::GainBlockConvolutionMode TConv>
        const ::std::array<::std::string, BlockTraits<std::GainBlock<TInput, TGain, TOps, TConv>>::kIns> BlockTraits<std::GainBlock<TInput, TGain, TOps, TConv>>::inTypes =
                {demangle(typeid(TInput).name())};

        template<typename TInput, typename TGain, std::GainBlockOperator TOps, std::GainBlockConvolutionMode TConv>
        const ::std::array<::std::string, BlockTraits<std::GainBlock<TInput, TGain, TOps, TConv>>::kOuts> BlockTraits<std::GainBlock<TInput, TGain, TOps, TConv>>::outTypes =
                {demangle(typeid(typename std::GainBlock<TInput, TGain, TOps>::OutputType).name())};

        template<typename TInput, typename TGain, std::GainBlockOperator TOps, std::GainBlockConvolutionMode TConv>
        const ::std::array<::std::string, BlockTraits<std::GainBlock<TInput, TGain, TOps, TConv>>::kPars> BlockTraits<std::GainBlock<TInput, TGain, TOps, TConv>>::parTypes =
                {demangle(typeid(TGain).name()), "double"};

        template<typename TInput, typename TGain, std::GainBlockOperator TOps, std::GainBlockConvolutionMode TConv>
        const ::std::array<::std::string, 4> BlockTraits<std::GainBlock<TInput, TGain, TOps, TConv>>::templateTypes =
                {demangle(typeid(TInput).name()), demangle(typeid(TGain).name()), demangle(typeid(TOps).name()),
                 demangle(typeid(TConv).name())};
    }
}

#undef OUTPUT_GAINBLOCK

#endif //LODESTAR_GAINBLOCK_HPP
