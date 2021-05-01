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
        TransferFunction() : _num(Eigen::MatrixXd::Constant(1, 1, 1)),
                             _den(Eigen::MatrixXd::Constant(1, 1, 1))
        {}

        TransferFunction(const TransferFunction &tf);

        TransferFunction(const Eigen::MatrixXd &num,
                         const Eigen::MatrixXd &den) : _num(num), _den(den)
        {}

        Eigen::MatrixXd getNum() const;

        const Eigen::MatrixXd& getNumRef();

        void setNum(const Eigen::MatrixXd &num);

        Eigen::MatrixXd getDen() const;

        const Eigen::MatrixXd& getDenRef();

        void setDen(const Eigen::MatrixXd &num);

        void normalize();
        TransferFunction normalized() const;

        StateSpace toStateSpace() const;

        StateSpace toDiscreteStateSpace(double dt) const;
        StateSpace toDiscreteStateSpace(double dt, double alpha) const;

    private:
        Eigen::MatrixXd _num, _den;
    };
} }

#endif //LODESTAR_TRANSFERFUNCTION_HPP
