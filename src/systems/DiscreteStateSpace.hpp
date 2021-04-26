//
// Created by Hamza El-Kebir on 4/21/21.
//

#ifndef LODESTAR_DISCRETESTATESPACE_HPP
#define LODESTAR_DISCRETESTATESPACE_HPP

#include "StateSpace.hpp"
#include "analysis/ZeroOrderHold.hpp"
#include "analysis/BilinearTransformation.hpp"

namespace ls { namespace systems {
    class DiscreteStateSpace : public StateSpace {
    public:
        DiscreteStateSpace() : StateSpace()
        {
            setDiscreteParams(1);
        }

        DiscreteStateSpace(double dt) : StateSpace()
        {
            setDiscreteParams(dt);
        }

        DiscreteStateSpace(const Eigen::MatrixXd &A, const Eigen::MatrixXd &B,
                           const Eigen::MatrixXd &C, const Eigen::MatrixXd &D)
                : StateSpace(A, B, C, D)
        {
            setDiscreteParams(1);
        }

        DiscreteStateSpace(const Eigen::MatrixXd &A, const Eigen::MatrixXd &B,
                           const Eigen::MatrixXd &C, const Eigen::MatrixXd &D,
                           double dt)
                : StateSpace(A, B, C, D)
        {
            setDiscreteParams(dt);
        }

        DiscreteStateSpace(const DiscreteStateSpace &dss) : StateSpace(dss)
        {
            setDiscreteParams(dss._dt, dss._isDiscrete);
        }

        void resample(const double dt);

        bool isStable(double tolerance=0) const override;
    };
} }

#endif //LODESTAR_DISCRETESTATESPACE_HPP
