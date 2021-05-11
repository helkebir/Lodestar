//
// Created by Hamza El-Kebir on 4/17/21.
//

#ifndef LODESTAR_ZEROORDERHOLD_HPP
#define LODESTAR_ZEROORDERHOLD_HPP

#include "Eigen/Dense"
#include "systems/StateSpace.hpp"

namespace ls {
    namespace analysis {
        /**
         * @brief Routines for computing zero-order hold transformation on state
         * space systems.
         */
        class ZeroOrderHold {
        public:
            /**
             * @brief Generates zero-order hold discretization from a
             * continuous-time state space system.
             *
             * @param A State matrix.
             * @param B Input matrix.
             * @param C Output matrix.
             * @param D Feedforward matrix.
             * @param dt Sampling period.
             *
             * @return Zero-order hold discrete-time state space system.
             */
            static systems::StateSpace
            c2d(const Eigen::MatrixXd &A, const Eigen::MatrixXd &B,
                const Eigen::MatrixXd &C, const Eigen::MatrixXd &D, double dt);

            /**
             * @brief Generates zero-order hold discretization from a
             * continuous-time state space system.
             *
             * @param ss State space system.
             * @param dt Sampling period.
             *
             * @return Zero-order hold discrete-time state space system.
             */
            static systems::StateSpace
            c2d(const systems::StateSpace &ss, double dt);

            /**
             * @brief Reverts a zero-order hold discretization on a
             * discrete-time state space system.
             *
             * @param A State matrix.
             * @param B Input matrix.
             * @param C Output matrix.
             * @param D Feedforward matrix.
             * @param dt Sampling period.
             *
             * @return Zero-order hold continuous-time state space system.
             */
            static systems::StateSpace
            d2c(const Eigen::MatrixXd &A, const Eigen::MatrixXd &B,
                const Eigen::MatrixXd &C, const Eigen::MatrixXd &D, double dt);

            /**
             * @brief Reverts a zero-order hold discretization on a
             * discrete-time state space system.
             *
             * @param ss State space system.
             * @param dt Sampling period.
             *
             * @return Continuous-time state space system.
             */
            static systems::StateSpace
            d2c(const systems::StateSpace &ss, double dt);
        };
    }
}

#endif //LODESTAR_ZEROORDERHOLD_HPP
