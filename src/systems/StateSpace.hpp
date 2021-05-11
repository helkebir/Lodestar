//
// Created by Hamza El-Kebir on 4/17/21.
//

#ifndef LODESTAR_STATESPACE_HPP
#define LODESTAR_STATESPACE_HPP

#include "SystemStateless.hpp"
#include "Eigen/Dense"

namespace ls {
    namespace systems {
        class StateSpace : public SystemStateless {
        public:
            /**
             * @brief Default constructor.
             */
            StateSpace() : _A(Eigen::MatrixXd::Zero(1, 1)),
                           _B(Eigen::MatrixXd::Zero(1, 1)),
                           _C(Eigen::MatrixXd::Zero(1, 1)),
                           _D(Eigen::MatrixXd::Zero(1, 1)),
                           _dt(-1), _isDiscrete(false)
            {};

            /**
             * @brief Construct a state space system with the given matrices.
             *
             * @note State space systems are assumed to be in continuous time by
             * default.
             *
             * @param A State matrix.
             * @param B Input matrix.
             * @param C Output matrix.
             * @param D Feedforward matrix.
             */
            StateSpace(const Eigen::MatrixXd &A, const Eigen::MatrixXd &B,
                       const Eigen::MatrixXd &C, const Eigen::MatrixXd &D);

            /**
             * @brief Copy constructor.
             *
             * @param other State space object to copy.
             */
            StateSpace(const StateSpace &other);

            /**
             * @brief Gets the state matrix.
             *
             * @return State matrix.
             */
            Eigen::MatrixXd getA() const;

            /**
             * @brief Sets the state matrix.
             *
             * @param A State matrix.
             */
            void setA(const Eigen::MatrixXd &A);

            /**
             * @brief Gets the input matrix.
             *
             * @return Input matrix.
             */
            Eigen::MatrixXd getB() const;

            /**
             * @brief Sets the input matrix.
             *
             * @param B Input matrix.
             */
            void setB(const Eigen::MatrixXd &B);

            /**
             * @brief Gets the output matrix.
             *
             * @return Output matrix.
             */
            Eigen::MatrixXd getC() const;

            /**
             * @brief Sets the output matrix.
             *
             * @param C Output matrix.
             */
            void setC(const Eigen::MatrixXd &C);

            /**
             * @brief Gets the feedforward matrix.
             *
             * @return Feedforward matrix.
             */
            Eigen::MatrixXd getD() const;

            /**
             * @brief Sets the feedforward matrix.
             *
             * @param D Feedforward matrix.
             */
            void setD(const Eigen::MatrixXd &D);

            /**
             * @brief Copies matrices from one state space object to the current
             * instance.
             *
             * @param ss State space object to copy matrices from.
             */
            void copyMatrices(const StateSpace &ss);

            /**
             * @brief Sets the discrete time system parameters.
             *
             * @param dt Sampling period.
             */
            void setDiscreteParams(double dt);

            /**
             * @brief Sets the discrete time system parameters.
             *
             * @param dt Sampling period.
             * @param discrete If true, the system is treated as a discrete time
             * system.
             */
            void setDiscreteParams(double dt, bool discrete);

            /**
             * @brief Returns a bool that tells if the system is discrete.
             *
             * @return True if the system is discrete.
             */
            bool isDiscrete() const;

            /**
             * @brief Returns the sampling period.
             *
             * @return Sampling period.
             */
            double getSamplingPeriod() const;

            /**
             * @brief Sets the sampling period.
             *
             * @param dt Sampling period.
             */
            void setSamplingPeriod(double dt);

            /**
             * @brief Returns the state dimension.
             *
             * @return State dimension.
             */
            long stateDim() const;

            /**
             * @brief Returns the input dimension.
             *
             * @return Input dimension.
             */
            long inputDim() const;

            /**
             * @brief Returns the output dimension.
             *
             * @return Output dimension
             */
            long outputDim() const;

            /**
             * @brief Appends to state space systems.
             *
             * If the discrete time parameters do not match the current system,
             * the input system is altered to match the current system.
             *
             * @param ss State space system to append.
             */
            virtual void append(const StateSpace &ss);

            /**
             * @brief Determines if the system is stable based on its
             * eigenvalues.
             *
             * \p tolerance sets the stability margin that is taken into
             * account during computation.
             *
             * @param tolerance Eigenvalue tolerance.
             * @return True if system is stable.
             */
            virtual bool isStable(double tolerance = 0) const;

        protected:
            Eigen::MatrixXd _A, /// State matrix.
            _B, /// Input matrix.
            _C, /// Output matrix.
            _D; /// Feedforward matrix.
            double _dt; /// Sampling period.
            bool _isDiscrete; /// Discrete flag.
        };
    }
}


#endif //LODESTAR_STATESPACE_HPP
