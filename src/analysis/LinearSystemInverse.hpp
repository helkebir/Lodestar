//
// Created by Hamza El-Kebir on 4/17/21.
//

#ifndef LODESTAR_LINEARSYSTEMINVERSE_HPP
#define LODESTAR_LINEARSYSTEMINVERSE_HPP

#include "systems/StateSpace.hpp"

namespace ls {
    namespace analysis {
        /**
         * @brief Routines for computing the  inverse of a continuous-time state
         * space systems.
         *
         * Corresponds to SLICOT Routine <a href="http://slicot.org/objects/software/shared/doc/AB07ND.html">AB07ND</a>
         * (<em>Inverse of a given state-space representation</em>).
         */
        class LinearSystemInverse {
        public:
            /**
             * @brief Generates the inverse of a state space system.
             *
             * @param ss State space system.
             *
             * @return Inverted state space system.
             */
            static systems::StateSpace inverse(systems::StateSpace &ss);
        };
    }
}


#endif //LODESTAR_LINEARSYSTEMINVERSE_HPP
