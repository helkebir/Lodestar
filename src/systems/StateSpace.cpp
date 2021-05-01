//
// Created by Hamza El-Kebir on 4/17/21.
//

#include "StateSpace.hpp"

ls::systems::StateSpace::StateSpace(const StateSpace &lti)
{
    _A = lti.getA();
    _B = lti.getB();
    _C = lti.getC();
    _D = lti.getD();
    _dt = lti.getSamplingPeriod();
    _isDiscrete = lti.isDiscrete();
}

ls::systems::StateSpace::StateSpace(const Eigen::MatrixXd &A,
                                    const Eigen::MatrixXd &B,
                                    const Eigen::MatrixXd &C,
                                    const Eigen::MatrixXd &D)
{
    _A = A;
    _B = B;
    _C = C;
    _D = D;
    _dt = -1;
    _isDiscrete = false;
}

Eigen::MatrixXd ls::systems::StateSpace::getA() const {
    return _A;
}

const Eigen::MatrixXd& ls::systems::StateSpace::getARef() {
    return _A;
}

void ls::systems::StateSpace::setA(const Eigen::MatrixXd &A) {
    _A = A;
}

Eigen::MatrixXd ls::systems::StateSpace::getB() const {
    return _B;
}

const Eigen::MatrixXd& ls::systems::StateSpace::getBRef() {
    return _B;
}

void ls::systems::StateSpace::setB(const Eigen::MatrixXd &B) {
    _B = B;
}

Eigen::MatrixXd ls::systems::StateSpace::getC() const {
    return _C;
}

const Eigen::MatrixXd& ls::systems::StateSpace::getCRef() {
    return _C;
}

void ls::systems::StateSpace::setC(const Eigen::MatrixXd &C) {
    _C = C;
}

Eigen::MatrixXd ls::systems::StateSpace::getD() const {
    return _D;
}

const Eigen::MatrixXd& ls::systems::StateSpace::getDRef() {
    return _D;
}

void ls::systems::StateSpace::setD(const Eigen::MatrixXd &D) {
    _D = D;
}

bool ls::systems::StateSpace::isDiscrete() const {
    return _isDiscrete;
}

double ls::systems::StateSpace::getSamplingPeriod() const {
    return _dt;
}

void ls::systems::StateSpace::setSamplingPeriod(double dt) {
    _dt = dt;
}

long ls::systems::StateSpace::stateDim() const
{
    return _A.rows();
}

long ls::systems::StateSpace::inputDim() const
{
    return _B.cols();
}

long ls::systems::StateSpace::outputDim() const
{
    return _C.rows();
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


void ls::systems::StateSpace::append(const ls::systems::StateSpace &ss)
{
    // TODO: Implement append function (conservative resize matrices).
}

bool ls::systems::StateSpace::isStable(const double tolerance) const
{
    auto eig = _A.eigenvalues();

    for (int i = 0; i < eig.size(); i++) {
        if (eig(i).real() > tolerance)
            return false;
    }

    return true;
}