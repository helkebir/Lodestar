//
// Created by Hamza El-Kebir on 4/17/21.
//

#ifndef LODESTAR_BILINEARTRANSFORMATION_HPP
#define LODESTAR_BILINEARTRANSFORMATION_HPP

#include "Eigen/Dense"
#include "systems/StateSpace.hpp"

namespace ls {
    namespace analysis {
        /**
         * @brief Routines for converting a state space system from continuous-
         * to discrete-time and vice versa.
         *
         * Corresponds to SLICOT Routine <a href="http://slicot.org/objects/software/shared/doc/AB04MD.html">AB04MD</a>
         * (<em>Discrete-time <-> continuous-time conversion by bilinear transformation</em>).
         */
        class BilinearTransformation {
        public:
            /**
             * @brief Generates generalized bilinear transform of a
             * continuous-time state space system.
             *
             * @param A State matrix.
             * @param B Input matrix.
             * @param C Output matrix.
             * @param D Feedforward matrix.
             * @param dt Sampling period.
             * @param alpha Generalized bilinear transformation parameter; default
             * parameter corresponds to backward differencing transform.
             *
             * @return Transformed discrete-time state space system.
             */
            static systems::StateSpace
            c2d(const Eigen::MatrixXd &A, const Eigen::MatrixXd &B,
                const Eigen::MatrixXd &C, const Eigen::MatrixXd &D,
                double dt,
                double alpha = 1);

            /**
             * @brief Generates generalized bilinear transform of a
             * continuous-time state space system.
             *
             * @param ss State space system.
             * @param dt Sampling period.
             * @param alpha Generalized bilinear transformation parameter; default
             * parameter corresponds to backward differencing transform.
             *
             * @return Transformed discrete-time state space system.
             */
            static systems::StateSpace
            c2d(const systems::StateSpace &ss, double dt,
                double alpha = 1);

            /**
             * @brief Generates generalized bilinear transform of a
             * discrete-time state space system.
             *
             * @param ss State space system.
             * @param dt Sampling period.
             * @param alpha Generalized bilinear transformation parameter; default
             * parameter corresponds to backward differencing transform.
             *
             * @return Transformed continuous-time state space system.
             */
            static systems::StateSpace
            d2c(const systems::StateSpace &ss, double dt,
                double alpha = 1);

            /**
             * @brief Generates generalized bilinear transform of a
             * discrete-time state space system.
             *
             * This method retrieves the sampling period from the state space
             * object.
             *
             * @param ss State space system.
             * @param alpha Generalized bilinear transformation parameter; default
             * parameter corresponds to backward differencing transform.
             *
             * @return Transformed continuous-time state space system.
             */
            static systems::StateSpace
            d2c(const systems::StateSpace &ss, double alpha = 1);

            /**
             * @brief Generates generalized bilinear transform of a
             * discrete-time state space system.
             *
             * @param A State matrix.
             * @param B Input matrix.
             * @param C Output matrix.
             * @param D Feedforward matrix.
             * @param dt Sampling period.
             * @param alpha Generalized bilinear transformation parameter; default
             * parameter corresponds to backward differencing transform.
             *
             * @return Transformed continuous-time state space system.
             */
            static systems::StateSpace
            d2c(const Eigen::MatrixXd &A, const Eigen::MatrixXd &B,
                const Eigen::MatrixXd &C, const Eigen::MatrixXd &D, double dt,
                double alpha = 1);

            /**
             * @brief Generates Tustin transform of a continuous-time state
             * space system.
             *
             * @param ss State space system.
             * @param dt Sampling period.
             *
             * @return Transformed discrete-time state space system.
             */
            static systems::StateSpace
            c2dTustin(const systems::StateSpace &ss, double dt);

            /**
             * @brief Generates Tustin transform of a discrete-time state space
             * system.
             *
             * @param ss State space system.
             * @param dt Sampling period.
             *
             * @return Transformed continuous-time state space system.
             */
            static systems::StateSpace
            d2cTustin(const systems::StateSpace &ss, double dt);

            /**
             * @brief Generates Euler transform of a continuous-time state space
             * system.
             *
             * @param ss State space system.
             * @param dt Sampling period.
             *
             * @return Transformed discrete-time state space system.
             */
            static systems::StateSpace
            c2dEuler(const systems::StateSpace &ss, double dt);

            /**
             * @brief Generates Euler transform of a discrete-time state space
             * system.
             *
             * @param ss State space system.
             * @param dt Sampling period.
             *
             * @return Transformed continuous-time state space system.
             */
            static systems::StateSpace
            d2cEuler(const systems::StateSpace &ss, double dt);

            /**
             * @brief Generates backward differencing transform of a
             * continuous-time state space system.
             *
             * @param ss State space system.
             * @param dt Sampling period.
             *
             * @return Transformed discrete-time state space system.
             */
            static systems::StateSpace
            c2dBwdDiff(const systems::StateSpace &ss, double dt);

            /**
             * @brief Generates backward differencing transform of a
             * discrete-time state space system.
             *
             * @param ss State space system.
             * @param dt Sampling period.
             *
             * @return Transformed continuous-time state space system.
             */
            static systems::StateSpace
            d2cBwdDiff(const systems::StateSpace &ss, double dt);
        };
    }
}


#endif //LODESTAR_BILINEARTRANSFORMATION_HPP
