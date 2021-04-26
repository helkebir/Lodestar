//
// Created by Hamza El-Kebir on 4/17/21.
//

#ifndef LODESTAR_LINEARSYSTEMINVERSE_HPP
#define LODESTAR_LINEARSYSTEMINVERSE_HPP

#include "systems/StateSpace.hpp"

namespace ls { namespace analysis {
    class LinearSystemInverse {
    public:
        /**
         * @brief Generates inverse of a linear time invariant system.
         *
         * @param lti Linear time invariant system.
         *
         * @return Inverted linear time invariant system.
         */
        static systems::StateSpace
        inverse(systems::StateSpace &lti);
    };
} }


#endif //LODESTAR_LINEARSYSTEMINVERSE_HPP
