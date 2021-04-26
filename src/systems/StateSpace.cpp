//
// Created by Hamza El-Kebir on 4/17/21.
//

#include "StateSpace.hpp"

ls::systems::StateSpace::StateSpace(const StateSpace &lti)
{
    A = lti.A;
    B = lti.B;
    C = lti.C;
    D = lti.D;
    _dt = lti._dt;
    _isDiscrete = lti._isDiscrete;
}

ls::systems::StateSpace::StateSpace(const Eigen::MatrixXd &A_,
                                    const Eigen::MatrixXd &B_,
                                    const Eigen::MatrixXd &C_,
                                    const Eigen::MatrixXd &D_)
{
    A = A_;
    B = B_;
    C = C_;
    D = D_;
    _dt = -1;
    _isDiscrete = false;
}

int ls::systems::StateSpace::stateDim() const
{
    return A.rows();
}

int ls::systems::StateSpace::inputDim() const
{
    return B.cols();
}

int ls::systems::StateSpace::outputDim() const
{
    return C.rows();
}

void ls::systems::StateSpace::setDiscreteParams(double dt)
{
    _dt = dt;
    _isDiscrete = true;
}

void ls::systems::StateSpace::setDiscreteParams(double dt, bool discrete)
{
    _dt = dt;
    _isDiscrete = discrete;
}

bool ls::systems::StateSpace::isDiscrete() const
{
    return _isDiscrete;
}

double ls::systems::StateSpace::getSamplingPeriod() const
{
    return _dt;
}

void ls::systems::StateSpace::setSamplingPeriod(const double dt)
{
    _dt = dt;
}

void ls::systems::StateSpace::append(const ls::systems::StateSpace &ss)
{
    // TODO: Implement append function (conservative resize matrices).
}

bool ls::systems::StateSpace::isStable(const double tolerance) const
{
    auto eig = A.eigenvalues();

    for (int i = 0; i < eig.size(); i++) {
        if (eig(i).real() > tolerance)
            return false;
    }

    return true;
}
