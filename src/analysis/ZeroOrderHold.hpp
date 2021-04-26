//
// Created by Hamza El-Kebir on 4/17/21.
//

#ifndef LODESTAR_ZEROORDERHOLD_HPP
#define LODESTAR_ZEROORDERHOLD_HPP

#include "Eigen/Dense"
#include "systems/StateSpace.hpp"

namespace ls { namespace analysis {
    class ZeroOrderHold {
    public:
        /**
         * @brief Generates zero-order hold discretization from continuous time
         * LTI system.
         *
         * @param lti Linear time invariant system.
         * @param dt Sampling period.
         *
         * @return Zero-order hold discrete time system.
         */
        static systems::StateSpace
        c2d(const systems::StateSpace &lti, double dt);

        /**
         * @brief Generates zero-order hold discretization from continuous time
         * LTI system.
         *
         * @param lti Linear time invariant system.
         * @param dt Sampling period.
         *
         * @return Zero-order hold discrete time system.
         */
        static systems::StateSpace
        d2c(const systems::StateSpace &lti, double dt);
    };
} }

#endif //LODESTAR_ZEROORDERHOLD_HPP
