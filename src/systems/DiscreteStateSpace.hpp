//
// Created by Hamza El-Kebir on 4/21/21.
//

#ifndef LODESTAR_DISCRETESTATESPACE_HPP
#define LODESTAR_DISCRETESTATESPACE_HPP

#include "StateSpace.hpp"
#include "analysis/ZeroOrderHold.hpp"
#include "analysis/BilinearTransformation.hpp"

namespace ls {
    namespace systems {
        class DiscreteStateSpace : public StateSpace {
        public:
            /**
             * @brief Default constructor.
             *
             * Sets sampling time to 1.
             */
            DiscreteStateSpace() : StateSpace()
            {
                setDiscreteParams(1);
            }

            /**
             * @brief Constructs empty discrete state space system with given
             * sampling period.
             *
             * @param dt Sampling period.
             */
            DiscreteStateSpace(double dt) : StateSpace()
            {
                setDiscreteParams(dt);
            }

            /**
             * @brief Constructs a discrete state space system with the given
             * matrices.
             *
             * The sampling period is set to 1.
             *
             * @param A State matrix.
             * @param B Input matrix.
             * @param C Output matrix.
             * @param D Feedforward matrix.
             */
            DiscreteStateSpace(const Eigen::MatrixXd &A,
                               const Eigen::MatrixXd &B,
                               const Eigen::MatrixXd &C,
                               const Eigen::MatrixXd &D)
                    : StateSpace(A, B, C, D)
            {
                setDiscreteParams(1);
            }

            /**
             * @brief Constructs a discrete state space system with the given
             * matrices.
             *
             * @param A State matrix.
             * @param B Input matrix.
             * @param C Output matrix.
             * @param D Feedforward matrix.
             * @param dt Sampling period.
             */
            DiscreteStateSpace(const Eigen::MatrixXd &A,
                               const Eigen::MatrixXd &B,
                               const Eigen::MatrixXd &C,
                               const Eigen::MatrixXd &D,
                               double dt)
                    : StateSpace(A, B, C, D)
            {
                setDiscreteParams(dt);
            }

            /**
             * @brief Copy constructor.
             *
             * @param other Discrete state space object to copy.
             */
            DiscreteStateSpace(const DiscreteStateSpace &other) :
                    StateSpace(other)
            {
                setDiscreteParams(other._dt, other._isDiscrete);
            }

            /**
             * @brief Resamples the system.
             *
             * This method uses zero-order hold.
             *
             * @param dt New sampling period.
             */
            void resample(double dt);

            /**
             * @brief Resamples the system.
             *
             * This method uses a backward difference transformation.
             *
             * @param dt New sampling period.
             */
            void resampleFast(double dt);

            bool isStable(double tolerance = 0) const override;
        };
    }
}

#endif //LODESTAR_DISCRETESTATESPACE_HPP
