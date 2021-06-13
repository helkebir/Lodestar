//
// Created by Hamza El-Kebir on 6/10/21.
//

#ifndef LODESTAR_DEMUX_HPP
#define LODESTAR_DEMUX_HPP

#include "../Block.hpp"
#include "aux/Repeat.hpp"
#include "Eigen/Dense"
#include "aux/CompileTimeQualifiers.hpp"

namespace ls {
    namespace block {
        template<typename TType, unsigned int TTimes, size_t TCallbackNumber = (LS_MAX_CALLBACKS > TTimes ? TTimes : LS_MAX_CALLBACKS), size_t TTicketNumber = LS_MAX_TICKETS>
        using DemuxBlockType = Block<std::tuple<Eigen::Matrix<double, TTimes, 1>*>, typename Repeat<TType, TTimes>::type, TCallbackNumber, TTicketNumber>;

        template<typename TType, unsigned int TTimes, size_t TCallbackNumber = LS_MAX_CALLBACKS, size_t TTicketNumber = LS_MAX_TICKETS>
        class DemuxBlock
                : public Block<std::tuple<Eigen::Matrix<double, TTimes, 1>*>, typename Repeat<TType, TTimes>::type, TCallbackNumber, TTicketNumber> {
        public:
            typedef Block<std::tuple<Eigen::Matrix<double, TTimes, 1>*>, typename Repeat<TType, TTimes>::type, TCallbackNumber, TTicketNumber> Base;
            typedef Eigen::Matrix<double, TTimes, 1> TDVector;
            using Base::inputs_;

            DemuxBlock() : Base()
            {
                std::get<0>(inputs_) = new TDVector;
                getVector().setZero();
                initCallbacks();
            }

            DemuxBlock(TDVector *vec) : Base()
            {
                std::get<0>(inputs_) = vec;
                initCallbacks();
            }

            DemuxBlock(TDVector &vec) : Base()
            {
                std::get<0>(inputs_) = &vec;
                initCallbacks();
            }

            inline bool initCallbacks()
            {
                this->clearInputCallbacks();
                return recursiveInit<TTimes - 1>();
            }

        protected:
            inline TDVector &getVector()
            {
                return *std::get<0>(this->inputs_);
            }

            template<size_t TSlotIdx>
            inline typename std::enable_if<(TSlotIdx > 0), bool>::type recursiveInit()
            {
                std::function<bool(TDVector*)> func = [&](TDVector* val) {
                    this->template setOutput<TSlotIdx>(getVector()(TSlotIdx, 0));

                    return true;
                };

                this->template setInputCallback<0>(func);

                return recursiveInit<TSlotIdx - 1>();
            }

            template<size_t TSlotIdx>
            inline typename std::enable_if<(TSlotIdx == 0), bool>::type recursiveInit()
            {
                std::function<bool(TDVector*)> func = [&](TDVector* val) {
                    this->template setOutput<0>(getVector()(0, 0));

                    return true;
                };

                this->template setInputCallback<0>(func);

                return true;
            }
        };
    }
}

#endif //LODESTAR_DEMUX_HPP
