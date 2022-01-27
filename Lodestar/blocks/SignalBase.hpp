//
// Created by Hamza El-Kebir on 12/22/21.
//

#ifndef LODESTAR_SIGNALBASE_HPP
#define LODESTAR_SIGNALBASE_HPP

#include "Lodestar/GlobalConstants.hpp"
#include <set>

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

            unsigned int id() const
            { return id_; }

            inline
            SignalBase *getConnection(int idx)
            {
                if (idx < 0 || idx >= connectionNumber)
                    return nullptr;

                return *::std::next(connectionPtrs.begin(), idx);
            }

            int slotId; /// Slot index identifier (local counter from 0).

            int blockId; /// Block index (global counter).

            bool isInput; /// True if the signal is an input, false otherwise.

            int connectionNumber = 0; /// Number of connections the SignalBase is currently engaged in.

            ::std::set<SignalBase *> connectionPtrs; // Set containing SignalBase pointers that are connected.
        protected:

            static unsigned int ID;
            unsigned int id_;
        };
    }
}


#endif //LODESTAR_SIGNALBASE_HPP
