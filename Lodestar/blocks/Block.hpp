//
// Created by Hamza El-Kebir on 12/22/21.
//

#ifndef LODESTAR_BLOCK_HPP
#define LODESTAR_BLOCK_HPP

#include <tuple>
#include <type_traits>
#include <functional>
#include "BlockBase.hpp"
#include "Signal.hpp"
#include "BlockTraits.hpp"
#include "Lodestar/aux/TemplateTools.hpp"
#include "Lodestar/aux/AlwaysFalse.hpp"

#ifdef LS_USE_GINAC

#include <ginac/ginac.h>

#endif

namespace ls {
    /**
     * @brief Main functional block definitions.
     * @ingroup blocks_module
     */
    namespace blocks {
        /**
         * @class Block
         * @ingroup blocks_module
         *
         * @brief Generic base template class for all tuple-based Block instances.
         *
         * For the partial specialization that defines that implementation, see
         * @ref Block_implementation "Block implementation".
         *
         * @tparam TInputsList Inputs list parameter.
         * @tparam TOutputsList Inputs list parameter.
         * @tparam TParametersList Inputs list parameter.
         *
         * @sa @ref Block_implementation "Block implementation"
         */
        template<typename TInputsList, typename TOutputsList, typename TParametersList = BlockProto::empty>
        class Block
                : public BlockBase<Block<TInputsList, TOutputsList, TParametersList>> {
        };

        /**
         * @class Block
         * @ingroup blocks_module
         *
         * @brief Base class for all Block implementations.
         *
         * All @a Block classes in Lodestar derive their core functionality from
         * this class. A @a Block consists of three parameter packs each wrapped
         * in a @c ::std::tuple; any of these parameter packs may be empty.
         *
         * All @c TInputs and @c TOutputs are wrapped in the @c Signal
         * class; @c TParameters are an exception to this, since parameters are
         * intended for internal use only (preferably only at instantiation).
         *
         * @tparam TInputs Template pack of input types.
         * @tparam TOutputs Template pack of output types.
         * @tparam TParameters Template pack of parameter types.
         *
         * @sa @ref Signal
         */
        template<typename... TInputs, typename... TOutputs, typename... TParameters>
        /// @anchor Block_implementation
        class Block<
                ::std::tuple<TInputs...>,
                ::std::tuple<TOutputs...>,
                ::std::tuple<TParameters...>
        >
                : public BlockBase<Block<
                        ::std::tuple<TInputs...>,
                        ::std::tuple<TOutputs...>,
                        ::std::tuple<TParameters...>>
                > {
        public:
            /// Using-declaration of the full @c Block type.
            using type =
            Block<
                    ::std::tuple<TInputs...>,
                    ::std::tuple<TOutputs...>,
                    ::std::tuple<TParameters...>
            >;
            /// Using-declaration of the raw (unwrapped) input types.
            using InputsRaw = ::std::tuple<TInputs...>;
            /// Using-declaration of the Signal-wrapped input types.
            using Inputs = ::std::tuple<typename ls::aux::TemplateTools::wrap<TInputs, Signal>::type...>;
            /// Using-declaration of the raw (unwrapped) output types.
            using OutputsRaw = ::std::tuple<TOutputs...>;
            /// Using-declaration of the Signal-wrapped output types.
            using Outputs = ::std::tuple<typename ls::aux::TemplateTools::wrap<TOutputs, Signal>::type...>;
            /// Using-declaration of the parameter types.
            using Params = ::std::tuple<TParameters...>;

            /// Using-declaration of the trigger equation function type.
            using Equation = ::std::function<void(type &)>;

            enum {
                kIns = sizeof...(TInputs), /// Number of input slots.
                kOuts = sizeof...(TOutputs), /// Number of output slots.
                kPars = sizeof...(TParameters) /// Number of parameter slots.
            };

            /// Globally unique identifier.
//            const unsigned int id;
            using BlockProto::id;

            /**
             * @brief Default constructor.
             *
             * @details The @c id parameter is automatically incremented and
             * assigned.
             */
            Block() : inputs(Inputs{}), outputs(Outputs{}), params(Params{}),
                      equation{}
            {
                BlockProto::ins = kIns;
                BlockProto::outs = kOuts;
                BlockProto::pars = kPars;

                int inputSlotCounter = 0;
                auto primeInputSignal = [&](SignalBase *sb) {
                    sb->blockId = id;
                    sb->slotId = inputSlotCounter++;
                    sb->isInput = true;

                    BlockProto::inputPointers.push_back(sb);
                };

                int outputSlotCounter = 0;
                auto primeOutputSignal = [&](SignalBase *sb) {
                    sb->blockId = id;
                    sb->slotId = outputSlotCounter++;
                    sb->isInput = false;

                    BlockProto::outputPointers.push_back(sb);
                };

                ls::aux::TemplateTools::Executors::forEachPointer(inputs,
                                                                  primeInputSignal);
                ls::aux::TemplateTools::Executors::forEachPointer(outputs,
                                                                  primeOutputSignal);

//#ifdef LS_USE_GINAC
//                serial = GiNaC::function::register_new(
//                        GiNaC::function_options("blkf" + ::std::to_string(id) + "__", blkFunc_NPARAMS)
//                );
//#endif
            }

            //    void connect();

            // INPUTS

            /**
             * Returns a reference to the @c TIdx-th input.
             * @tparam TIdx Input index.
             * @return Reference to the input signal.
             */
            template<size_t TIdx,
                    typename ::std::enable_if<((TIdx >= 0) && (TIdx < kIns))>::type * = nullptr>
            typename ::std::tuple_element<TIdx, Inputs>::type &getInput()
            {
                return ::std::get<TIdx>(inputs);
            }

            /**
             * Out of bounds case for the input getter.
             * @tparam TIdx Input index.
             * @return None.
             */
            template<size_t TIdx,
                    typename ::std::enable_if<!((TIdx >= 0) && (TIdx < kIns))>::type * = nullptr>
            typename ::std::tuple_element<TIdx, Inputs>::type &getInput()
            {
                static_assert(((TIdx >= 0) && (TIdx < kIns)),
                              "Input index out of bounds.");
            }

            /**
             * Returns a const reference to the @c TIdx-th input.
             * @tparam TIdx Input index.
             * @return Const reference to the input signal.
             */
            template<size_t TIdx,
                    typename ::std::enable_if<((TIdx >= 0) && (TIdx < kIns))>::type * = nullptr>
            const typename ::std::tuple_element<TIdx, Inputs>::type &
            getInput() const
            {
                return ::std::get<TIdx>(inputs);
            }

            /**
             * Out of bounds case for the input getter.
             * @tparam TIdx Input index.
             * @return None.
             */
            template<size_t TIdx,
                    typename ::std::enable_if<!((TIdx >= 0) && (TIdx < kIns))>::type * = nullptr>
            const typename ::std::tuple_element<TIdx, Inputs>::type &
            getInput() const
            {
                static_assert(((TIdx >= 0) && (TIdx < kIns)),
                              "Input index out of bounds.");
            }

            /**
             * Returns a reference to the @c TIdx-th input.
             * @tparam TIdx Input index.
             * @return Reference to the input signal.
             *
             * @sa @ref getInput()
             */
            template<size_t TIdx,
                    typename ::std::enable_if<((TIdx >= 0) && (TIdx < kIns))>::type * = nullptr>
            typename ::std::tuple_element<TIdx, Inputs>::type &i()
            {
                return getInput<TIdx>();
            }

            /**
             * Out of bounds case for the input getter.
             * @tparam TIdx Input index.
             * @return None.
             */
            template<size_t TIdx,
                    typename ::std::enable_if<!((TIdx >= 0) && (TIdx < kIns))>::type * = nullptr>
            typename ::std::tuple_element<TIdx, Inputs>::type &i()
            {
                static_assert(((TIdx >= 0) && (TIdx < kIns)),
                              "Input index out of bounds.");
            }

            /**
             * Returns a reference to the @c TIdx-th input.
             * @tparam TIdx Input index.
             * @return Reference to the input signal.
             *
             * @sa @ref getInput() const
             */
            template<size_t TIdx,
                    typename ::std::enable_if<((TIdx >= 0) && (TIdx < kIns))>::type * = nullptr>
            const typename ::std::tuple_element<TIdx, Inputs>::type &i() const
            {
                return getInput<TIdx>();
            }

            /**
             * Out of bounds case for the input getter.
             * @tparam TIdx Input index.
             * @return None.
             */
            template<size_t TIdx,
                    typename ::std::enable_if<!((TIdx >= 0) && (TIdx < kIns))>::type * = nullptr>
            const typename ::std::tuple_element<TIdx, Inputs>::type &i() const
            {
                static_assert(((TIdx >= 0) && (TIdx < kIns)),
                              "Input index out of bounds.");
            }

            // OUTPUTS

            /**
             * Returns a reference to the @c TIdx-th output.
             * @tparam TIdx Output index.
             * @return Reference to the output signal.
             */
            template<size_t TIdx,
                    typename ::std::enable_if<((TIdx >= 0) && (TIdx < kOuts))>::type * = nullptr>
            typename ::std::tuple_element<TIdx, Outputs>::type &getOutput()
            {
                return ::std::get<TIdx>(outputs);
            }

            /**
             * Out of bounds case for the output getter.
             * @tparam TIdx Output index.
             * @return None.
             */
            template<size_t TIdx,
                    typename ::std::enable_if<!((TIdx >= 0) && (TIdx < kOuts))>::type * = nullptr>
            typename ::std::tuple_element<TIdx, Outputs>::type &getOutput()
            {
                static_assert(((TIdx >= 0) && (TIdx < kOuts)),
                              "Output index out of bounds.");
            }

            /**
             * Returns a const reference to the @c TIdx-th output.
             * @tparam TIdx Output index.
             * @return Const reference to the output signal.
             */
            template<size_t TIdx,
                    typename ::std::enable_if<((TIdx >= 0) && (TIdx < kOuts))>::type * = nullptr>
            const typename ::std::tuple_element<TIdx, Outputs>::type &
            getOutput() const
            {
                return ::std::get<TIdx>(outputs);
            }

            /**
             * Out of bounds case for the output getter.
             * @tparam TIdx Output index.
             * @return None.
             */
            template<size_t TIdx,
                    typename ::std::enable_if<!((TIdx >= 0) && (TIdx < kOuts))>::type * = nullptr>
            const typename ::std::tuple_element<TIdx, Outputs>::type &
            getOutput() const
            {
                static_assert(((TIdx >= 0) && (TIdx < kOuts)),
                              "Output index out of bounds.");
            }

            /**
             * Returns a reference to the @c TIdx-th output.
             * @tparam TIdx Output index.
             * @return Reference to the output signal.
             *
             * @sa @ref getOutput()
             */
            template<size_t TIdx,
                    typename ::std::enable_if<((TIdx >= 0) && (TIdx < kOuts))>::type * = nullptr>
            typename ::std::tuple_element<TIdx, Outputs>::type &o()
            {
                return getOutput<TIdx>();
            }

            /**
             * Out of bounds case for the output getter.
             * @tparam TIdx Output index.
             * @return None.
             */
            template<size_t TIdx,
                    typename ::std::enable_if<!((TIdx >= 0) && (TIdx < kOuts))>::type * = nullptr>
            typename ::std::tuple_element<TIdx, Outputs>::type &o()
            {
                static_assert(((TIdx >= 0) && (TIdx < kOuts)),
                              "Output index out of bounds.");
            }

            /**
             * Returns a const reference to the @c TIdx-th output.
             * @tparam TIdx Output index.
             * @return Const reference to the output signal.
             *
             * @sa @ref getOutput() const
             */
            template<size_t TIdx,
                    typename ::std::enable_if<((TIdx >= 0) && (TIdx < kOuts))>::type * = nullptr>
            const typename ::std::tuple_element<TIdx, Outputs>::type &o() const
            {
                return getOutput<TIdx>();
            }

            /**
             * Out of bounds case for the output getter.
             * @tparam TIdx Output index.
             * @return None.
             */
            template<size_t TIdx,
                    typename ::std::enable_if<!((TIdx >= 0) && (TIdx < kOuts))>::type * = nullptr>
            const typename ::std::tuple_element<TIdx, Outputs>::type &o() const
            {
                static_assert(((TIdx >= 0) && (TIdx < kOuts)),
                              "Output index out of bounds.");
            }

            // PARAMETERS

            /**
             * Returns a reference to the @c TIdx-th parameter.
             * @tparam TIdx Parameter index.
             * @return Reference to the parameter.
             */
            template<size_t TIdx,
                    typename ::std::enable_if<((TIdx >= 0) && (TIdx < kPars))>::type * = nullptr>
            typename ::std::tuple_element<TIdx, Params>::type &getParam()
            {
                return ::std::get<TIdx>(params);
            }

            /**
             * Out of bounds case for the parameter getter.
             * @tparam TIdx Parameter index.
             * @return None.
             */
            template<size_t TIdx,
                    typename ::std::enable_if<!((TIdx >= 0) && (TIdx < kPars))>::type * = nullptr>
            typename ::std::tuple_element<TIdx, Params>::type &getParam()
            {
                static_assert(((TIdx >= 0) && (TIdx < kPars)),
                              "Parameter index out of bounds.");
            }

            /**
             * Returns a const reference to the @c TIdx-th parameter.
             * @tparam TIdx Parameter index.
             * @return Const reference to the parameter.
             */
            template<size_t TIdx,
                    typename ::std::enable_if<((TIdx >= 0) && (TIdx < kPars))>::type * = nullptr>
            const typename ::std::tuple_element<TIdx, Params>::type &
            getParam() const
            {
                return ::std::get<TIdx>(params);
            }

            /**
             * Out of bounds case for the parameter getter.
             * @tparam TIdx Parameter index.
             * @return None.
             */
            template<size_t TIdx,
                    typename ::std::enable_if<!((TIdx >= 0) && (TIdx < kPars))>::type * = nullptr>
            const typename ::std::tuple_element<TIdx, Params>::type &
            getParam() const
            {
                static_assert(((TIdx >= 0) && (TIdx < kPars)),
                              "Parameter index out of bounds.");
            }

            /**
             * Returns a reference to the @c TIdx-th parameter.
             * @tparam TIdx Output index.
             * @return Reference to the parameter.
             *
             * @sa @ref getParam()
             */
            template<size_t TIdx,
                    typename ::std::enable_if<((TIdx >= 0) && (TIdx < kPars))>::type * = nullptr>
            typename ::std::tuple_element<TIdx, Params>::type &p()
            {
                return getParam<TIdx>();
            }

            /**
             * Out of bounds case for the parameter getter.
             * @tparam TIdx Parameter index.
             * @return None.
             */
            template<size_t TIdx,
                    typename ::std::enable_if<!((TIdx >= 0) && (TIdx < kPars))>::type * = nullptr>
            typename ::std::tuple_element<TIdx, Params>::type &p()
            {
                static_assert(((TIdx >= 0) && (TIdx < kPars)),
                              "Parameter index out of bounds.");
            }

            /**
             * Returns a const reference to the @c TIdx-th parameter.
             * @tparam TIdx Output index.
             * @return Const reference to the parameter.
             *
             * @sa @ref getParam() const
             */
            template<size_t TIdx,
                    typename ::std::enable_if<((TIdx >= 0) && (TIdx < kPars))>::type * = nullptr>
            const typename ::std::tuple_element<TIdx, Params>::type &p() const
            {
                return getParam<TIdx>();
            }

            /**
             * Out of bounds case for the parameter getter.
             * @tparam TIdx Parameter index.
             * @return None.
             */
            template<size_t TIdx,
                    typename ::std::enable_if<!((TIdx >= 0) && (TIdx < kPars))>::type * = nullptr>
            const typename ::std::tuple_element<TIdx, Params>::type &p() const
            {
                static_assert(((TIdx >= 0) && (TIdx < kPars)),
                              "Parameter index out of bounds.");
            }

            /**
             * Triggers @c equation to process inputs and update output.
             */
            void trigger()
            {
                if (equation)
                    return equation(*this);
            }

#ifdef LS_USE_GINAC

            const ::std::array<GiNaC::ex, kIns> &inputSymbols()
            {
                if (!isInitInput_) {
                    for (int i = 0; i < kIns; i++)
                        inputSymbols_[i] = GiNaC::symbol{"blk" + ::std::to_string(id) + "_i_" + ::std::to_string(i),
                                               "\\text{BLK}^{i, " + ::std::to_string(i) + "}_{" + ::std::to_string(id) +
                                               "}"};

                    isInitInput_ = true;
                }

                return inputSymbols_;
            }

            const ::std::array<GiNaC::ex, kOuts> &outputSymbols()
            {
                if (!isInitOutput_) {
                    for (int i = 0; i < kOuts; i++)
                        outputSymbols_[i] = GiNaC::symbol{"blk" + ::std::to_string(id) + "_o_" + ::std::to_string(i),
                                               "\\text{BLK}^{o, " + ::std::to_string(i) + "}_{" + ::std::to_string(id) +
                                               "}"};

                    isInitOutput_ = true;
                }

                return outputSymbols_;
            }

            const ::std::array<GiNaC::ex, kPars> &parameterSymbols()
            {
                if (!isInitParameter_) {
                    for (int i = 0; i < kPars; i++)
                        parameterSymbols_[i] = GiNaC::symbol{"blk" + ::std::to_string(id) + "_p_" + ::std::to_string(i),
                                               "\\text{BLK}^{o, " + ::std::to_string(i) + "}_{" + ::std::to_string(id) +
                                               "}"};

                    isInitParameter_ = true;
                }

                return parameterSymbols_;
            }

//            GiNaC::function_options & getFunctionOptions()
//            {
//                static ::std::vector<GiNaC::function_options> fops{};
//                fops = GiNaC::function::get_registered_functions();
//
//                return fops[serial];
//            }

            static const unsigned blkFunc_NPARAMS = 1;

            template<typename ...T, typename ::std::enable_if<sizeof...(T) == kIns>::type * = nullptr>
            const GiNaC::function blkf(const T &...p)
            {
                return GiNaC::function(BlockProto::serial, ::std::vector<GiNaC::ex>{GiNaC::ex(p)..., GiNaC::numeric{id}});
            }

            template<typename ...T, typename ::std::enable_if<sizeof...(T) != kIns>::type * = nullptr>
            const GiNaC::function blkf(const T &...p)
            {
                static_assert(sizeof...(T) == blkFunc_NPARAMS,
                              "Incorrect number of arguments provided to symbolic function.");

                return GiNaC::function(BlockProto::serial, ::std::vector<GiNaC::ex>{GiNaC::ex(p)...});
            }
#else

            ::std::array<int, kIns> &inputSymbols()
            {
                static_assert(always_false<::std::array<int, kIns>>::value, "GiNaC use is not enabled. Please compile with LS_USE_GINAC flag.");

                static ::std::array<int, kIns> arr;
                return arr;
            }

            ::std::array<int, kIns> &outputSymbols()
            {
                static_assert(always_false<::std::array<int, kIns>>::value, "GiNaC use is not enabled. Please compile with LS_USE_GINAC flag.");

                static ::std::array<int, kIns> arr;
                return arr;
            }

            ::std::array<int, kIns> &parameterSymbols()
            {
                static_assert(always_false<::std::array<int, kIns>>::value, "GiNaC use is not enabled. Please compile with LS_USE_GINAC flag.");

                static ::std::array<int, kIns> arr;
                return arr;
            }

#endif

            /// Input signals.
            Inputs inputs;
            /// Output signals.
            Outputs outputs;
            /// Parameters.
            Params params;
            /// Trigger function.
            Equation equation;

#ifdef LS_USE_GINAC
        protected:
            bool isInitInput_ = false;
            bool isInitOutput_ = false;
            bool isInitParameter_ = false;

            ::std::array<GiNaC::ex, kIns> inputSymbols_;
            ::std::array<GiNaC::ex, kOuts> outputSymbols_;
            ::std::array<GiNaC::ex, kPars> parameterSymbols_;
#endif
        };

        template<typename... TInputs,
                typename... TOutputs,
                typename... TParameters>
        class BlockTraits<
                Block<
                        ::std::tuple<TInputs...>,
                        ::std::tuple<TOutputs...>,
                        ::std::tuple<TParameters...>
                >> {
        public:
            static constexpr const BlockType blockType = BlockType::GenericBlock;
            static constexpr const bool directFeedthrough = false;

            using type =
            Block<
                    ::std::tuple<TInputs...>,
                    ::std::tuple<TOutputs...>,
                    ::std::tuple<TParameters...>
            >;
            using Base = typename type::Base;

            static const constexpr int kIns = type::Base::kIns;
            static const constexpr int kOuts = type::Base::kOuts;
            static const constexpr int kPars = type::Base::kPars;
        };

#ifdef LS_USE_GINAC
        static ::std::unordered_map<unsigned int, ::std::function<GiNaC::ex(::std::vector<GiNaC::ex>)>>
        symbolicEvalFunctionMap{}, symbolicEvalfFunctionMap{}, symbolicConjugateFunctionMap{}, symbolicRealFunctionMap{},
        symbolicImagFunctionMap{}, symbolicExpandFunctionMap{}, symbolicDerivFunctionMap{}, symbolicExplDerivFunctionMap{},
        symbolicPowerFunctionMap{}, symbolicSeriesFunctionMap{}, symbolicPrintFunctionMap{}, symbolicInfoFunctionMap{};

        static GiNaC::ex symbolicEval(const ::std::vector<GiNaC::ex> &args)
        {
            return symbolicEvalFunctionMap[GiNaC::ex_to<GiNaC::numeric>(args.back()).to_int()](
                    ::std::vector<GiNaC::ex>{args.begin(), args.end() - 1});
        }

        static GiNaC::ex symbolicEvalf(const ::std::vector<GiNaC::ex> &args)
        {
            return symbolicEvalfFunctionMap[GiNaC::ex_to<GiNaC::numeric>(args.back()).to_int()](
                    ::std::vector<GiNaC::ex>{args.begin(), args.end() - 1});
        }

        static GiNaC::ex symbolicConjugate(const ::std::vector<GiNaC::ex> &args)
        {
            return symbolicConjugateFunctionMap[GiNaC::ex_to<GiNaC::numeric>(args.back()).to_int()](
                    ::std::vector<GiNaC::ex>{args.begin(), args.end() - 1});
        }

        static GiNaC::ex symbolicReal(const ::std::vector<GiNaC::ex> &args)
        {
            return symbolicRealFunctionMap[GiNaC::ex_to<GiNaC::numeric>(args.back()).to_int()](
                    ::std::vector<GiNaC::ex>{args.begin(), args.end() - 1});
        }

        static GiNaC::ex symbolicImag(const ::std::vector<GiNaC::ex> &args)
        {
            return symbolicImagFunctionMap[GiNaC::ex_to<GiNaC::numeric>(args.back()).to_int()](
                    ::std::vector<GiNaC::ex>{args.begin(), args.end() - 1});
        }

        static GiNaC::ex symbolicExpand(const ::std::vector<GiNaC::ex> &args)
        {
            return symbolicExpandFunctionMap[GiNaC::ex_to<GiNaC::numeric>(args.back()).to_int()](
                    ::std::vector<GiNaC::ex>{args.begin(), args.end() - 1});
        }

        static GiNaC::ex symbolicDeriv(const ::std::vector<GiNaC::ex> &args)
        {
            return symbolicDerivFunctionMap[GiNaC::ex_to<GiNaC::numeric>(args.back()).to_int()](
                    ::std::vector<GiNaC::ex>{args.begin(), args.end() - 1});
        }

        static GiNaC::ex symbolicExplDeriv(const ::std::vector<GiNaC::ex> &args)
        {
            return symbolicExplDerivFunctionMap[GiNaC::ex_to<GiNaC::numeric>(args.back()).to_int()](
                    ::std::vector<GiNaC::ex>{args.begin(), args.end() - 1});
        }

        static GiNaC::ex symbolicPower(const ::std::vector<GiNaC::ex> &args)
        {
            return symbolicPowerFunctionMap[GiNaC::ex_to<GiNaC::numeric>(args.back()).to_int()](
                    ::std::vector<GiNaC::ex>{args.begin(), args.end() - 1});
        }

        static GiNaC::ex symbolicSeries(const ::std::vector<GiNaC::ex> &args)
        {
            return symbolicSeriesFunctionMap[GiNaC::ex_to<GiNaC::numeric>(args.back()).to_int()](
                    ::std::vector<GiNaC::ex>{args.begin(), args.end() - 1});
        }

        static GiNaC::ex symbolicPrint(const ::std::vector<GiNaC::ex> &args)
        {
            return symbolicPrintFunctionMap[GiNaC::ex_to<GiNaC::numeric>(args.back()).to_int()](
                    ::std::vector<GiNaC::ex>{args.begin(), args.end() - 1});
        }

        static GiNaC::ex symbolicInfo(const ::std::vector<GiNaC::ex> &args)
        {
            return symbolicInfoFunctionMap[GiNaC::ex_to<GiNaC::numeric>(args.back()).to_int()](
                    ::std::vector<GiNaC::ex>{args.begin(), args.end() - 1});
        }
#endif
    }
}


#endif //LODESTAR_BLOCK_HPP
