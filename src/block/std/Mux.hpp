//
// Created by Hamza El-Kebir on 6/10/21.
//

#ifndef LODESTAR_MUX_HPP
#define LODESTAR_MUX_HPP

#include "../Block.hpp"
#include "aux/Repeat.hpp"
#include <Eigen/Dense>

namespace ls {
    namespace block {
        template<typename TType, unsigned int TTimes, size_t TCallbackNumber = LS_MAX_CALLBACKS, size_t TTicketNumber = LS_MAX_TICKETS>
        using MuxBlockType = Block<typename Repeat<TType, TTimes>::type, std::tuple<Eigen::Matrix<double, TTimes, 1>*>, TCallbackNumber, TTicketNumber>;

        template<typename TType, unsigned int TTimes, size_t TCallbackNumber = LS_MAX_CALLBACKS, size_t TTicketNumber = LS_MAX_TICKETS>
        class MuxBlock
                : public Block<typename Repeat<TType, TTimes>::type, std::tuple<Eigen::Matrix<double, TTimes, 1>*>, TCallbackNumber, TTicketNumber> {
        public:
            typedef Block<typename Repeat<TType, TTimes>::type, std::tuple<Eigen::Matrix<double, TTimes, 1>*>, TCallbackNumber, TTicketNumber> Base;
            typedef Eigen::Matrix<double, TTimes, 1> TDVector;
            using Base::outputs_;

            MuxBlock() : Base()
            {
                std::get<0>(outputs_) = new TDVector;
                getVector().setZero();
                initCallbacks();
            }

            MuxBlock(TDVector *vec) : Base()
            {
                std::get<0>(outputs_) = vec;
                initCallbacks();
            }

            MuxBlock(TDVector &vec) : Base()
            {
                std::get<0>(outputs_) = &vec;
                initCallbacks();
            }

            template<unsigned int TSlotIdx = 0, typename TArg>
            inline typename std::enable_if<(std::is_convertible<TArg, TType>::value), bool>::type set(TArg var)
            {
                this->template setInput<TSlotIdx>(var);
                return true;
            }

            template<unsigned int TSlotIdx = 0, typename TArg>
            inline typename std::enable_if<(!std::is_convertible<TArg, TType>::value), bool>::type set(TArg var)
            {
                static_assert(std::is_convertible<TArg, TType>::value, "Mux input must be convertible.");

                return false;
            }

            template<unsigned int TSlotIdx = 0, typename TArg, typename... TArgs>
            inline typename std::enable_if<
                    (std::is_convertible<TArg, TType>::value) && (sizeof...(TArgs) < TTimes), bool>::type
            set(TArg var, TArgs... vars)
            {
                this->template setInput<TSlotIdx>(var);
                return set<TSlotIdx + 1>(vars...);
            }

            template<unsigned int TSlotIdx = 0, typename TArg, typename... TArgs>
            inline typename std::enable_if<
                    (!std::is_convertible<TArg, TType>::value) && (sizeof...(TArgs) < TTimes), bool>::type
            set(TArg var, TArgs... vars)
            {
                static_assert(std::is_convertible<TArg, TType>::value, "Mux input must be convertible.");

                return false;
            }

            template<unsigned int TSlotIdx = 0, typename TArg, typename... TArgs>
            inline typename std::enable_if<
                    (std::is_convertible<TArg, TType>::value) && (sizeof...(TArgs) >= TTimes), bool>::type
            set(TArg var, TArgs... vars)
            {
                static_assert(sizeof...(TArgs) < TTimes,
                              "Number of input arguments to Mux cannot be greater than number of slots.");

                return false;
            }

            inline bool initCallbacks()
            {
                this->clearInputCallbacks();
                return recursiveInit<TTimes - 1>();
            }

        protected:
            inline TDVector &getVector()
            {
                return *std::get<0>(this->outputs_);
            }

            template<size_t TSlotIdx>
            inline typename std::enable_if<(TSlotIdx > 0), bool>::type recursiveInit()
            {
                std::function<bool(TType)> func = [&](TType val) {
                    std::get<0>(this->outputs_)->operator()(TSlotIdx, 0) = val;

                    return true;
                };

                this->template setInputCallback<TSlotIdx>(func);

                return recursiveInit<TSlotIdx - 1>();
            }

            template<size_t TSlotIdx>
            inline typename std::enable_if<(TSlotIdx == 0), bool>::type recursiveInit()
            {
                std::function<bool(TType)> func = [&](TType val) {
                    std::get<0>(this->outputs_)->operator()(0, 0) = val;

                    return true;
                };

                this->template setInputCallback<0>(func);

                return true;
            }
        };
    }
}

#endif //LODESTAR_MUX_HPP
