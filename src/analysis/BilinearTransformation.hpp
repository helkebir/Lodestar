//
// Created by Hamza El-Kebir on 4/17/21.
//

#ifndef LODESTAR_BILINEARTRANSFORMATION_HPP
#define LODESTAR_BILINEARTRANSFORMATION_HPP

#include "Eigen/Dense"
#include "systems/StateSpace.hpp"

namespace ls { namespace analysis {
    class BilinearTransformation {
    public:
        /**
         * @brief Generates generalized bilinear transform from continuous-time
         * LTI system.
         *
         * @param lti Linear time invariant system.
         * @param dt Sampling period.
         * @param alpha Generalized bilinear transformation parameter; default
         * parameter corresponds to backward differencing transform.
         *
         * @return Transformed discrete-time LTI system.
         */
        static systems::StateSpace
        c2d(const systems::StateSpace &lti, double dt,
            double alpha = 1);

        /**
         * @brief Generates generalized bilinear transform from discrete-time
         * LTI system.
         *
         * @param lti Linear time invariant system.
         * @param dt Sampling period.
         * @param alpha Generalized bilinear transformation parameter; default
         * parameter corresponds to backward differencing transform.
         *
         * @return Transformed continuous-time LTI system.
         */
        static systems::StateSpace
        d2c(const systems::StateSpace &lti, double dt,
            double alpha = 1);

        /**
         * @brief Generates Tustin transform from continuous-time
         * LTI system.
         *
         * @param lti Linear time invariant system.
         * @param dt Sampling period.
         *
         * @return Transformed discrete-time LTI system.
         */
        static systems::StateSpace
        c2dTustin(const systems::StateSpace &lti, double dt);

        /**
         * @brief Generates Tustin transform from discrete-time
         * LTI system.
         *
         * @param lti Linear time invariant system.
         * @param dt Sampling period.
         *
         * @return Transformed continuous-time LTI system.
         */
        static systems::StateSpace
        d2cTustin(const systems::StateSpace &lti, double dt);

        /**
         * @brief Generates Euler transform from continuous-time
         * LTI system.
         *
         * @param lti Linear time invariant system.
         * @param dt Sampling period.
         *
         * @return Transformed discrete-time LTI system.
         */
        static systems::StateSpace
        c2dEuler(const systems::StateSpace &lti, double dt);

        /**
         * @brief Generates Euler transform from discrete-time
         * LTI system.
         *
         * @param lti Linear time invariant system.
         * @param dt Sampling period.
         *
         * @return Transformed continuous-time LTI system.
         */
        static systems::StateSpace
        d2cEuler(const systems::StateSpace &lti, double dt);

        /**
         * @brief Generates backward differencing transform from continuous-time
         * LTI system.
         *
         * @param lti Linear time invariant system.
         * @param dt Sampling period.
         *
         * @return Transformed discrete-time LTI system.
         */
        static systems::StateSpace
        c2dBwdDiff(const systems::StateSpace &lti, double dt);

        /**
         * @brief Generates backward differencing transform from discrete-time
         * LTI system.
         *
         * @param lti Linear time invariant system.
         * @param dt Sampling period.
         *
         * @return Transformed continuous-time LTI system.
         */
        static systems::StateSpace
        d2cBwdDiff(const systems::StateSpace &lti, double dt);
    };
} }


#endif //LODESTAR_BILINEARTRANSFORMATION_HPP
