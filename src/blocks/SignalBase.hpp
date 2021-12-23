//
// Created by Hamza El-Kebir on 12/22/21.
//

#ifndef LODESTAR_SIGNALBASE_HPP
#define LODESTAR_SIGNALBASE_HPP

#include "GlobalConstants.hpp"
#include <array>

namespace ls {
    namespace blocks {
        /**
         * Signal base class.
         */
        class SignalBase {
        public:
            SignalBase() : id_(0)
            {}

            SignalBase(unsigned int id) : id_(id)
            {}

            /**
             * Increments global Signal ID counter.
             * @return Incremented Signal ID.
             */
            static unsigned int next()
            {
                return ID++;
            }

            int blockId;

            int connectionNumber = 0;
            std::array<SignalBase *, LS_MAX_CONNECTIONS> connectionPointers;
        protected:

            static unsigned int ID;
            unsigned int id_;
        };
    }
}


#endif //LODESTAR_SIGNALBASE_HPP
