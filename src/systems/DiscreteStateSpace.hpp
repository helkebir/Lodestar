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
        template<typename TScalar = double, int TStateDim = Eigen::Dynamic, int TInputDim = Eigen::Dynamic, int TOutputDim = Eigen::Dynamic>
        class DiscreteStateSpace : public StateSpace<TScalar, TStateDim, TInputDim, TOutputDim> {
        public:
            typedef StateSpace<TScalar, TStateDim, TInputDim, TOutputDim> Base;

            /**
             * @brief Default constructor.
             *
             * Sets sampling time to 1.
             */
            DiscreteStateSpace() : StateSpace<TScalar, TStateDim, TInputDim, TOutputDim>()
            {
                Base::setDiscreteParams(1);
            }

            /**
             * @brief Constructs empty discrete state space system with given
             * sampling period.
             *
             * @param dt Sampling period.
             */
            DiscreteStateSpace(double dt) : StateSpace<TScalar, TStateDim, TInputDim, TOutputDim>()
            {
                Base::setDiscreteParams(dt);
            }

            /**
             * @brief Constructs a discrete state space system with the given
             * matrices.
             *
             * The sampling period is set to 1.
             *
             * @param A TState matrix.
             * @param B Input matrix.
             * @param C Output matrix.
             * @param D Feedforward matrix.
             */
            DiscreteStateSpace(const Eigen::MatrixXd &A,
                               const Eigen::MatrixXd &B,
                               const Eigen::MatrixXd &C,
                               const Eigen::MatrixXd &D)
                    : StateSpace<>(A, B, C, D)
            {
                Base::setDiscreteParams(1);
            }

            /**
             * @brief Constructs a discrete state space system with the given
             * matrices.
             *
             * @param A TState matrix.
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
                    : StateSpace<>(A, B, C, D)
            {
                Base::setDiscreteParams(dt);
            }

            /**
             * @brief Copy constructor.
             *
             * @param other Discrete state space object to copy.
             */
            DiscreteStateSpace(const DiscreteStateSpace &other) :
                    StateSpace<TScalar, TStateDim, TInputDim, TOutputDim>(other)
            {
                setDiscreteParams(other.dt_, other.isDiscrete_);
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

            bool isStable(double tolerance = 0) const;
        };
    }
}

template<typename TScalar, int TStateDim, int TInputDim, int TOutputDim>
void ls::systems::DiscreteStateSpace<TScalar, TStateDim, TInputDim, TOutputDim>::resample(const double dt)
{
    auto dss = ls::analysis::ZeroOrderHold::c2d(
            ls::analysis::ZeroOrderHold::d2c(*this, Base::getSamplingPeriod()), dt);

    copyMatrices(dss);

    Base::setSamplingPeriod(dt);
}

template<typename TScalar, int TStateDim, int TInputDim, int TOutputDim>
void ls::systems::DiscreteStateSpace<TScalar, TStateDim, TInputDim, TOutputDim>::resampleFast(const double dt)
{
    auto dss = ls::analysis::BilinearTransformation::c2dBwdDiff(
            ls::analysis::BilinearTransformation::d2cBwdDiff(*this, Base::getSamplingPeriod()), dt);

    copyMatrices(dss);

    Base::setSamplingPeriod(dt);
}

template<typename TScalar, int TStateDim, int TInputDim, int TOutputDim>
bool ls::systems::DiscreteStateSpace<TScalar, TStateDim, TInputDim, TOutputDim>::isStable(const double tolerance) const
{
    auto eig = Base::A_->eigenvalues();
    double tol = (tolerance < 0 ? -tolerance * tolerance : tolerance *
                                                           tolerance);

    for (int i = 0; i < eig.size(); i++) {
        if (eig(i).real() * eig(i).real() + eig(i).imag() * eig(i).imag() > 1 + tol)
            return false;
    }

    return true;
}

#endif //LODESTAR_DISCRETESTATESPACE_HPP
