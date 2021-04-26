//
// Created by Hamza El-Kebir on 4/18/21.
//

#ifndef LODESTAR_TRANSFERFUNCTION_HPP
#define LODESTAR_TRANSFERFUNCTION_HPP

#include "SystemStateless.hpp"
#include "StateSpace.hpp"
#include "DiscreteStateSpace.hpp"
#include "analysis/BilinearTransformation.hpp"
#include "LodestarErrors.hpp"

#include "Eigen/Dense"

namespace ls { namespace systems {
    class TransferFunction : SystemStateless {
    public:
        TransferFunction() : num(Eigen::MatrixXd::Constant(1, 1, 1)),
                             den(Eigen::MatrixXd::Constant(1, 1, 1))
        {}

        TransferFunction(const TransferFunction &tf);

        TransferFunction(const Eigen::MatrixXd &_num,
                         const Eigen::MatrixXd &_den) : num(_num), den(_den)
        {}

        void normalize();
        TransferFunction normalized() const;

        StateSpace toStateSpace() const;

        StateSpace toDiscreteStateSpace(double dt) const;
        StateSpace toDiscreteStateSpace(double dt, double alpha) const;

        Eigen::MatrixXd num, den;
    };
} }

#endif //LODESTAR_TRANSFERFUNCTION_HPP
