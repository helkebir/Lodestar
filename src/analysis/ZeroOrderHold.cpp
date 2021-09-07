//
// Created by Hamza El-Kebir on 4/17/21.
//

#include "ZeroOrderHold.hpp"

ls::systems::StateSpace<>
ls::analysis::ZeroOrderHold::c2d(const Eigen::MatrixXd &A,
                                 const Eigen::MatrixXd &B,
                                 const Eigen::MatrixXd &C,
                                 const Eigen::MatrixXd &D, double dt)
{
    systems::StateSpace<> ss(A, B, C, D);

    return c2d(ss, dt);
}

ls::systems::StateSpace<>
ls::analysis::ZeroOrderHold::c2d(Eigen::MatrixXd *A,
                                 Eigen::MatrixXd *B,
                                 Eigen::MatrixXd *C,
                                 Eigen::MatrixXd *D, double dt)
{
    systems::StateSpace<> ss(A, B, C, D);

    return c2d(ss, dt);
}

ls::systems::StateSpace<>
ls::analysis::ZeroOrderHold::c2d(const systems::StateSpace<> &ss, double dt)
{
    return c2d(&ss, dt);
}

ls::systems::StateSpace<>
ls::analysis::ZeroOrderHold::c2d(const systems::StateSpace<> *ss, double dt)
{
    const long n = ss->stateDim();
    const long m = ss->inputDim();

    systems::StateSpace<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::Dynamic> out;
    auto *memStruct = new mallocStruct<>;
    memStruct->upperXM.resize(n, n + m);
    memStruct->upperXM.setZero();

    memStruct->lowerXM.resize(m, n + m);
    memStruct->lowerXM.setZero();

    memStruct->XM.resize(n + m, n + m);
    memStruct->XM.setZero();

    memStruct->XXM.resize(n, n + m);
    memStruct->XXM.setZero();

    c2d<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::Dynamic>(ss, dt, &out, memStruct);
    delete memStruct;

    return out;
}

ls::systems::StateSpace<>
ls::analysis::ZeroOrderHold::d2c(const Eigen::MatrixXd &A,
                                 const Eigen::MatrixXd &B,
                                 const Eigen::MatrixXd &C,
                                 const Eigen::MatrixXd &D, double dt)
{
    systems::StateSpace<> ss(A, B, C, D);

    return d2c(ss, dt);
}

ls::systems::StateSpace<>
ls::analysis::ZeroOrderHold::d2c(Eigen::MatrixXd *A,
                                 Eigen::MatrixXd *B,
                                 Eigen::MatrixXd *C,
                                 Eigen::MatrixXd *D, double dt)
{
    systems::StateSpace<> ss(A, B, C, D);

    return d2c(ss, dt);
}

ls::systems::StateSpace<>
ls::analysis::ZeroOrderHold::d2c(const ls::systems::StateSpace<> *ss, double dt)
{
    const long n = ss->stateDim();
    const long m = ss->inputDim();

    systems::StateSpace<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::Dynamic> out;
    auto *memStruct = new mallocStruct<>;
    memStruct->upperXM.resize(n, n + m);
    memStruct->upperXM.setZero();

    memStruct->lowerXM.resize(m, n + m);
    memStruct->lowerXM.setZero();

    memStruct->XM.resize(n + m, n + m);
    memStruct->XM.setZero();

    memStruct->XXM.resize(n, n + m);
    memStruct->XXM.setZero();

    d2c<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::Dynamic>(ss, dt, &out, memStruct);
    delete memStruct;

    return out;
}

ls::systems::StateSpace<>
ls::analysis::ZeroOrderHold::d2c(const ls::systems::StateSpace<> &ss, double dt)
{
    return d2c(&ss, dt);
}