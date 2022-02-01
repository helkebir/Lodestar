//
// Created by Hamza El-Kebir on 12/22/21.
//

#ifndef LODESTAR_BLOCKPROTO_HPP
#define LODESTAR_BLOCKPROTO_HPP

#include "SignalBase.hpp"
#include <vector>
#include <tuple>

namespace ls {
    namespace blocks {
        /**
         * Block prototype class.
         */
        class BlockProto {
        public:
            using empty = std::tuple<>; /// Utility using declaration for empty slot bank.

            std::vector<SignalBase *>
            inputPointers{},  /// Vector of input signal pointers.
            outputPointers{}; /// Vector of output signal pointers.

            const unsigned int id; /// Unique Block ID.
            unsigned int
                    ins,  /// Number of input slots.
            outs, /// Number of output slots.
            pars; /// Number of parameter slots.

            /**
             * Virtual trigger function.
             *
             * @details
             * To be overwritten by implementing class to allow for remote triggering of
             * the derived Block.
             */
            virtual void trigger()
            {}

            /**
             * Sets execution priority.
             *
             * @param prio Execution priority.
             */
            void setPriority(int prio)
            {
                prio_ = prio;
            }

            /**
             * Gets execution priority.
             *
             * @return Execution priority.
             */
            int getPriority() const
            {
                return prio_;
            }

            static int objects_created;
            static int objects_alive;

            BlockProto() : id(++objects_created)
            {
                ++objects_alive;
            }

        protected:
            int prio_ = -1;

            virtual ~BlockProto()
            {
                --objects_alive;
            }
        };
    }
}


#endif //LODESTAR_BLOCKPROTO_HPP
