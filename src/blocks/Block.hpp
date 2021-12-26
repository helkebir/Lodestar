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
#include "aux/TemplateTools.hpp"

/**
 * @defgroup blocks_module Blocks module
 *
 * This module provides the main functional block diagram features in Lodestar,
 * including a standard library of blocks, execution order computations,
 * simplifying operations, algebraic loop resolution, and more.
 */

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
         * For the partial specialization that defined that implementation, see
         * @ref Block_implementation "Block implementation".
         *
         * @tparam TInputsList Inputs list parameter.
         * @tparam TOutputsList Inputs list parameter.
         * @tparam TParametersList Inputs list parameter.
         *
         * @sa @ref Block_implementation "Block implementation"
         */
        template <typename TInputsList, typename TOutputsList, typename TParametersList = BlockProto::empty>
        class Block : public BlockBase<Block<TInputsList, TOutputsList, TParametersList>> {};

        /**
         * @class Block
         * @ingroup blocks_module
         *
         * @brief Base class for all Block implementations.
         *
         * All @a Block classes in Lodestar derive their core functionality from
         * this class. A @a Block consists of three parameter packs each wrapped
         * in a @c std::tuple; any of these parameter packs may be empty.
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
        template <typename... TInputs, typename... TOutputs, typename... TParameters>
        class Block<std::tuple<TInputs...>, std::tuple<TOutputs...>, std::tuple<TParameters...>> : public BlockBase<Block<std::tuple<TInputs...>, std::tuple<TOutputs...>, std::tuple<TParameters...>>> {
        public:
            /// @anchor Block_implementation
            //    using Inputs = std::tuple<TInputs...>;
            //    using Outputs = std::tuple<TOutputs...>;
            /// Using-declaration of the full @c Block type.
            using type = Block<std::tuple<TInputs...>, std::tuple<TOutputs...>, std::tuple<TParameters...>>;
            /// Using-declaration of the raw (unwrapped) input types.
            using InputsRaw = std::tuple<TInputs...>;
            /// Using-declaration of the Signal-wrapped input types.
            using Inputs = std::tuple<typename ls::aux::TemplateTools::wrap<TInputs, Signal>::type...>;
            /// Using-declaration of the raw (unwrapped) output types.
            using OutputsRaw = std::tuple<TOutputs...>;
            /// Using-declaration of the Signal-wrapped output types.
            using Outputs = std::tuple<typename ls::aux::TemplateTools::wrap<TOutputs, Signal>::type...>;
            /// Using-declaration of the parameter types.
            using Params = std::tuple<TParameters...>;

            /// Using-declaration of the trigger equation function type.
            using Equation = std::function<void (type&)>;

            /// Number of input slots.
            static const int kIns;
            /// Number of output slots.
            static const int kOuts;
            /// Number of parameter slots.
            static const int kPars;

            /// Globally unique identifier.
            const unsigned int id;

            //    constexpr static const int n = sizeof...(TInputs);
            //    constexpr static const int m = sizeof...(TOutputs);
            //    constexpr static const int p = sizeof...(TParameters);

            /**
             * @brief Default constructor.
             *
             * @details The @c id parameter is automatically incremented and
             * assigned.
             */
            Block() : inputs(Inputs{}), outputs(Outputs{}), params(Params{}), equation{}, id(BlockProto::id)
            {
                BlockProto::ins = kIns;
                BlockProto::outs = kOuts;
                BlockProto::pars = kPars;

                auto primeInputSignal = [&](SignalBase * sb) {
                    sb->blockId = id;
                    BlockProto::inputPointers.push_back(sb);
                };

                auto primeOutputSignal = [&](SignalBase * sb) {
                    sb->blockId = id;
                    BlockProto::outputPointers.push_back(sb);
                };

                ls::aux::TemplateTools::Executors::forEachPointer(inputs, primeInputSignal);
                ls::aux::TemplateTools::Executors::forEachPointer(outputs, primeOutputSignal);
            }

            //    void connect();

            // INPUTS

            /**
             * Returns a reference to the @c TIdx-th input.
             * @tparam TIdx Input index.
             * @return Reference to the input signal.
             */
            template <size_t TIdx, typename std::enable_if<((TIdx >= 0) && (TIdx < kIns)), void*>::type* = nullptr>
            typename std::tuple_element<TIdx, Inputs>::type& getInput()
            {
                return std::get<TIdx>(inputs);
            }

            /**
             * Out of bounds case for the input getter.
             * @tparam TIdx Input index.
             * @return None.
             */
            template <size_t TIdx, typename std::enable_if<!((TIdx >= 0) && (TIdx < kIns)), void*>::type* = nullptr>
            typename std::tuple_element<TIdx, Inputs>::type& getInput()
            {
                static_assert(((TIdx >= 0) && (TIdx < kIns)), "Input index out of bounds.");
            }

            /**
             * Returns a const reference to the @c TIdx-th input.
             * @tparam TIdx Input index.
             * @return Const reference to the input signal.
             */
            template <size_t TIdx, typename std::enable_if<((TIdx >= 0) && (TIdx < kIns)), void*>::type* = nullptr>
            const typename std::tuple_element<TIdx, Inputs>::type& getInput() const
            {
                return std::get<TIdx>(inputs);
            }

            /**
             * Out of bounds case for the input getter.
             * @tparam TIdx Input index.
             * @return None.
             */
            template <size_t TIdx, typename std::enable_if<!((TIdx >= 0) && (TIdx < kIns)), void*>::type* = nullptr>
            const typename std::tuple_element<TIdx, Inputs>::type& getInput() const
            {
                static_assert(((TIdx >= 0) && (TIdx < kIns)), "Input index out of bounds.");
            }

            /**
             * Returns a reference to the @c TIdx-th input.
             * @tparam TIdx Input index.
             * @return Reference to the input signal.
             *
             * @sa @ref getInput()
             */
            template <size_t TIdx, typename std::enable_if<((TIdx >= 0) && (TIdx < kIns)), void*>::type* = nullptr>
            typename std::tuple_element<TIdx, Inputs>::type& i()
            {
                return getInput<TIdx>();
            }

            /**
             * Out of bounds case for the input getter.
             * @tparam TIdx Input index.
             * @return None.
             */
            template <size_t TIdx, typename std::enable_if<!((TIdx >= 0) && (TIdx < kIns)), void*>::type* = nullptr>
            typename std::tuple_element<TIdx, Inputs>::type& i()
            {
                static_assert(((TIdx >= 0) && (TIdx < kIns)), "Input index out of bounds.");
            }

            /**
             * Returns a reference to the @c TIdx-th input.
             * @tparam TIdx Input index.
             * @return Reference to the input signal.
             *
             * @sa @ref getInput() const
             */
            template <size_t TIdx, typename std::enable_if<((TIdx >= 0) && (TIdx < kIns)), void*>::type* = nullptr>
            const typename std::tuple_element<TIdx, Inputs>::type& i() const
            {
                return getInput<TIdx>();
            }

            /**
             * Out of bounds case for the input getter.
             * @tparam TIdx Input index.
             * @return None.
             */
            template <size_t TIdx, typename std::enable_if<!((TIdx >= 0) && (TIdx < kIns)), void*>::type* = nullptr>
            const typename std::tuple_element<TIdx, Inputs>::type& i() const
            {
                static_assert(((TIdx >= 0) && (TIdx < kIns)), "Input index out of bounds.");
            }

            // OUTPUTS

            /**
             * Returns a reference to the @c TIdx-th output.
             * @tparam TIdx Output index.
             * @return Reference to the output signal.
             */
            template <size_t TIdx, typename std::enable_if<((TIdx >= 0) && (TIdx < kOuts)), void*>::type* = nullptr>
            typename std::tuple_element<TIdx, Outputs>::type& getOutput()
            {
                return std::get<TIdx>(outputs);
            }

            /**
             * Out of bounds case for the output getter.
             * @tparam TIdx Output index.
             * @return None.
             */
            template <size_t TIdx, typename std::enable_if<!((TIdx >= 0) && (TIdx < kOuts)), void*>::type* = nullptr>
            typename std::tuple_element<TIdx, Outputs>::type& getOutput()
            {
                static_assert(((TIdx >= 0) && (TIdx < kOuts)), "Output index out of bounds.");
            }

            /**
             * Returns a const reference to the @c TIdx-th output.
             * @tparam TIdx Output index.
             * @return Const reference to the output signal.
             */
            template <size_t TIdx, typename std::enable_if<((TIdx >= 0) && (TIdx < kOuts)), void*>::type* = nullptr>
            const typename std::tuple_element<TIdx, Outputs>::type& getOutput() const
            {
                return std::get<TIdx>(outputs);
            }

            /**
             * Out of bounds case for the output getter.
             * @tparam TIdx Output index.
             * @return None.
             */
            template <size_t TIdx, typename std::enable_if<!((TIdx >= 0) && (TIdx < kOuts)), void*>::type* = nullptr>
            const typename std::tuple_element<TIdx, Outputs>::type& getOutput() const
            {
                static_assert(((TIdx >= 0) && (TIdx < kOuts)), "Output index out of bounds.");
            }

            /**
             * Returns a reference to the @c TIdx-th output.
             * @tparam TIdx Output index.
             * @return Reference to the output signal.
             *
             * @sa @ref getOutput()
             */
            template <size_t TIdx, typename std::enable_if<((TIdx >= 0) && (TIdx < kOuts)), void*>::type* = nullptr>
            typename std::tuple_element<TIdx, Outputs>::type& o()
            {
                return getOutput<TIdx>();
            }

            /**
             * Out of bounds case for the output getter.
             * @tparam TIdx Output index.
             * @return None.
             */
            template <size_t TIdx, typename std::enable_if<!((TIdx >= 0) && (TIdx < kOuts)), void*>::type* = nullptr>
            typename std::tuple_element<TIdx, Outputs>::type& o()
            {
                static_assert(((TIdx >= 0) && (TIdx < kOuts)), "Output index out of bounds.");
            }

            /**
             * Returns a const reference to the @c TIdx-th output.
             * @tparam TIdx Output index.
             * @return Const reference to the output signal.
             *
             * @sa @ref getOutput() const
             */
            template <size_t TIdx, typename std::enable_if<((TIdx >= 0) && (TIdx < kOuts)), void*>::type* = nullptr>
            const typename std::tuple_element<TIdx, Outputs>::type& o() const
            {
                return getOutput<TIdx>();
            }

            /**
             * Out of bounds case for the output getter.
             * @tparam TIdx Output index.
             * @return None.
             */
            template <size_t TIdx, typename std::enable_if<!((TIdx >= 0) && (TIdx < kOuts)), void*>::type* = nullptr>
            const typename std::tuple_element<TIdx, Outputs>::type& o() const
            {
                static_assert(((TIdx >= 0) && (TIdx < kOuts)), "Output index out of bounds.");
            }

            // PARAMETERS

            /**
             * Returns a reference to the @c TIdx-th parameter.
             * @tparam TIdx Parameter index.
             * @return Reference to the parameter.
             */
            template <size_t TIdx, typename std::enable_if<((TIdx >= 0) && (TIdx < kPars)), void*>::type* = nullptr>
            typename std::tuple_element<TIdx, Params>::type& getParam()
            {
                return std::get<TIdx>(params);
            }

            /**
             * Out of bounds case for the parameter getter.
             * @tparam TIdx Parameter index.
             * @return None.
             */
            template <size_t TIdx, typename std::enable_if<!((TIdx >= 0) && (TIdx < kPars)), void*>::type* = nullptr>
            typename std::tuple_element<TIdx, Params>::type& getParam()
            {
                static_assert(((TIdx >= 0) && (TIdx < kPars)), "Parameter index out of bounds.");
            }

            /**
             * Returns a const reference to the @c TIdx-th parameter.
             * @tparam TIdx Parameter index.
             * @return Const reference to the parameter.
             */
            template <size_t TIdx, typename std::enable_if<((TIdx >= 0) && (TIdx < kPars)), void*>::type* = nullptr>
            const typename std::tuple_element<TIdx, Params>::type& getParam() const
            {
                return std::get<TIdx>(params);
            }

            /**
             * Out of bounds case for the parameter getter.
             * @tparam TIdx Parameter index.
             * @return None.
             */
            template <size_t TIdx, typename std::enable_if<!((TIdx >= 0) && (TIdx < kPars)), void*>::type* = nullptr>
            const typename std::tuple_element<TIdx, Params>::type& getParam() const
            {
                static_assert(((TIdx >= 0) && (TIdx < kPars)), "Parameter index out of bounds.");
            }

            /**
             * Returns a reference to the @c TIdx-th parameter.
             * @tparam TIdx Output index.
             * @return Reference to the parameter.
             *
             * @sa @ref getParam()
             */
            template <size_t TIdx, typename std::enable_if<((TIdx >= 0) && (TIdx < kPars)), void*>::type* = nullptr>
            typename std::tuple_element<TIdx, Params>::type& p()
            {
                return getParam<TIdx>();
            }

            /**
             * Out of bounds case for the parameter getter.
             * @tparam TIdx Parameter index.
             * @return None.
             */
            template <size_t TIdx, typename std::enable_if<!((TIdx >= 0) && (TIdx < kPars)), void*>::type* = nullptr>
            typename std::tuple_element<TIdx, Params>::type& p()
            {
                static_assert(((TIdx >= 0) && (TIdx < kPars)), "Parameter index out of bounds.");
            }

            /**
             * Returns a const reference to the @c TIdx-th parameter.
             * @tparam TIdx Output index.
             * @return Const reference to the parameter.
             *
             * @sa @ref getParam() const
             */
            template <size_t TIdx, typename std::enable_if<((TIdx >= 0) && (TIdx < kPars)), void*>::type* = nullptr>
            const typename std::tuple_element<TIdx, Params>::type& p() const
            {
                return getParam<TIdx>();
            }

            /**
             * Out of bounds case for the parameter getter.
             * @tparam TIdx Parameter index.
             * @return None.
             */
            template <size_t TIdx, typename std::enable_if<!((TIdx >= 0) && (TIdx < kPars)), void*>::type* = nullptr>
            const typename std::tuple_element<TIdx, Params>::type& p() const
            {
                static_assert(((TIdx >= 0) && (TIdx < kPars)), "Parameter index out of bounds.");
            }

            /**
             * Triggers @c equation to process inputs and update output.
             */
            void trigger()
            {
                if (equation)
                    return equation(*this);
            }

            /// Input signals.
            Inputs inputs;
            /// Output signals.
            Outputs outputs;
            /// Parameters.
            Params params;
            /// Trigger function.
            Equation equation;
        };

        template <typename... TInputs, typename... TOutputs, typename... TParameters>
        constexpr const int Block<std::tuple<TInputs...>, std::tuple<TOutputs...>, std::tuple<TParameters...>>::kIns = sizeof...(TInputs);

        template <typename... TInputs, typename... TOutputs, typename... TParameters>
        constexpr const int Block<std::tuple<TInputs...>, std::tuple<TOutputs...>, std::tuple<TParameters...>>::kOuts = sizeof...(TOutputs);

        template <typename... TInputs, typename... TOutputs, typename... TParameters>
        constexpr const int Block<std::tuple<TInputs...>, std::tuple<TOutputs...>, std::tuple<TParameters...>>::kPars = sizeof...(TParameters);

        template<typename... TInputs, typename... TOutputs, typename... TParameters>
        class BlockTraits<Block<std::tuple<TInputs...>, std::tuple<TOutputs...>, std::tuple<TParameters...>>> {
        public:
            static constexpr const BlockType blockType = BlockType::GenericBlock;
            static constexpr const bool directFeedthrough = false;

            using type =
            Block<
                std::tuple<TInputs...>,
                std::tuple<TOutputs...>,
                std::tuple<TParameters...>
            >;
            using Base = typename type::Base;

            static const constexpr int kIns = type::Base::kIns;
            static const constexpr int kOuts = type::Base::kOuts;
            static const constexpr int kPars = type::Base::kPars;
        };
    }
}


#endif //LODESTAR_BLOCK_HPP
