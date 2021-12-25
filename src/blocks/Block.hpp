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

namespace ls {
    namespace blocks {
        template <typename TInputsList, typename TOutputsList, typename TParametersList = BlockProto::empty>
        class Block : public BlockBase<Block<TInputsList, TOutputsList, TParametersList>> {};

        template <typename... TInputs, typename... TOutputs, typename... TParameters>
        class Block<std::tuple<TInputs...>, std::tuple<TOutputs...>, std::tuple<TParameters...>> : public BlockBase<Block<std::tuple<TInputs...>, std::tuple<TOutputs...>, std::tuple<TParameters...>>> {
        public:
            //    using Inputs = std::tuple<TInputs...>;
            //    using Outputs = std::tuple<TOutputs...>;
            using type = Block<std::tuple<TInputs...>, std::tuple<TOutputs...>, std::tuple<TParameters...>>;
            using InputsRaw = std::tuple<TInputs...>;
            using Inputs = std::tuple<typename ls::aux::TemplateTools::wrap<TInputs, Signal>::type...>;
            using OutputsRaw = std::tuple<TOutputs...>;
            using Outputs = std::tuple<typename ls::aux::TemplateTools::wrap<TOutputs, Signal>::type...>;
            using Params = std::tuple<TParameters...>;

            using Equation = std::function<void (type&)>;

            static const int kIns;
            static const int kOuts;
            static const int kPars;

            const unsigned int id;

            //    constexpr static const int n = sizeof...(TInputs);
            //    constexpr static const int m = sizeof...(TOutputs);
            //    constexpr static const int p = sizeof...(TParameters);

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

            template <size_t TIdx, typename std::enable_if<((TIdx >= 0) && (TIdx < kIns)), void*>::type* = nullptr>
            typename std::tuple_element<TIdx, Inputs>::type& getInput()
            {
                return std::get<TIdx>(inputs);
            }

            template <size_t TIdx, typename std::enable_if<!((TIdx >= 0) && (TIdx < kIns)), void*>::type* = nullptr>
            typename std::tuple_element<TIdx, Inputs>::type& getInput()
            {
                static_assert(((TIdx >= 0) && (TIdx < kIns)), "Input index out of bounds.");
            }

            template <size_t TIdx, typename std::enable_if<((TIdx >= 0) && (TIdx < kIns)), void*>::type* = nullptr>
            const typename std::tuple_element<TIdx, Inputs>::type& getInput() const
            {
                return std::get<TIdx>(inputs);
            }

            template <size_t TIdx, typename std::enable_if<!((TIdx >= 0) && (TIdx < kIns)), void*>::type* = nullptr>
            const typename std::tuple_element<TIdx, Inputs>::type& getInput() const
            {
                static_assert(((TIdx >= 0) && (TIdx < kIns)), "Input index out of bounds.");
            }

            template <size_t TIdx, typename std::enable_if<((TIdx >= 0) && (TIdx < kIns)), void*>::type* = nullptr>
            typename std::tuple_element<TIdx, Inputs>::type& i()
            {
                return getInput<TIdx>();
            }

            template <size_t TIdx, typename std::enable_if<!((TIdx >= 0) && (TIdx < kIns)), void*>::type* = nullptr>
            typename std::tuple_element<TIdx, Inputs>::type& i()
            {
                static_assert(((TIdx >= 0) && (TIdx < kIns)), "Input index out of bounds.");
            }

            template <size_t TIdx, typename std::enable_if<((TIdx >= 0) && (TIdx < kIns)), void*>::type* = nullptr>
            const typename std::tuple_element<TIdx, Inputs>::type& i() const
            {
                return getInput<TIdx>();
            }

            template <size_t TIdx, typename std::enable_if<!((TIdx >= 0) && (TIdx < kIns)), void*>::type* = nullptr>
            const typename std::tuple_element<TIdx, Inputs>::type& i() const
            {
                static_assert(((TIdx >= 0) && (TIdx < kIns)), "Input index out of bounds.");
            }

            // OUTPUTS

            template <size_t TIdx, typename std::enable_if<((TIdx >= 0) && (TIdx < kOuts)), void*>::type* = nullptr>
            typename std::tuple_element<TIdx, Outputs>::type& getOutput()
            {
                return std::get<TIdx>(outputs);
            }

            template <size_t TIdx, typename std::enable_if<!((TIdx >= 0) && (TIdx < kOuts)), void*>::type* = nullptr>
            typename std::tuple_element<TIdx, Outputs>::type& getOutput()
            {
                static_assert(((TIdx >= 0) && (TIdx < kOuts)), "Output index out of bounds.");
            }

            template <size_t TIdx, typename std::enable_if<((TIdx >= 0) && (TIdx < kOuts)), void*>::type* = nullptr>
            const typename std::tuple_element<TIdx, Outputs>::type& getOutput() const
            {
                return std::get<TIdx>(outputs);
            }

            template <size_t TIdx, typename std::enable_if<!((TIdx >= 0) && (TIdx < kOuts)), void*>::type* = nullptr>
            const typename std::tuple_element<TIdx, Outputs>::type& getOutput() const
            {
                static_assert(((TIdx >= 0) && (TIdx < kOuts)), "Output index out of bounds.");
            }

            template <size_t TIdx, typename std::enable_if<((TIdx >= 0) && (TIdx < kOuts)), void*>::type* = nullptr>
            typename std::tuple_element<TIdx, Outputs>::type& o()
            {
                return getOutput<TIdx>();
            }

            template <size_t TIdx, typename std::enable_if<!((TIdx >= 0) && (TIdx < kOuts)), void*>::type* = nullptr>
            typename std::tuple_element<TIdx, Outputs>::type& o()
            {
                static_assert(((TIdx >= 0) && (TIdx < kOuts)), "Output index out of bounds.");
            }

            template <size_t TIdx, typename std::enable_if<((TIdx >= 0) && (TIdx < kOuts)), void*>::type* = nullptr>
            const typename std::tuple_element<TIdx, Outputs>::type& o() const
            {
                return getOutput<TIdx>();
            }

            template <size_t TIdx, typename std::enable_if<!((TIdx >= 0) && (TIdx < kOuts)), void*>::type* = nullptr>
            const typename std::tuple_element<TIdx, Outputs>::type& o() const
            {
                static_assert(((TIdx >= 0) && (TIdx < kOuts)), "Output index out of bounds.");
            }

            // PARAMETERS

            template <size_t TIdx, typename std::enable_if<((TIdx >= 0) && (TIdx < kPars)), void*>::type* = nullptr>
            typename std::tuple_element<TIdx, Params>::type& getParam()
            {
                return std::get<TIdx>(params);
            }

            template <size_t TIdx, typename std::enable_if<!((TIdx >= 0) && (TIdx < kPars)), void*>::type* = nullptr>
            typename std::tuple_element<TIdx, Params>::type& getParam()
            {
                static_assert(((TIdx >= 0) && (TIdx < kPars)), "Parameter index out of bounds.");
            }

            template <size_t TIdx, typename std::enable_if<((TIdx >= 0) && (TIdx < kPars)), void*>::type* = nullptr>
            const typename std::tuple_element<TIdx, Params>::type& getParam() const
            {
                return std::get<TIdx>(params);
            }

            template <size_t TIdx, typename std::enable_if<!((TIdx >= 0) && (TIdx < kPars)), void*>::type* = nullptr>
            const typename std::tuple_element<TIdx, Params>::type& getParam() const
            {
                static_assert(((TIdx >= 0) && (TIdx < kPars)), "Parameter index out of bounds.");
            }

            template <size_t TIdx, typename std::enable_if<((TIdx >= 0) && (TIdx < kPars)), void*>::type* = nullptr>
            typename std::tuple_element<TIdx, Params>::type& p()
            {
                return getParam<TIdx>();
            }

            template <size_t TIdx, typename std::enable_if<!((TIdx >= 0) && (TIdx < kPars)), void*>::type* = nullptr>
            typename std::tuple_element<TIdx, Params>::type& p()
            {
                static_assert(((TIdx >= 0) && (TIdx < kPars)), "Parameter index out of bounds.");
            }

            template <size_t TIdx, typename std::enable_if<((TIdx >= 0) && (TIdx < kPars)), void*>::type* = nullptr>
            const typename std::tuple_element<TIdx, Params>::type& p() const
            {
                return getParam<TIdx>();
            }

            template <size_t TIdx, typename std::enable_if<!((TIdx >= 0) && (TIdx < kPars)), void*>::type* = nullptr>
            const typename std::tuple_element<TIdx, Params>::type& p() const
            {
                static_assert(((TIdx >= 0) && (TIdx < kPars)), "Parameter index out of bounds.");
            }

            void trigger()
            {
                if (equation)
                    return equation(*this);
            }

            Inputs inputs;
            Outputs outputs;
            Params params;
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
